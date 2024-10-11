#pragma once

#include "CoreMinimal.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "GameFramework/Pawn.h"
#include "CG_PlayerPawn.generated.h"

USTRUCT()
struct FMovementInterpolateData
{
	GENERATED_BODY()
	
public:
	float InterpolationValue;
	FVector* StartPosition;
	FVector* EndPosition;
	FTimerHandle TimerHandle;

	FMovementInterpolateData(): StartPosition(nullptr), EndPosition(nullptr)
	{
		InterpolationValue = 0;
	}

	FMovementInterpolateData(FVector* startPos, const FTimerHandle* timerHandle): EndPosition(nullptr)
	{
		InterpolationValue = 0;
		StartPosition = startPos;
		TimerHandle = *timerHandle;
	}

public:
	void ResetTimer(FVector* EndPos)
	{
		InterpolationValue = 0;
		EndPosition = EndPos;
	}
};


class ACGCardActor;
class UCG_DeckComponent;
class UInputMappingContext;
class UInputAction;
class UCGState_DrawPhase;
class FOnDrawEnd;

UCLASS()
class CARDGAME_API ACG_PlayerPawn : public APawn
{
	GENERATED_BODY()

	/* ------------------------------------------ MEMBERS -------------------------------------------*/
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UCG_DeckComponent> m_DeckComponent;

	UPROPERTY()
	FMovementInterpolateData MovementInterpolateData;
	
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TSoftObjectPtr<UCurveFloat> CardDrawAnimCurve;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	float CardDrawAnimDuration;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	float CardDrawAnimRefreshRate;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	int32 DefaultMaxNumCardToDraw;
	
	UPROPERTY()
	bool IsDrawingCard;

	UPROPERTY()
	int32 CurrentMaxNumCardToDraw;
	
	UPROPERTY()
	TArray<TObjectPtr<ACGCardActor>> Hand;
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
	
public:
	ACG_PlayerPawn();

	UFUNCTION()
	void DrawCard(FOnDrawEnd DrawEndDelegate);

	DECLARE_GETTER(Hand, Hand, TArray<TObjectPtr<ACGCardActor>>);
	DECLARE_GETTER_IS_BOOL(Drawing, IsDrawingCard);
	DECLARE_GETTER(CurrentMaxNumCardToDraw, CurrentMaxNumCardToDraw, int32);

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
