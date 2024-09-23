#include "FSM_Gameplay.h"
#include "States/BaseState.h"
#include "States/State_DrawPhase.h"


UFSM_Gameplay::UFSM_Gameplay(const FObjectInitializer& fObj) : Super(fObj)
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UFSM_Gameplay::ChangeStateWithClass(TSubclassOf<UBaseState> NewStateClass)
{
	if(NewStateClass == nullptr)
	{
		return false;
	}
	else if(m_CurrentState != nullptr)
	{
		m_CurrentState->OnEnterState();
	}
	
	m_CurrentState = UBaseState::MakeStateWithClass(NewStateClass, GetOwner());
	m_CurrentState->OnExitState();
	
	return true;
}

void UFSM_Gameplay::BeginPlay()
{
	Super::BeginPlay();
	ChangeStateWithClass(m_StartState);
}

