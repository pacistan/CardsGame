#include "PlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CardGame_ICAN_5JV_1/Card/CardActor.h"
#include "CardGame_ICAN_5JV_1/Deck/DeckComponent.h"
#include "CardGame_ICAN_5JV_1/Macro/LogMacro.h"


APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	m_DeckComponent = CreateDefaultSubobject<UDeckComponent>(TEXT("Deck"));
}

void APlayerPawn::DrawCard()
{
	ACardActor* newCard;
	if(!m_DeckComponent->CreateCard(newCard) || !GetWorld())
	{
		return;
	}
	else
	{
		m_Hand.Add(newCard);
		FVector EndPosition = FVector(0,0,0);
		m_MovementInterpolateData->ResetTimer(EndPosition);
		GetWorld()->GetTimerManager().SetTimer(*m_MovementInterpolateData.Get()->TimerHandle, this, &APlayerPawn::DrawAnimTickRate, m_Duration, true);
	}
}

void APlayerPawn::DrawAnimTickRate()
{
	auto startPos = m_MovementInterpolateData->StartPosition;
	auto endPos = m_MovementInterpolateData->EndPosition;
	m_MovementInterpolateData->InterpolationValue += m_DrawAnimRefreshRate; / m_Duration;
	m_MovementInterpolateData->InterpolationValue = FMath::Clamp(0, 1, m_MovementInterpolateData->InterpolationValue);
	FVector newPosition = FMath::Lerp(startPos, endPos, m_Curve->FloatCurve.Eval(m_MovementInterpolateData->InterpolationValue));
	
	if(m_MovementInterpolateData->InterpolationValue >= 1 )
	{
		if(!GetWorld())
		{
			return;
		}
		m_Hand.Last()->SetActorLocation(m_MovementInterpolateData->EndPosition);
		GetWorld()->GetTimerManager().ClearTimer(*m_MovementInterpolateData->TimerHandle);
	}
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	FVector StartPosition = FVector(0,0,0);
	m_MovementInterpolateData = new FMovementInterpolateData(StartPosition, &TimerHandle);

}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
