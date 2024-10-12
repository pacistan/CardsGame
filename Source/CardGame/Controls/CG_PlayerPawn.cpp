#include "CG_PlayerPawn.h"
#include "CardGame/Card/CGCardActor.h"
#include "CardGame/Card/Deck/CG_DeckComponent.h"
#include "CardGame/FSM/States/CGState_DrawPhase.h"
#include "CardGame/Managers/CGGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ACG_PlayerPawn::ACG_PlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	DeckComponent = CreateDefaultSubobject<UCG_DeckComponent>(TEXT("Deck"));
}

void ACG_PlayerPawn::DrawCard(FOnDrawEnd DrawEndDelegate)
{
	if(GetWorld())
	{
		const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		const FVector CameraLocation = CameraManager->GetCameraLocation();
		const FRotator CameraRotation = CameraManager->GetCameraRotation();
		const FVector CameraRightVector = FRotationMatrix(CameraRotation).GetScaledAxis(EAxis::Y);
		
		auto newCard = DeckComponent->CreateCard();
		if(newCard == nullptr) return;
		PlayerHand.Add(newCard);
		;
		EndPosition = FVector(CameraLocation + (CameraRotation.Vector() * DistanceFromCamera) + CameraRightVector * CardOffset * (PlayerHand.Num())
			- CameraRightVector * CardOffset * GetCurrentMaxNumCardToDraw() / 2.0f);

		const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation + (CameraRotation.Vector() * DistanceFromCamera), CameraLocation);
		PlayerHand.Last()->SetActorRotation(LookAtRotation);
		
		InterpolationValue = 0;
		
		const FTimerDelegate TimerDel = FTimerDelegate::CreateLambda([this, DrawEndDelegate]()
		{
			DrawAnimTickRate(DrawEndDelegate);
		});
		OnDrawEndDelegate = DrawEndDelegate;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, CardDrawAnimRefreshRate, true);
	}
}

void ACG_PlayerPawn::DrawAnimTickRate(const FOnDrawEnd& DrawEndDelegate)
{
	if(!GetWorld() || PlayerHand.Num() == 0)
	{
		return;
	}
	const FVector newPosition = FMath::Lerp(StartPosition, EndPosition, CardDrawAnimCurve->FloatCurve.Eval(InterpolationValue));
	PlayerHand.Last()->SetActorLocation(newPosition);
	InterpolationValue = FMath::Clamp(InterpolationValue +  CardDrawAnimRefreshRate / CardDrawAnimDuration, 0, 1);

	if(InterpolationValue >= 1 )
	{
		PlayerHand.Last()->SetActorLocation(EndPosition);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		DrawEndDelegate.ExecuteIfBound(this);
	}
}

void ACG_PlayerPawn::RegisterPlayerToGameMode_Implementation()
{
	if (HasAuthority())
	{
		Cast<ACGGameMode>(GetWorld()->GetAuthGameMode())->RegisterPlayerPawn(this);
	}
}

bool ACG_PlayerPawn::RegisterPlayerToGameMode_Validate()
{
	return true;
}



void ACG_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerHand = *new TArray<ACGCardActor*>();
	PlayerHand.Reserve(5);
	CurrentMaxNumCardToDraw = DefaultMaxNumCardToDraw;
	StartPosition = FVector(GetActorLocation().X - 1000,0,0);
}

void ACG_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


