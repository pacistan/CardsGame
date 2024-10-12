#include "CGState_MainPhase.h"

#include "CGState_ResolvePhase.h"
#include "CG_FSM.h"
#include "CardGame/Managers/CGGameMode.h"

void UCGState_MainPhase::OnEnterState()
{
	Super::OnEnterState();
}

void UCGState_MainPhase::OnTurnEnd() const
{
	GameMode->GetFSM()->ChangeStateWithClass(UCGState_ResolvePhase::StaticClass());
}
