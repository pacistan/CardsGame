// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardGame/FSM/States/CGState_DrawPhase.h"
#include "CardGame/Interfaces/HoverableInterface.h"
#include "GameFramework/Actor.h"
#include "CGCardActor.generated.h"

class ACGPlayerPawn;
class UWidgetComponent;
class UStaticMeshComponent;
class UCGCardData_Base;


UENUM()
enum class ECardState : uint8
{
	INACTIVE,
	HOVERED,
	SELECTED,
	PLAYED,
	ISEXAMINED
};

UCLASS()
class CARDGAME_API ACGCardActor : public AActor, public IHoverableInterface
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY(EditAnywhere, Category="CardActor|", DisplayName = "Card Mesh")
	UStaticMeshComponent* CardMesh;

	UPROPERTY(EditAnywhere, Category="CardActor|", DisplayName = "Card Widget")
	UWidgetComponent* CardWidget;
	
	UPROPERTY(EditInstanceOnly, DisplayName = "Card Data")
	TSoftObjectPtr<UCGCardData_Base> CardData;

	UPROPERTY(EditInstanceOnly, DisplayName = "Card Owner")
	TObjectPtr<ACGPlayerPawn> CardOwner;
	
	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	TObjectPtr<UCurveFloat> CardDrawAnimCurve;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	float CardDrawAnimDuration;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	float CardDrawAnimRefreshRate;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	float CardOffset;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	float CardTiltOffset;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	float CardHeightOffset;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	float HandHeightOffset;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	float HoveredOffsetZ;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	float HoveredScaleOffset;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	float PlayedScaleOffSet;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	float SelectedScaleOffset;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	float HoveringTransitionDuration;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	TSoftObjectPtr<UMaterialInterface> SelectedMat;

	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	TSoftObjectPtr<UMaterialInterface> PlayedMat;
	
	UPROPERTY(EditAnywhere, Category="CardActor|CardMovement", meta=(AllowPrivateAccess))
	TSoftObjectPtr<UMaterialInterface> NormalMat;
	
	UPROPERTY()
	FVector BaseScale;
	
	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	FVector StartPosition;
	
	UPROPERTY()
	FVector EndPosition;

	UPROPERTY()
	FRotator StartRotator;

	UPROPERTY()
	FRotator EndRotator;
	
	UPROPERTY()
	FVector StartScale;

	UPROPERTY()
	FVector EndScale;
	
	UPROPERTY()
	float InterpolationValue;

	UPROPERTY()
	ECardState CurrentCardState;

	UPROPERTY()
	FVector AnchorPosition;
	
	/* ------------------------------------------ METHODS -------------------------------------------*/
public:
	ACGCardActor(FObjectInitializer const& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void OnCardPlayed();

	UFUNCTION(BlueprintCallable)
	void OnUnselect();

	UFUNCTION()
	void InitiateMovement(bool IsHoveringOperation = false, ACGPlayerPawn* PawnOwner = nullptr, const FOnDrawEnd& DrawEndDelegate = FOnDrawEnd());

	UFUNCTION()
	void RemoveCardFromPlayArray();
	
protected:
	UFUNCTION()
	void DrawAnimTickRate(const FOnDrawEnd& DrawEndDelegate, float Duration);

	/* ------------------------------------------ OVERRIDE -------------------------------------------*/
	virtual void BeginPlay() override;
	
	/* ------------------------------------------ INTERFACE -------------------------------------------*/
	
	virtual void OnHoverStart(ACGPlayerPawn* Pawn) override;
	
	virtual void OnHoverStop(ACGPlayerPawn* Pawn) override;
	
	virtual void OnSelect(ACGPlayerPawn* Pawn) override;
	
	virtual void OnRelease(ACGPlayerPawn* Pawn) override;
	
	virtual void OnDrag(ACGPlayerPawn* Pawn, FVector MousePosition) override;
	
	virtual void OnExamine(ACGPlayerPawn* Pawn) override;
};
