#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HoverableInterface.generated.h"


class ACGPlayerPawn;

UINTERFACE()
class UHoverableInterface : public UInterface
{
	GENERATED_BODY()
};


class CARDGAME_API IHoverableInterface
{
	GENERATED_BODY()

public:
	virtual void OnHoverStart(ACGPlayerPawn* Pawn) = 0;

	virtual void OnHoverStop(ACGPlayerPawn* Pawn) = 0;
	
	virtual void OnSelect(ACGPlayerPawn* Pawn) = 0;
	
	virtual void OnExamine(ACGPlayerPawn* Pawn) = 0;

	virtual void OnDrag(ACGPlayerPawn* Pawn, FVector MousePosition) = 0;
	
	virtual void OnRelease(ACGPlayerPawn* Pawn) = 0;
};
