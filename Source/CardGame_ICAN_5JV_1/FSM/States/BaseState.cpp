// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseState.h"

UBaseState* UBaseState::MakeStateWithClass(TSubclassOf<UBaseState> NewStateClass, UObject* Outer)
{
	return NewObject<UBaseState>(Outer, NewStateClass);
}

void UBaseState::Initialization(AGameMode_Gameplay* GameMode)
{
	m_GameMode = GameMode;
}

void UBaseState::OnEnterState()
{
}

void UBaseState::OnStateTick(float DeltaTime)
{
}

void UBaseState::OnExitState()
{
}
