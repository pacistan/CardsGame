// Fill out your copyright notice in the Description page of Project Settings.


#include "DeckComponent.h"

#include "CardGame_ICAN_5JV_1/Card/CardActor.h"
#include "CardGame_ICAN_5JV_1/Card/CardData/CardData_Base.h"
#include "CardGame_ICAN_5JV_1/Macro/LogMacro.h"


UDeckComponent::UDeckComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UDeckComponent::CreateCard(ACardActor* CreatedCard)
{
	auto CardData = m_Cards.Last().Get();

	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation = FVector(0, 0, 0);
	FRotator SpawnRotation = FRotator(0, 0, 0);
	
	if(CardData->GetCardType() == FGameplayTag::RequestGameplayTag(FName("Card.Type.Unit")))
	{
		CreatedCard = GetWorld()->SpawnActor<ACardActor>(m_CardUnitPrefab, SpawnLocation, SpawnRotation, SpawnParams);
		
	}
	else if(CardData->GetCardType() == FGameplayTag::RequestGameplayTag(FName("Card.Type.Spell")))
	{
		CreatedCard = GetWorld()->SpawnActor<ACardActor>(m_CardSpellPrefab, SpawnLocation, SpawnRotation, SpawnParams);
		
	}
	else if(CardData->GetCardType() == FGameplayTag::RequestGameplayTag(FName("Card.Type.Action")))
	{
		CreatedCard = GetWorld()->SpawnActor<ACardActor>(m_CardActionPrefab, SpawnLocation, SpawnRotation, SpawnParams);
		
	}
	else
	{
		DEBUG_ERROR("Wrong Input type for card : %s", CardData->GetCardName());
		return false;
	}
	CreatedCard->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetIncludingScale);

	return true;
}


void UDeckComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDeckComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

