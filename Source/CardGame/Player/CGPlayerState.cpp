// Fill out your copyright notice in the Description page of Project Settings.


#include "CGPlayerState.h"

#include "CGPlayerPawn.h"
#include "CG_PlayerController.h"
#include "CardGame/Macro/CGLogMacro.h"
#include "CardGame/Managers/CGGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

ACGPlayerState::ACGPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Player State need to be updtate at high frequency 
	NetUpdateFrequency = 100.0f;
}

ACG_PlayerController* ACGPlayerState::GetCGPlayerController() const
{
	return Cast<ACG_PlayerController>(GetOwner());
}

void ACGPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, PawnClass, SharedParams);
}

void ACGPlayerState::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ACGPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	UWorld* World = GetWorld();
	if (World && World->IsGameWorld() && World->GetNetMode() != NM_Client) {
		AGameStateBase* GameState = GetWorld()->GetGameState();
		check(GameState);
		if (ACGGameMode* CGGameMode = GetWorld()->GetAuthGameMode<ACGGameMode>()) {
			if (const TSubclassOf<ACGPlayerPawn> NewPawnClass = CGGameMode->GetPawnClassForController(GetOwningController())) {
				SetPawnClass(NewPawnClass);
			} else {
				DEBUG_ERROR("ACGPlayerState::PostInitializeComponents(): Unable to find PawnClass to initialize player state [%s]!", *GetNameSafe(this));
			}
		}
	}
}

void ACGPlayerState::SetPawnClass(const TSubclassOf<ACGPlayerPawn> InPawnClass)
{
	check(InPawnClass);
	if (!HasAuthority()) {
		return;
	}
	
	if (PawnClass) {
		DEBUG_ERROR("Trying to set PawnClass [%s] on player state [%s] that already has valid PawnClass [%s].", *GetNameSafe(InPawnClass), *GetNameSafe(this), *GetNameSafe(PawnClass));
		return;
	}
	
	// MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, PawnClass, this);
	PawnClass = InPawnClass;
	
	ForceNetUpdate();
}


