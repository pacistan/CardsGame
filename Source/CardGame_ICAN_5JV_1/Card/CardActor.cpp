// Fill out your copyright notice in the Description page of Project Settings.


#include "CardActor.h"

#include "CardData/CardData_Base.h"
#include "CardData/CardProperties/CardPropertyBase.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/GameState.h"


ACardActor::ACardActor(FObjectInitializer const& ObjectInitializer) : Super(ObjectInitializer)
{
	m_CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	m_CardWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Card Widget"));
}

void ACardActor::OnSelected()
{
	TObjectPtr<UCardData_Base> CardData = m_CardData.Get();
	if (!IsValid(CardData)) {
		return;
	}

	TObjectPtr<UCardPropertyBase> CardProperty = CardData->GetCardProperty();
	if (!IsValid(CardProperty)) {
		return;
	}
}

void ACardActor::OnDeselected()
{
	
}

void ACardActor::OnCardPlayed()
{
	// TODO : Check If the card is Play During Player turn or During resolution phase
	if (!IsValid(GetWorld())) {
		return;
	}
	AGameState
	 GetWorld()->GetGameState();
}






