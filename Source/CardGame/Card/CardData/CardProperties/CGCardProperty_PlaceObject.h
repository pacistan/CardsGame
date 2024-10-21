#pragma once

#include "CoreMinimal.h"
#include "CGCardPropertyBase.h"
#include "CGCardProperty_PlaceObject.generated.h"

UCLASS()
class CARDGAME_API UCGCardProperty_PlaceObject : public UCGCardPropertyBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
	/* ------------------------------------------ METHODS -------------------------------------------*/
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
public:
	virtual bool Behaviors(ACGTile* TargetTile, ACG_PlayerPawn* CardOwner) override;
};
