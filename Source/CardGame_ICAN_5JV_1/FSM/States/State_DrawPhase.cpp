// Fill out your copyright notice in the Description page of Project Settings.


#include "State_DrawPhase.h"

#include "State_MainPhase.h"
#include "CardGame_ICAN_5JV_1/Controls/PlayerPawn.h"
#include "CardGame_ICAN_5JV_1/FSM/FSM_Gameplay.h"
#include "CardGame_ICAN_5JV_1/Macro/LogMacro.h"
#include "CardGame_ICAN_5JV_1/Managers/GameMode_Gameplay.h"

void UState_DrawPhase::Initialization(AGameMode_Gameplay* GameMode)
{
	Super::Initialization(GameMode);
	m_Players = m_GameMode->GetPlayerPawn();
	m_DrawEndDelegate.BindUFunction(this, FName("OnDrawEnd"));
}

void UState_DrawPhase::OnEnterState()
{
	Super::OnEnterState();
	for(auto player : m_Players)
	{
		player->DrawCard(m_DrawEndDelegate);
	}
}

void UState_DrawPhase::OnDrawEnd(APlayerPawn* PlayerPawn)
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
		m_GameMode->GetFSM()->ChangeStateWithClass(UState_MainPhase::StaticClass());
		return;
	}
}


