#include "CGState_DrawPhase.h"
#include "CGState_MainPhase.h"
#include "CG_FSM.h"
#include "CardGame/Player/CGPlayerPawn.h"
#include "CardGame/Macro/CGLogMacro.h"
#include "CardGame/Managers/CGGameMode.h"

void UCGState_DrawPhase::Initialization(ACGGameMode* lGameMode)
{
	Super::Initialization(lGameMode);
	Players = lGameMode->GetPlayerPawn();
	DrawEndDelegate.BindDynamic(this, &UCGState_DrawPhase::OnDrawEnd);
	//DrawEndDelegate.BindUFunction(this, FName("OnDrawEnd"));
}

void UCGState_DrawPhase::OnEnterState()
{
	Super::OnEnterState();
	for(const auto player : Players)
	{
		player->DrawCard(DrawEndDelegate);
	}
}

void UCGState_DrawPhase::OnDrawEnd(ACGPlayerPawn* PlayerPawn)
{
	if(PlayerPawn->GetCurrentHandSize() < PlayerPawn->GetCurrentMaxNumCardToDraw())
	{
		PlayerPawn->DrawCard(DrawEndDelegate);
	}
	else
	{
		if(!Players.Contains(PlayerPawn))
		{
			DEBUG_ERROR("Weird Stuff my dude");
			return;
		}
		Players.Remove(PlayerPawn);
	}
	if(Players.Num() == 0)
	{
		GameMode->GetFSM()->ChangeStateWithClass(UCGState_MainPhase::StaticClass());
	}
}
