#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Clickable.generated.h"

class ACG_PlayerPawn;

UINTERFACE()
class UClickable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CARDGAME_API IClickable
{
	GENERATED_BODY()

public:
	virtual void OnClick(ACG_PlayerPawn* Pawn) = 0;
};
