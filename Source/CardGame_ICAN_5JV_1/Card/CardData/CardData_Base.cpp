// Fill out your copyright notice in the Description page of Project Settings.


#include "CardData_Base.h"

#include "CardProperties/CardPropertyBase.h"
#include "Kismet/GameplayStatics.h"

UCardPropertyBase* UCardData_Base::GetCardPropertyByClass(TSubclassOf<UCardPropertyBase> cardPropertyClass)
{
	for (UCardPropertyBase* cardProperty : m_CardProperties) {
		if (cardProperty->GetClass() == cardPropertyClass) {
			return cardProperty;
		}
	}
	return nullptr;
}
