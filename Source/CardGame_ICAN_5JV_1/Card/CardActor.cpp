// Fill out your copyright notice in the Description page of Project Settings.


#include "CardActor.h"

#include "Components/WidgetComponent.h"


ACardActor::ACardActor(FObjectInitializer const& ObjectInitializer) : Super(ObjectInitializer)
{
	m_CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	m_CardWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Card Widget"));
}




