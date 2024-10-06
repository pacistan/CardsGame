#include "CGFSM.h"

#include "States/CGBaseState.h"

UCGFSM::UCGFSM(const FObjectInitializer& fObj) : Super(fObj)
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UCGFSM::ChangeStateWithClass(TSubclassOf<UCGBaseState> NewStateClass)
{
	if(NewStateClass == nullptr)
	{
		return false;
	}
	
	if(CurrentState != nullptr)
	{
		CurrentState->OnEnterState();
	}

	CurrentState = UCGBaseState::MakeStateWithClass(NewStateClass, GetOwner());
	CurrentState->OnExitState();
	return true;
}

void UCGFSM::BeginPlay()
{
	Super::BeginPlay();
	ChangeStateWithClass(StartState);
}

