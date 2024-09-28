// Fill out your copyright notice in the Description page of Project Settings.


#include "CardProperty_Summon.h"

#include "CardGame_ICAN_5JV_1/GameplayElements/Tile.h"
#include "CardGame_ICAN_5JV_1/Macro/LogMacro.h"

bool UCardProperty_Summon::Behvaviors(ATile* TargetTile, APawn* CardOwner)
{
	if (!IsValid(TargetTile) || !IsValid(CardOwner)) {
		DEBUG_LOG_SCREEN_SIMPLE("Target Tile or PawnOwner is not valid");
		return false;
	}
	
	if (!TargetTile->CanSummonOnTile(CardOwner)) {
		DEBUG_WARNING("%s Can't summon on the tile %s", *CardOwner->GetName(), *TargetTile->GetName());
		return false;
	}
	
	TargetTile->SummonOnTile(m_CardObjectClassToSummon, CardOwner);
	return Super::Behvaviors(TargetTile, CardOwner);
}
