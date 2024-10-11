#include "CGBaseState.h"

UCGBaseState* UCGBaseState::MakeStateWithClass(TSubclassOf<UCGBaseState> NewStateClass, UObject* Outer)
{
	return NewObject<UCGBaseState>(Outer, NewStateClass);
}

void UCGBaseState::Initialization(ACGGameMode* GameMode)
{
	m_GameMode = GameMode;
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
