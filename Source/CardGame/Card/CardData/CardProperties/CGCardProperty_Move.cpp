#include "CGCardProperty_Move.h"


bool UCGCardProperty_Move::Behvaviors(ACGTile* TargetTile, ACG_PlayerPawn* CardOwner)
{
	// TODO : Check if the target tile is valid
	return Super::Behaviors(TargetTile, CardOwner);
}
