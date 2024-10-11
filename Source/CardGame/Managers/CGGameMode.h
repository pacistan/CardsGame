#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "CGGameMode.generated.h"

class UCGBaseState;
class ACG_PlayerPawn;
class UCG_FSM;
class AGridManager;

UCLASS()
class CARDGAME_API ACGGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UCG_FSM> FSM;

	UPROPERTY()
	TArray<TObjectPtr<ACG_PlayerPawn>> Players;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCGBaseState> StartState;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	DECLARE_GETTER(FSM, FSM, TObjectPtr<UCG_FSM>);
	DECLARE_GETTER(PlayerPawn, Players, TArray<TObjectPtr<ACG_PlayerPawn>>);
	DECLARE_GETTER(StartState, StartState, TSubclassOf<UCGBaseState>);
	
	void RegisterPlayerPawn(ACG_PlayerPawn* Player);

	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
	virtual void BeginPlay() override;
	
};
