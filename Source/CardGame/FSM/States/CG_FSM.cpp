#include "CG_FSM.h"
#include "CGBaseState.h"
#include "CardGame/Managers/CGGameMode.h"


UCG_FSM::UCG_FSM()
{
}

void UCG_FSM::Initialize(const ACGGameMode* GameMode)
{
	ChangeStateWithClass(GameMode->GetStartState());
}


bool UCG_FSM::ChangeStateWithClass(TSubclassOf<UCGBaseState> NewStateClass)
{
	if(NewStateClass == nullptr)
	{
		return false;
	}
	else if(CurrentState != nullptr)
	{
		CurrentState->OnExitState();
	}
	
	CurrentState = UCGBaseState::MakeStateWithClass(NewStateClass, Owner);
	CurrentState->Initialization(Cast<ACGGameMode>(Owner));
	CurrentState->OnEnterState();
	return true;
}

void UCG_FSM::Tick(float DeltaTime) const
{
	if(CurrentState)
	{
		CurrentState->OnStateTick(DeltaTime);
	}
}
