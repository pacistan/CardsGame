#include "CGBaseState.h"

UCGBaseState* UCGBaseState::MakeStateWithClass(TSubclassOf<UCGBaseState> NewStateClass, UObject* Outer)
{
	return NewObject<UCGBaseState>(Outer, NewStateClass);
}

void UCGBaseState::Initialization(ACGGameMode* gameMode)
{
	GameMode = gameMode;
}

void UCGBaseState::OnEnterState()
{
}

void UCGBaseState::OnStateTick(float DeltaTime)
{
}

void UCGBaseState::OnExitState()
{
}
