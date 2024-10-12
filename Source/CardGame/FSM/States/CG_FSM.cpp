#include "CG_FSM.h"
#include "CGBaseState.h"
#include "CardGame/Managers/CGGameMode.h"
#include "DSP/Delay.h"


UCG_FSM::UCG_FSM()
{
}

void UCG_FSM::Initialize(ACGGameMode* GameMode)
{
	Owner = GameMode;
	FTimerHandle TimerHandle;
	const auto TimerDel = FTimerDelegate::CreateLambda([this, GameMode]()
	{
		ChangeStateWithClass(GameMode->GetStartState());
	});
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, .1f, false);
	//ChangeStateWithClass(GameMode->GetStartState());
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
