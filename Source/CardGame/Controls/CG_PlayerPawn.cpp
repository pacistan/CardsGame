#include "CG_PlayerPawn.h"
#include "CardGame/Card/CGCardActor.h"
#include "CardGame/Card/Deck/CG_DeckComponent.h"
#include "CardGame/FSM/States/CGState_DrawPhase.h"
#include "CardGame/Managers/CGGameMode.h"

ACG_PlayerPawn::ACG_PlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	m_DeckComponent = CreateDefaultSubobject<UCG_DeckComponent>(TEXT("Deck"));
}

void ACG_PlayerPawn::DrawCard(FOnDrawEnd DrawEndDelegate)
{
	ACGCardActor* newCard = nullptr;
	if(!m_DeckComponent->CreateCard(newCard) || !GetWorld())
	{
		return;
	}
	else
	{
		Hand.Add(newCard);
		FVector* EndPosition = new FVector(0,0,0);
		MovementInterpolateData.ResetTimer(EndPosition);
		const FTimerDelegate TimerDel = FTimerDelegate::CreateLambda([this, DrawEndDelegate]()
		{
				ACG_PlayerPawn::DrawAnimTickRate(DrawEndDelegate);
		});
		GetWorld()->GetTimerManager().SetTimer(MovementInterpolateData.TimerHandle, TimerDel, CardDrawAnimDuration, true);
	}
}

void ACG_PlayerPawn::DrawAnimTickRate(FOnDrawEnd DrawEndDelegate)
{
	const auto startPos = MovementInterpolateData.StartPosition;
	const auto endPos = MovementInterpolateData.EndPosition;
	MovementInterpolateData.InterpolationValue += CardDrawAnimRefreshRate / CardDrawAnimDuration;
	MovementInterpolateData.InterpolationValue = FMath::Clamp(0, 1, MovementInterpolateData.InterpolationValue);
	const FVector newPosition = FMath::Lerp(*startPos, *endPos, CardDrawAnimCurve->FloatCurve.Eval(MovementInterpolateData.InterpolationValue));
	Hand.Last()->SetActorLocation(newPosition);
	
	if(MovementInterpolateData.InterpolationValue >= 1 )
	{
		if(!GetWorld())
		{
			return;
		}
		Hand.Last()->SetActorLocation(*MovementInterpolateData.EndPosition);
		GetWorld()->GetTimerManager().ClearTimer(MovementInterpolateData.TimerHandle);
		DrawEndDelegate.ExecuteIfBound(this);
	}
	else
	{
		const FTimerDelegate TimerDel = FTimerDelegate::CreateLambda([this, DrawEndDelegate]()
		{
			ACG_PlayerPawn::DrawAnimTickRate(DrawEndDelegate);
		});
		GetWorld()->GetTimerManager().SetTimer(MovementInterpolateData.TimerHandle, TimerDel, CardDrawAnimDuration, true);
	}
}

void ACG_PlayerPawn::RegisterPlayerToGameMode_Implementation()
{
	if (HasAuthority())
	{
		// We're the server, call the function directly
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
	CurrentMaxNumCardToDraw = DefaultMaxNumCardToDraw;
	const FTimerHandle TimerHandle;
	FVector StartPosition = FVector(0,0,0);
	MovementInterpolateData = *new FMovementInterpolateData(&StartPosition, &TimerHandle);
	if(GetWorld())
	{
		RegisterPlayerToGameMode();
	}

}

void ACG_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


