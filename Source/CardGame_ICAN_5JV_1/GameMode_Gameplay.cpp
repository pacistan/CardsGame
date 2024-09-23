// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_Gameplay.h"

#include "FSM/FSM_Gameplay.h"

AGameMode_Gameplay::AGameMode_Gameplay(const FObjectInitializer& fObj) : Super(fObj)
{
	m_FSM = CreateDefaultSubobject<UFSM_Gameplay>(TEXT("FSM"));
}