#include "FSM_Gameplay.h"

#include "CardGame_ICAN_5JV_1/CardGame_ICAN_5JV_1.h"
#include "CardGame_ICAN_5JV_1/Macro/LogMacro.h"
#include "CardGame_ICAN_5JV_1/Managers/GameMode_Gameplay.h"
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
		m_CurrentState->OnExitState();
	}
	
	m_CurrentState = UBaseState::MakeStateWithClass(NewStateClass, GetOwner());
	m_CurrentState->Initialization(Cast<AGameMode_Gameplay>(GetOwner()));
	m_CurrentState->OnEnterState();
	return true;
}

void UFSM_Gameplay::BeginPlay()
{
	Super::BeginPlay();
	ChangeStateWithClass(m_StartState);
}

void UFSM_Gameplay::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(m_CurrentState)
	{
		m_CurrentState->OnStateTick(DeltaTime);
	}
}

