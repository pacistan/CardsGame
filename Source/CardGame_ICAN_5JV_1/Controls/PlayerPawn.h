#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class CARDGAME_ICAN_5JV_1_API APlayerPawn : public APawn
{
	GENERATED_BODY()

	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
	
public:
	APlayerPawn();

	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
