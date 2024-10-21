// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CGMovementPatternBase.generated.h"


/**
 *  Class That handle a Pattern of Movement 
 */
UCLASS()
class CARDGAME_API UCGMovementPatternBase : public UDataAsset
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
public:
	/* 0 Up, 1 Diagonal, 2 Right */ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	TArray<uint8> MovementGrid ;  

	// Function de validation du pattern
	bool IsValidPattern(int8 x, int8 y) const; 
};
