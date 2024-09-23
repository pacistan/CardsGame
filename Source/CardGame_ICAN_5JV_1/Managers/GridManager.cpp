#include "GridManager.h"


UGridManager::UGridManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGridManager::BeginPlay()
{
	Super::BeginPlay();
}


void UGridManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

