#include "CGGameMode.h"
#include "CardGame/FSM/States/CG_FSM.h"


ACGGameMode::ACGGameMode(const FObjectInitializer& fObj) : Super(fObj)
{
	FSM = CreateDefaultSubobject<UCG_FSM>(TEXT("FSM"), false);
	FSM->Initialize(this);
}

void ACGGameMode::BeginPlay()
{
	Super::BeginPlay();
	Players = *new TArray<TObjectPtr<ACG_PlayerPawn>>;
}

void ACGGameMode::RegisterPlayerPawn(ACG_PlayerPawn* Player)
{
	Players.Add(Player);
}
