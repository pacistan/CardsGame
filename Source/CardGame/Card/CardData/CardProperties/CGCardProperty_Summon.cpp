#include "CGCardProperty_Summon.h"

#include "CardGame/GameplayElements/CGTile.h"
#include "CardGame/Macro/CGLogMacro.h"

bool UCGCardProperty_Summon::Behaviors(ACGTile* TargetTile, ACG_PlayerPawn* CardOwner)
{
	if (!IsValid(TargetTile) || !IsValid(CardOwner)) {
		DEBUG_LOG_SCREEN_SIMPLE("Target Tile or PawnOwner is not valid");
		return false;
	}
	
	if (!TargetTile->CanSummonOnTile(CardOwner)) {
		DEBUG_WARNING("%s Can't summon on the tile %s", *CardOwner->GetName(), *TargetTile->GetName());
		return false;
	}
	
	TargetTile->SummonOnTile(CardObjectClassToSummon, CardOwner);
	return Super::Behaviors(TargetTile, CardOwner);
}
