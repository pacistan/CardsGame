// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Barrier.generated.h"

class APlayerPawn;
/**
 * 
 */
UCLASS()
class CARDGAME_ICAN_5JV_1_API UBarrier : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<APlayerPawn*> m_Players;

	UPROPERTY()
	bool m_IsBarriereCompleted;
	
	UFUNCTION()
	void OnBarrierIni();

	UFUNCTION()
	void OnTick(float DeltaTime);

};
