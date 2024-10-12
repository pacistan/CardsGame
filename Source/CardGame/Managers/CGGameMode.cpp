#include "CGGameMode.h"

#include "CardGame/Controls/CG_PlayerPawn.h"
#include "CardGame/FSM/States/CG_FSM.h"
#include "Kismet/GameplayStatics.h"


ACGGameMode::ACGGameMode(const FObjectInitializer& fObj) : Super(fObj)
{

}

void ACGGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACG_PlayerPawn::StaticClass(), PlayerActors);

	Players.SetNum(PlayerActors.Num());
	for(int i = 0; i < PlayerActors.Num(); i++)
	{
		Players[i] = Cast<ACG_PlayerPawn>(PlayerActors[i]);
	}
	
	FSM = NewObject<UCG_FSM>(this);
	FSM->Initialize(this);
}

void ACGGameMode::RegisterPlayerPawn(ACG_PlayerPawn* Player)
{
	Players.Add(Player);
}
