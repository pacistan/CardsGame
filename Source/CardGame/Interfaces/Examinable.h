#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Examinable.generated.h"

class ACG_PlayerPawn;

UINTERFACE()
class UExaminable : public UInterface
{
	GENERATED_BODY()
};


class CARDGAME_API IExaminable
{
	GENERATED_BODY()

public:
	virtual void OnExamine(ACG_PlayerPawn* Pawn) = 0;
};
