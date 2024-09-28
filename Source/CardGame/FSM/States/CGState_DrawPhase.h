// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CGBaseState.h"
#include "UObject/Object.h"
#include "CGState_DrawPhase.generated.h"


UCLASS()
class CARDGAME_API UCGState_DrawPhase : public UCGBaseState
{
	GENERATED_BODY()

	virtual void OnEnterState() override;
	
};
