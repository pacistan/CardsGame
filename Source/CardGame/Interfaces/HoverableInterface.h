#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HoverableInterface.generated.h"


class ACG_PlayerPawn;

UINTERFACE()
class UHoverableInterface : public UInterface
{
	GENERATED_BODY()
};


class CARDGAME_API IHoverableInterface
{
	GENERATED_BODY()

public:
	virtual void OnHoverStart(ACG_PlayerPawn* Pawn) = 0;

	virtual void OnHoverStop(ACG_PlayerPawn* Pawn) = 0;
	
	virtual void OnSelect(ACG_PlayerPawn* Pawn) = 0;
	
	virtual void OnExamine(ACG_PlayerPawn* Pawn) = 0;

	virtual void OnDrag(ACG_PlayerPawn* Pawn, FVector MousePosition) = 0;
	
	virtual void OnRelease(ACG_PlayerPawn* Pawn) = 0;
};
