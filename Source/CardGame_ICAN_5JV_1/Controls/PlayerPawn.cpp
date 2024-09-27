#include "PlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CardGame_ICAN_5JV_1/Macro/LogMacro.h"


APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}



void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
