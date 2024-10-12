#include "CG_DeckComponent.h"

#include "CG_DeckData.h"
#include "CardGame/Card/CGCardActor.h"
#include "CardGame/Card/CardData/CGCardData_Base.h"
#include "CardGame/Macro/CGLogMacro.h"


UCG_DeckComponent::UCG_DeckComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

ACGCardActor* UCG_DeckComponent::CreateCard()
{
	if(SelectedDeck == nullptr)
	{
		SelectedDeck = DefaultDeckData.Get();
	}
	const auto CardData = SelectedDeck->GetCards().Last();

	const FActorSpawnParameters SpawnParams;
	const FVector SpawnLocation = FVector(0, 0, 0);
	const FRotator SpawnRotation = FRotator(0, 0, 0);
	
	if(CardData->GetCardType() == FGameplayTag::RequestGameplayTag(FName("TileObject.Type.Unit")))
	{
		return GetWorld()->SpawnActor<ACGCardActor>(CardUnitPrefab, SpawnLocation, SpawnRotation, SpawnParams);
	}
	else if(CardData->GetCardType() == FGameplayTag::RequestGameplayTag(FName("TileObject.Type.Spell")))
	{
		return GetWorld()->SpawnActor<ACGCardActor>(CardSpellPrefab, SpawnLocation, SpawnRotation, SpawnParams);
		
	}
	else if(CardData->GetCardType() == FGameplayTag::RequestGameplayTag(FName("TileObject.Type.Action")))
	{
		return GetWorld()->SpawnActor<ACGCardActor>(CardActionPrefab, SpawnLocation, SpawnRotation, SpawnParams);
		
	}
	else
	{
		DEBUG_ERROR("Wrong Input type for card : %s", CardData->GetCardName());
		return nullptr;
	}
	//CreatedCard->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetIncludingScale);
}


void UCG_DeckComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCG_DeckComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

