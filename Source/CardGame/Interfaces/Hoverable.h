#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Hoverable.generated.h"


class ACG_PlayerPawn;

UINTERFACE()
class UHoverable : public UInterface
{
	GENERATED_BODY()
};


class CARDGAME_API IHoverable
{
	GENERATED_BODY()

public:
	virtual void OnHoverStart(ACG_PlayerPawn* Pawn) = 0;

	virtual void OnHoverStop(ACG_PlayerPawn* Pawn) = 0;

};
