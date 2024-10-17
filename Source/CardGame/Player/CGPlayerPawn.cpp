#include "CGPlayerPawn.h"
#include "CardGame/Card/CGCardActor.h"
#include "CardGame/Card/Deck/CG_DeckActor.h"
#include "CardGame/Card/Deck/CG_DeckComponent.h"
#include "CardGame/FSM/States/CGState_DrawPhase.h"
#include "CardGame/Managers/CGGameMode.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ACGPlayerPawn::ACGPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	DeckComponent = CreateDefaultSubobject<UCG_DeckComponent>(TEXT("Deck"));
}

void ACGPlayerPawn::DrawCard(const FOnDrawEnd& DrawEndDelegate)
{
	if(GetWorld())
	{
		const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		const FVector CameraLocation = CameraManager->GetCameraLocation();
		const FRotator CameraRotation = CameraManager->GetCameraRotation();
		const FRotator StartRotator = UKismetMathLibrary::FindLookAtRotation(CameraLocation + (CameraRotation.Vector() * DistanceFromCamera), CameraLocation);
		auto newCard = DeckComponent->CreateCard(DeckActorLocation, StartRotator);
		if(newCard == nullptr) return;
		PlayerHand.Add(newCard);
		for(int i = 0; i < PlayerHand.Num() - 1; i++ )
		{
			PlayerHand[i]->InitiateMovement();
		}
		newCard->InitiateMovement(false, this, DrawEndDelegate);
	}
}

void ACGPlayerPawn::RegisterPlayerToGameMode_Implementation()
{
	if (HasAuthority())
	{
		Cast<ACGGameMode>(GetWorld()->GetAuthGameMode())->RegisterPlayerPawn(this);
	}
}

bool ACGPlayerPawn::RegisterPlayerToGameMode_Validate()
{
	return true;
}

void ACGPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerHand = *new TArray<ACGCardActor*>();
	PlayerHand.Reserve(5);
	CurrentMaxNumCardToDraw = DefaultMaxNumCardToDraw;
	DeckActorLocation = Cast<ACGGameMode>(GetWorld()->GetAuthGameMode())->GetDeck(0)->GetActorLocation();
	PlayedCardIndexs = TArray<int32>();
	PlayedCardIndexs.Reserve(5);
}

void ACGPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


