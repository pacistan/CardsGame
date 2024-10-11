#include "CG_DeckComponent.h"

#include "CardGame/Card/CGCardActor.h"
#include "CardGame/Card/CardData/CGCardData_Base.h"
#include "CardGame/Macro/CGLogMacro.h"


UCG_DeckComponent::UCG_DeckComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UCG_DeckComponent::CreateCard(ACGCardActor* CreatedCard)
{
	const auto CardData = Cards.Last().Get();

	const FActorSpawnParameters SpawnParams;
	const FVector SpawnLocation = FVector(0, 0, 0);
	const FRotator SpawnRotation = FRotator(0, 0, 0);
	
	if(CardData->GetCardType() == FGameplayTag::RequestGameplayTag(FName("Card.Type.Unit")))
	{
		CreatedCard = GetWorld()->SpawnActor<ACGCardActor>(CardUnitPrefab, SpawnLocation, SpawnRotation, SpawnParams);
		
	}
	else if(CardData->GetCardType() == FGameplayTag::RequestGameplayTag(FName("Card.Type.Spell")))
	{
		CreatedCard = GetWorld()->SpawnActor<ACGCardActor>(CardSpellPrefab, SpawnLocation, SpawnRotation, SpawnParams);
		
	}
	else if(CardData->GetCardType() == FGameplayTag::RequestGameplayTag(FName("Card.Type.Action")))
	{
		CreatedCard = GetWorld()->SpawnActor<ACGCardActor>(CardActionPrefab, SpawnLocation, SpawnRotation, SpawnParams);
		
	}
	else
	{
		DEBUG_ERROR("Wrong Input type for card : %s", CardData->GetCardName());
		return false;
	}
	CreatedCard->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetIncludingScale);

	return true;
}


void UCG_DeckComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCG_DeckComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

