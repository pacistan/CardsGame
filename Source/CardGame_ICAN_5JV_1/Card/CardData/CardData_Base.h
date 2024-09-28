// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CardGame_ICAN_5JV_1/Macro/GetSetMacro.h"
#include "Engine/DataAsset.h"
#include "CardData_Base.generated.h"

class UCardPropertyBase;

/**
 * 
 */
UCLASS()
class CARDGAME_ICAN_5JV_1_API UCardData_Base : public UDataAsset
{
	GENERATED_BODY()
	// TODO : find a way to add condition of target for each cards (ex : target a tile, target a unit, target a player)
	/* ------------------------------------------ MEMBERS ------------------------------------------- */
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Card Name", AssetRegistrySearchable)
	FName m_CardName;

	UPROPERTY(EditAnywhere, DisplayName = "Card Description")
	FString m_CardDescription;
	
	UPROPERTY(EditAnywhere, DisplayName = "Card Image")
	TSoftObjectPtr<UTexture2D> m_CardImage;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseCardCost;

	/* 1 By default on All Card */
	UPROPERTY(EditAnywhere, DisplayName = "Card Cost", meta = (EditCondition = "bUseCardCost"))
	int m_CardCost = 1; 

	/* The priority of the card, the higher the value, the higher the priority */
	UPROPERTY(EditAnywhere, DisplayName = "Card Priority")
	int m_CardPriority;
	
	UPROPERTY(EditAnywhere, DisplayName = "Card Type", AssetRegistrySearchable)
	FGameplayTag m_CardType;

	UPROPERTY(EditAnywhere, DisplayName = "Card Properties", Instanced , AssetRegistrySearchable)
	TObjectPtr<UCardPropertyBase> m_CardProperty;
	
	/* ------------------------------------------ METHODS ------------------------------------------- */
public:
	
	DECLARE_GETTER(CardName,m_CardName, FName);
	DECLARE_GETTER(CardDescription,m_CardDescription,FString);
	DECLARE_GETTER(CardImage,m_CardImage,TSoftObjectPtr<UTexture2D>);
	DECLARE_GETTER(CardCost,m_CardCost,int);
	DECLARE_GETTER(CardPriority,m_CardPriority,int);
	DECLARE_GETTER(CardType,m_CardType,FGameplayTag);
	DECLARE_GETTER(CardProperty,m_CardProperty,TObjectPtr<UCardPropertyBase>);
};
