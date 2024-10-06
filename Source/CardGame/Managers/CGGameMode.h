// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGGameMode.generated.h"

class UCGFSM;
class ACGGridManager;

UCLASS()
class CARDGAME_API ACGGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

public:
	//TODO: Make a getter for FSM

protected:
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UCGFSM> m_FSM;
};
