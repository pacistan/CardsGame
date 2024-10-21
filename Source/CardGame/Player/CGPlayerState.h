// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "GameFramework/PlayerState.h"
#include "CGPlayerState.generated.h"

class ACGPlayerPawn;
class ACG_PlayerController;
/**
 * 
 */
UCLASS()
class CARDGAME_API ACGPlayerState : public APlayerState
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UFUNCTION(BlueprintCallable, Category = "CG|PlayerState")
	ACG_PlayerController* GetCGPlayerController() const;

public:
	
	// Class to instantiate for this pawn (need to derive if ACGPlayerPawn)
	UPROPERTY(Replicated)
	TSubclassOf<ACGPlayerPawn> PawnClass;
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
protected:
	
public:
	ACGPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void SetPawnClass(const TSubclassOf<ACGPlayerPawn> InPawnClass);
	/* ------------------------------------------ OVERRIDE -------------------------------------------*/
	
	//~AActor interface
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	//~End of AActor interface
};
