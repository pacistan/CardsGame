#pragma once

#include "CoreMinimal.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "GameFramework/GameModeBase.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "CGGameMode.generated.h"

class ACG_DeckActor;
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

	UPROPERTY()
	TArray<TObjectPtr<ACG_DeckActor>> Decks;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCGBaseState> StartState;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	void RegisterPlayerPawn(ACG_PlayerPawn* Player);
	
	DECLARE_GETTER(FSM, FSM, TObjectPtr<UCG_FSM>);
	DECLARE_GETTER(PlayerPawn, Players, TArray<TObjectPtr<ACG_PlayerPawn>>);
	DECLARE_GETTER(StartState, StartState, TSubclassOf<UCGBaseState>);

	ACG_DeckActor* GetDeck(int PlayerIndex)
	{
		if(!Decks.IsEmpty() && Decks.Num() > 0)
			return Decks[PlayerIndex];
		return nullptr;
	}

	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
	virtual void BeginPlay() override;
	
};
