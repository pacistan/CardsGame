// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardGame/Interfaces/HoverableInterface.h"
#include "GameFramework/Actor.h"
#include "CG_MainButton.generated.h"

UCLASS()
class CARDGAME_API ACG_MainButton : public AActor, public IHoverableInterface
{
	GENERATED_BODY()

public:
	ACG_MainButton();

protected:
	virtual void BeginPlay() override;

public:

	virtual void OnHoverStart(ACG_PlayerPawn* Pawn) override;

	virtual void OnHoverStop(ACG_PlayerPawn* Pawn) override;

	virtual void OnSelect(ACG_PlayerPawn* Pawn) override;

	virtual void OnRelease(ACG_PlayerPawn* Pawn) override;

	virtual void OnDrag(ACG_PlayerPawn* Pawn, FVector MousePosition) override;

	virtual void OnExamine(ACG_PlayerPawn* Pawn) override;
};
