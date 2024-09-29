#pragma once

#include "CoreMinimal.h"
#include "CardGame_ICAN_5JV_1/FSM/States/State_DrawPhase.h"
#include "CardGame_ICAN_5JV_1/Macro/GetSetMacro.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class ACardActor;
class UDeckComponent;
class UInputMappingContext;
class UInputAction;
class UState_DrawPhase;

USTRUCT()
struct FMovementInterpolateData
{
GENERATED_BODY()
	
public:
	float InterpolationValue;
	FVector StartPosition;
	FVector EndPosition;
	FTimerHandle TimerHandle;

	FMovementInterpolateData(){}
	
	FMovementInterpolateData(FVector startPos, FTimerHandle* timerHandle)
	{
		StartPosition = startPos;
		TimerHandle = *timerHandle;
	}

public:
	void ResetTimer(FVector EndPos)
	{
		InterpolationValue = 0;
		EndPosition = EndPos;
	}
};

UCLASS()
class CARDGAME_ICAN_5JV_1_API APlayerPawn : public APawn
{
	GENERATED_BODY()

	/* ------------------------------------------ MEMBERS -------------------------------------------*/
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UDeckComponent> m_DeckComponent;

	UPROPERTY()
	FMovementInterpolateData m_MovementInterpolateData;
	
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TSoftObjectPtr<UCurveFloat> m_Curve;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	float m_Duration;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	float m_DrawAnimRefreshRate;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	int32 m_DefaultMaxNumCardToDraw;
	
	UPROPERTY()
	bool m_IsDrawingCard;

	UPROPERTY()
	int32 m_CurrentMaxNumCardToDraw;
	
	UPROPERTY()
	TArray<TObjectPtr<ACardActor>> m_Hand;
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
	
public:
	APlayerPawn();

	UFUNCTION()
	void DrawCard(FOnDrawEnd DrawEndDelegate);

	DECLARE_GETTER(Hand, m_Hand, TArray<TObjectPtr<ACardActor>>);
	DECLARE_GETTER_IS_BOOL(Drawing, m_IsDrawingCard);
	DECLARE_GETTER(CurrentMaxNumCardToDraw, m_CurrentMaxNumCardToDraw, int32);

protected:
	UFUNCTION()
	void DrawAnimTickRate(FOnDrawEnd DrawEndDelegate);

	UFUNCTION(Server, Reliable, WithValidation)
	void RegisterPlayerToGameMode();
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
