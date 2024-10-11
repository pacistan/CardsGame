// Fill out your copyright notice in the Description page of Project Settings.


#include "CGCardActor.h"

#include "CardData/CGCardData_Base.h"
#include "CardData/CardProperties/CGCardPropertyBase.h"
#include "Components/WidgetComponent.h"


ACGCardActor::ACGCardActor(FObjectInitializer const& ObjectInitializer) : Super(ObjectInitializer)
{
	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	CardWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Card Widget"));
}

void ACGCardActor::OnSelected()
{
	const TObjectPtr<UCGCardData_Base> lCardData = CardData.Get();
	if (!IsValid(lCardData)) {
		return;
	}

	const TObjectPtr<UCGCardPropertyBase> CardProperty = lCardData->GetCardProperty();
	if (!IsValid(CardProperty)) {
		return;
	}
}

void ACGCardActor::OnDeselected()
{
	
}

void ACGCardActor::OnCardPlayed()
{
	// TODO : Check If the card is Play During Player turn or During resolution phase
	if (!IsValid(GetWorld())) {
		return;
	}
	// TODO : get State of the Game
}






