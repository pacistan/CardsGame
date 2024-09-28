#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class ACardActor;
class UDeckComponent;
class UInputMappingContext;
class UInputAction;

USTRUCT()
struct FMovementInterpolateData
{
public:
	float InterpolationValue;
	FVector StartPosition;
	FVector EndPosition;
	TObjectPtr<FTimerHandle> TimerHandle;

	FMovementInterpolateData(FVector startPos, FTimerHandle* timerHandle)
	{
		StartPosition = startPos;
		TimerHandle = timerHandle;
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
	TObjectPtr<FMovementInterpolateData> m_MovementInterpolateData;
	
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TSoftObjectPtr<UCurveFloat> m_Curve;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	float m_Duration;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	float m_DrawAnimRefreshRate;
	
	UPROPERTY()
	TArray<TObjectPtr<ACardActor>> m_Hand;
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
	
public:
	APlayerPawn();

	UFUNCTION()
	void DrawCard();

protected:
	UFUNCTION()
	void DrawAnimTickRate();
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
