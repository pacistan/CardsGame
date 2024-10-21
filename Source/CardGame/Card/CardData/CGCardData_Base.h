// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "Engine/DataAsset.h"
#include "CGCardData_Base.generated.h"

class ACGTileObjectBase;
class UCGCardPropertyBase;

/**
 * 
 */
UCLASS()
class CARDGAME_API UCGCardData_Base : public UDataAsset
{
	GENERATED_BODY()
	// TODO : find a way to add condition of target for each cards (ex : target a tile, target a unit, target a player)
	/* ------------------------------------------ MEMBERS ------------------------------------------- */
protected:
		UPROPERTY(EditAnywhere, DisplayName = "Card Name", AssetRegistrySearchable)
	FName CardName;

	UPROPERTY(EditAnywhere, DisplayName = "Card Description")
	FString CardDescription;
	
	UPROPERTY(EditAnywhere, DisplayName = "Card Image")
	TSoftObjectPtr<UTexture2D> CardImage;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseCardCost;

	/* 1 By default on All Card */
	UPROPERTY(EditAnywhere, DisplayName = "Card Cost", meta = (EditCondition = "bUseCardCost"))
	int CardCost = 1; 

	/* The priority of the card, the higher the value, the higher the priority */
	UPROPERTY(EditAnywhere, DisplayName = "Card Priority")
	int CardPriority;
	
	UPROPERTY(EditAnywhere, DisplayName = "Card Type", AssetRegistrySearchable)
	FGameplayTag CardType;

	UPROPERTY(EditAnywhere, DisplayName = "Card Properties", Instanced , AssetRegistrySearchable)
	TObjectPtr<UCGCardPropertyBase> CardProperty;

	UPROPERTY(EditAnywhere, DisplayName = "Unit to Spawn", AssetRegistrySearchable)
	TSubclassOf<ACGTileObjectBase> UnitToSpawn;
	
	/* ------------------------------------------ METHODS ------------------------------------------- */
public:

	
	DECLARE_GETTER(CardName,CardName, FName);
	DECLARE_GETTER(CardDescription,CardDescription,FString);
	DECLARE_GETTER(CardImage,CardImage,TSoftObjectPtr<UTexture2D>);
	DECLARE_GETTER(CardCost,CardCost,int);
	DECLARE_GETTER(CardPriority,CardPriority,int);
	DECLARE_GETTER(CardType,CardType,FGameplayTag);
	DECLARE_GETTER(CardProperty,CardProperty,TObjectPtr<UCGCardPropertyBase>);
	DECLARE_GETTER(UnitToSpawn, UnitToSpawn, TSubclassOf<ACGTileObjectBase>);
};
