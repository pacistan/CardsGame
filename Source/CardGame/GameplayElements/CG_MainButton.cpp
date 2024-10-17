// Fill out your copyright notice in the Description page of Project Settings.


#include "CG_MainButton.h"

#include "CardGame/Controls/CG_PlayerPawn.h"


ACG_MainButton::ACG_MainButton()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACG_MainButton::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACG_MainButton::OnHoverStart(ACGPlayerPawn* Pawn)
{
}

void ACG_MainButton::OnHoverStop(ACGPlayerPawn* Pawn)
{
}

void ACG_MainButton::OnSelect(ACGPlayerPawn* Pawn)
{
	Pawn->PlayCard();
}

void ACG_MainButton::OnRelease(ACGPlayerPawn* Pawn)
{
}

void ACG_MainButton::OnDrag(ACGPlayerPawn* Pawn, FVector MousePosition)
{
}

void ACG_MainButton::OnExamine(ACGPlayerPawn* Pawn)
{
}


