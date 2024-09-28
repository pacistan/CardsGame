#include "PlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CardGame_ICAN_5JV_1/Card/CardActor.h"
#include "CardGame_ICAN_5JV_1/Deck/DeckComponent.h"
#include "CardGame_ICAN_5JV_1/Macro/LogMacro.h"
#include "CardGame_ICAN_5JV_1/Managers/GameMode_Gameplay.h"


APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	m_DeckComponent = CreateDefaultSubobject<UDeckComponent>(TEXT("Deck"));
}

void APlayerPawn::DrawCard(FOnDrawEnd DrawEndDelegate)
{
	ACardActor* newCard = nullptr;
	if(!m_DeckComponent->CreateCard(newCard) || !GetWorld())
	{
		return;
	}
	else
	{
		m_Hand.Add(newCard);
		FVector EndPosition = FVector(0,0,0);
		m_MovementInterpolateData.ResetTimer(EndPosition);
		FTimerDelegate TimerDel = FTimerDelegate::CreateLambda([this, DrawEndDelegate]()
		{
				APlayerPawn::DrawAnimTickRate(DrawEndDelegate);
		});
		GetWorld()->GetTimerManager().SetTimer(m_MovementInterpolateData.TimerHandle, TimerDel, m_Duration, true);
	}
}

void APlayerPawn::DrawAnimTickRate(FOnDrawEnd DrawEndDelegate)
{
	auto startPos = m_MovementInterpolateData.StartPosition;
	auto endPos = m_MovementInterpolateData.EndPosition;
	m_MovementInterpolateData.InterpolationValue += m_DrawAnimRefreshRate / m_Duration;
	m_MovementInterpolateData.InterpolationValue = FMath::Clamp(0, 1, m_MovementInterpolateData.InterpolationValue);
	FVector newPosition = FMath::Lerp(startPos, endPos, m_Curve->FloatCurve.Eval(m_MovementInterpolateData.InterpolationValue));
	
	if(m_MovementInterpolateData.InterpolationValue >= 1 )
	{
		if(!GetWorld())
		{
			return;
		}
		m_Hand.Last()->SetActorLocation(m_MovementInterpolateData.EndPosition);
		GetWorld()->GetTimerManager().ClearTimer(m_MovementInterpolateData.TimerHandle);
		DrawEndDelegate.ExecuteIfBound(this);
	}
	else
	{
		FTimerDelegate TimerDel = FTimerDelegate::CreateLambda([this, DrawEndDelegate]()
		{
			APlayerPawn::DrawAnimTickRate(DrawEndDelegate);
		});
		GetWorld()->GetTimerManager().SetTimer(m_MovementInterpolateData.TimerHandle, TimerDel, m_Duration, true);
	}
}

void APlayerPawn::RegisterPlayerToGameMode_Implementation()
{
	if (HasAuthority())
	{
		// We're the server, call the function directly
		Cast<AGameMode_Gameplay>(GetWorld()->GetAuthGameMode())->RegisterPlayerPawn(this);
	}
}

bool APlayerPawn::RegisterPlayerToGameMode_Validate()
{
	return true;
}



void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	m_CurrentMaxNumCardToDraw = m_DefaultMaxNumCardToDraw;
	FTimerHandle TimerHandle;
	FVector StartPosition = FVector(0,0,0);
	m_MovementInterpolateData = *new FMovementInterpolateData(StartPosition, &TimerHandle);
	if(GetWorld())
	{
		RegisterPlayerToGameMode();
	}

}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
