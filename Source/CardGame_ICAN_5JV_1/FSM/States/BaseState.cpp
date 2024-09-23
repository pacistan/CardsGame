// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseState.h"

UBaseState* UBaseState::MakeStateWithClass(TSubclassOf<UBaseState> NewStateClass, UObject* Outer)
{
	return NewObject<UBaseState>(Outer, NewStateClass);
}

void UBaseState::OnEnterState()
{
}

void UBaseState::OnExitState()
{
}
