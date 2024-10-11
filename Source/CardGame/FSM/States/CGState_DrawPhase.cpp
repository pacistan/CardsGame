#include "CGState_DrawPhase.h"
#include "CGState_MainPhase.h"
#include "CG_FSM.h"
#include "CardGame/Controls/CG_PlayerPawn.h"
#include "CardGame/Macro/CGLogMacro.h"
#include "CardGame/Managers/CGGameMode.h"

void UCGState_DrawPhase::Initialization(ACGGameMode* GameMode)
{
	Super::Initialization(GameMode);
	m_Players = m_GameMode->GetPlayerPawn();
	m_DrawEndDelegate.BindUFunction(this, FName("OnDrawEnd"));
}

void UCGState_DrawPhase::OnEnterState()
{
	Super::OnEnterState();
	for(const auto player : m_Players)
	{
		player->DrawCard(m_DrawEndDelegate);
	}
}

void UCGState_DrawPhase::OnDrawEnd(ACG_PlayerPawn* PlayerPawn)
{
	if(!PlayerPawn->IsDrawing() && PlayerPawn->GetHand().Num() < PlayerPawn->GetCurrentMaxNumCardToDraw())
	{
		PlayerPawn->DrawCard(m_DrawEndDelegate);
	}
	else if(!PlayerPawn->IsDrawing() && PlayerPawn->GetHand().Num() >= PlayerPawn->GetCurrentMaxNumCardToDraw())
	{
		if(!m_Players.Contains(PlayerPawn))
		{
			DEBUG_ERROR("Weird Stuff my dude");
			return;
		}
		m_Players.Remove(PlayerPawn);
	}
	if(m_Players.Num() == 0)
	{
		m_GameMode->GetFSM()->ChangeStateWithClass(UCGState_MainPhase::StaticClass());
		return;
	}
}
