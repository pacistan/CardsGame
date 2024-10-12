#pragma once

#include "CoreMinimal.h"
#include "CGBaseState.h"
#include "CGState_ResolvePhase.generated.h"

UCLASS()
class CARDGAME_API UCGState_ResolvePhase : public UCGBaseState
{
	GENERATED_BODY()

	virtual void OnEnterState() override;
};
