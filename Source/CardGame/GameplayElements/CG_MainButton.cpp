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

void ACG_MainButton::OnHoverStart(ACG_PlayerPawn* Pawn)
{
}

void ACG_MainButton::OnHoverStop(ACG_PlayerPawn* Pawn)
{
}

void ACG_MainButton::OnSelect(ACG_PlayerPawn* Pawn)
{
	Pawn->PlayCard();
}

void ACG_MainButton::OnRelease(ACG_PlayerPawn* Pawn)
{
}

void ACG_MainButton::OnDrag(ACG_PlayerPawn* Pawn, FVector MousePosition)
{
}

void ACG_MainButton::OnExamine(ACG_PlayerPawn* Pawn)
{
}


