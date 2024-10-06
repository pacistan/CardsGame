// Fill out your copyright notice in the Description page of Project Settings.


#include "CGBaseState.h"

UCGBaseState* UCGBaseState::MakeStateWithClass(TSubclassOf<UCGBaseState> NewStateClass, UObject* Outer)
{
	return NewObject<UCGBaseState>(Outer, NewStateClass);
}

void UCGBaseState::OnEnterState()
{
}

void UCGBaseState::OnExitState()
{
}
