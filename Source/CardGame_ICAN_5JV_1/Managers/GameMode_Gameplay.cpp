// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_Gameplay.h"
#include "GridManager.h"
#include "CardGame_ICAN_5JV_1/FSM/FSM_Gameplay.h"


AGameMode_Gameplay::AGameMode_Gameplay(const FObjectInitializer& fObj) : Super(fObj)
{
	m_GridManager = CreateDefaultSubobject<UGridManager>(TEXT("Grid Manager"));
	m_FSM = CreateDefaultSubobject<UFSM_Gameplay>(TEXT("Finite State Machine"));
}
