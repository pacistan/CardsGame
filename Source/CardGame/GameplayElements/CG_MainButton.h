// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardGame/Interfaces/Clickable.h"
#include "CardGame/Interfaces/Hoverable.h"
#include "GameFramework/Actor.h"
#include "CG_MainButton.generated.h"

UCLASS()
class CARDGAME_API ACG_MainButton : public AActor, public IClickable
{
	GENERATED_BODY()

public:
	ACG_MainButton();

protected:
	virtual void BeginPlay() override;

public:

	virtual void OnClick(ACG_PlayerPawn* Pawn) override;
};
