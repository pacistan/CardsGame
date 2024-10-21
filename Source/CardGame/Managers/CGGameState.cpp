// Fill out your copyright notice in the Description page of Project Settings.


#include "CGGameState.h"

#include "EngineUtils.h"
#include "CardGame/Player/CG_PlayerController.h"
#include "CardGame/Macro/CGLogMacro.h"
#include "CardGame/Player/CGPlayerStart.h"
#include "Engine/PlayerStartPIE.h"
#include "GameFramework/PlayerStart.h"
#include "Net/UnrealNetwork.h"

extern ENGINE_API float GAverageFPS;

ACGGameState::ACGGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	ServerFPS = 0.0f;
}

void ACGGameState::AddPlayerToMap(TObjectPtr<ACG_PlayerController> PlayerController, TObjectPtr<ACGPlayerStart> PlayerSpawn)
{
	if (!HasAuthority()) {
		return;
	}
	
	if (SpawnOfPlayerMap.Contains(PlayerController)) {
		return;
	}
	
	SpawnOfPlayerMap.Add(PlayerController, PlayerSpawn);
}

AActor* ACGGameState::ChoosePlayerStart(AController* Player)
{
	if (Player) {
#if WITH_EDITOR
		if (APlayerStart* PlayerStart = FindPlayFromHereStart(Player)) {
			return PlayerStart;
		}
#endif
		TArray<ACGPlayerStart*> StarterPoints;
		for (auto StartIt = CachedPlayerStarts.CreateIterator(); StartIt; ++StartIt) {
			if (ACGPlayerStart* Start = (*StartIt).Get()) {
				StarterPoints.Add(Start);
			} else {
				StartIt.RemoveCurrent();
			}
		}

		AActor* PlayerSpawn = GetFirstRandomUnoccupiedPlayerStart(Player, StarterPoints);

		if (ACGPlayerStart* CGPlayerSpawn = Cast<ACGPlayerStart>(PlayerSpawn)){
			CGPlayerSpawn->TryClaim(Player);
		}

		return PlayerSpawn;
	}

	return nullptr;
}


void ACGGameState::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	// TODO Call back for blueprint 
}

#if WITH_EDITOR
APlayerStart* ACGGameState::FindPlayFromHereStart(AController* Player)
{
	// Only 'Play From Here' for a player controller, bots etc. should all spawn from normal spawn points.
	if (Player->IsA<APlayerController>()) {
		if (UWorld* World = GetWorld()) {
			for (TActorIterator<APlayerStart> It(World); It; ++It){
				if (APlayerStart* PlayerStart = *It) {
					if (PlayerStart->IsA<APlayerStartPIE>()) {
						// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode
						return PlayerStart;
					}
				}
			}
		}
	}

	return nullptr;
}
#endif

void ACGGameState::HandleOnActorSpawned(AActor* SpawnedActor)
{
	if (ACGPlayerStart* PlayerStart = Cast<ACGPlayerStart>(SpawnedActor)) {
		CachedPlayerStarts.Add(PlayerStart);
	}
}

APlayerStart* ACGGameState::GetFirstRandomUnoccupiedPlayerStart(AController* Controller, const TArray<ACGPlayerStart*>& FoundStartPoints) const
{
	if (Controller) {
		TArray<ACGPlayerStart*> UnOccupiedStartPoints;

		for (ACGPlayerStart* StartPoint : FoundStartPoints) {
			if (!StartPoint->IsClaimed()) {
				UnOccupiedStartPoints.Add(StartPoint);
			}
		}

		if (UnOccupiedStartPoints.Num() > 0) {
			return UnOccupiedStartPoints[FMath::RandRange(0, UnOccupiedStartPoints.Num() - 1)];
		} 
	}

	return nullptr;
}

void ACGGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, ServerFPS);
}

void ACGGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetLocalRole() == ROLE_Authority) {
		ServerFPS = GAverageFPS;
	}
}

void ACGGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if(UWorld* World = GetWorld())
	{
		World->AddOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateUObject(this, &ThisClass::HandleOnActorSpawned));
		for (TActorIterator<ACGPlayerStart> It(World); It; ++It) {
			if (ACGPlayerStart* PlayerStart = *It){
				CachedPlayerStarts.Add(PlayerStart);
			}
		}
	}
}
