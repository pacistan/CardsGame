#pragma once

#include "CoreMinimal.h"
#include "CardGame/FSM/States/CGState_DrawPhase.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "GameFramework/Pawn.h"
#include "CG_PlayerPawn.generated.h"

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
	UPROPERTY(EditAnywhere)
	float DistanceFromCamera;
	
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UCG_DeckComponent> DeckComponent;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UCurveFloat> CardDrawAnimCurve;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	float CardDrawAnimDuration;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	float CardDrawAnimRefreshRate;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	int32 DefaultMaxNumCardToDraw;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	float CardOffset;
	
	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	FVector StartPosition;
	
	UPROPERTY()
	FVector EndPosition;

	UPROPERTY()
	float InterpolationValue;

	UPROPERTY()
	int32 CurrentMaxNumCardToDraw;
	
	UPROPERTY()
	TArray<TObjectPtr<ACGCardActor>> PlayerHand;

	UPROPERTY()
	FOnDrawEnd OnDrawEndDelegate;
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
	
public:
	ACG_PlayerPawn();

	UFUNCTION()
	void DrawCard(FOnDrawEnd DrawEndDelegate);

	DECLARE_GETTER(CurrentMaxNumCardToDraw, CurrentMaxNumCardToDraw, int32);

	UFUNCTION()
	TArray<ACGCardActor*> GetHand() {return PlayerHand;}
	
protected:
	UFUNCTION()
	void DrawAnimTickRate(const FOnDrawEnd& DrawEndDelegate);

	UFUNCTION(Server, Reliable, WithValidation)
	void RegisterPlayerToGameMode();
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
