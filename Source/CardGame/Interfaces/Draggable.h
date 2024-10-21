#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Draggable.generated.h"

class ACG_PlayerPawn;

UINTERFACE()
class UDraggable : public UInterface
{
	GENERATED_BODY()
};


class CARDGAME_API IDraggable
{
	GENERATED_BODY()

public:
	virtual void OnGrab(ACG_PlayerPawn* Pawn) = 0;
	
	virtual void OnDrag(ACG_PlayerPawn* Pawn, FVector MousePosition) = 0;
	
	virtual void OnRelease(ACG_PlayerPawn* Pawn) = 0;
	
};
