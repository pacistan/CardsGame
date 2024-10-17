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

	virtual void OnHoverStart(ACGPlayerPawn* Pawn) override;

	virtual void OnHoverStop(ACGPlayerPawn* Pawn) override;

	virtual void OnSelect(ACGPlayerPawn* Pawn) override;

	virtual void OnRelease(ACGPlayerPawn* Pawn) override;

	virtual void OnDrag(ACGPlayerPawn* Pawn, FVector MousePosition) override;

	virtual void OnExamine(ACGPlayerPawn* Pawn) override;
};
