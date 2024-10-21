#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Selectable.generated.h"

class ACG_PlayerPawn;

UINTERFACE()
class USelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CARDGAME_API ISelectable
{
	GENERATED_BODY()

public:
	virtual void OnSelect(ACG_PlayerPawn* Pawn) = 0;

	virtual void OnRelease(ACG_PlayerPawn* Pawn) = 0;
};
