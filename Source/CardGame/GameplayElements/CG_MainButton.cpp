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

void ACG_MainButton::OnClick(ACG_PlayerPawn* Pawn)
{
	Pawn->PlayCard(nullptr);
}
