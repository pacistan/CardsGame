﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CG_PlayerController.generated.h"

class ACG_PlayerPawn;
class IHoverable;
class ACGCardActor;
class UInputMappingContext;
class UInputAction;

UCLASS()
class CARDGAME_API ACG_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere,Category = "PlayerPawn|Input", meta=(DisplayName = "Card Distance from Camera"))
	float DistanceFromCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Default Mapping Context"))
	UInputMappingContext* IMC_Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Left Click Press Action"))
	UInputAction* IA_SelectCard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Left Click Drag Action"))
	UInputAction* IA_DragCard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Left Click Release Action"))
	UInputAction* IA_ReleaseCard;

	TObjectPtr<AActor> CurrentHoveredElement;
	
	TObjectPtr<AActor> CurrentSelectedElement;

	TObjectPtr<AActor> CurrentDraggedElement;

	UPROPERTY()
	TObjectPtr<ACG_PlayerPawn> PlayerPawn;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
private:
	UFUNCTION()
	void OnSelectCard() const;

	UFUNCTION()
	void OnDragCard();

	UFUNCTION()
	void OnReleaseCard();

	FVector GetMouseLocationInWorld() const;
	
	void AddDefaultMappingContext() const;

public:
	
	UFUNCTION()
	float GetDistanceFromCamera() const {return DistanceFromCamera;}

	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;
	void OnSelectCard();
};
