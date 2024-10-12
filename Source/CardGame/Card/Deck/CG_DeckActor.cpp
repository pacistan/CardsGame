// Fill out your copyright notice in the Description page of Project Settings.


#include "CG_DeckActor.h"


// Sets default values
ACG_DeckActor::ACG_DeckActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACG_DeckActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACG_DeckActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

