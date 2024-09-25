#include "Tile.h"


ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATile::BlueprintEditorTick(float DeltaTime)
{
	if(m_IsActive != m_IsActiveChecker)
	{
		m_MeshComponent = FindComponentByClass<UStaticMeshComponent>();
		if (m_MeshComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No StaticMeshComponent found on %s"), *GetName());
			return;
		}
		if(m_IsActive)
		{
			SetActorHiddenInGame(false);
			m_MeshComponent->SetMaterial(0, m_ActiveMaterial.Get());
		}
		else
		{
			SetActorHiddenInGame(true);
			m_MeshComponent->SetMaterial(0, m_InactiveMaterial.Get());
		}
	}
	m_IsActiveChecker = m_IsActive;
	
}

void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ATile::ShouldTickIfViewportsOnly() const
{
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor && m_UseEditorTick)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
#if WITH_EDITOR
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}
#endif
}

