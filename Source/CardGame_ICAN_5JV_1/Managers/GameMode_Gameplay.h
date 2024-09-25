// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_Gameplay.generated.h"

class UFSM_Gameplay;
class AGridManager;

UCLASS()
class CARDGAME_ICAN_5JV_1_API AGameMode_Gameplay : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

public:
	//TODO: Make a getter for FSM


protected:
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UFSM_Gameplay> m_FSM;
};
