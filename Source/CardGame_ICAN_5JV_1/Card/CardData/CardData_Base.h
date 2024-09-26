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
	/* ------------------------------------------ MEMBERS ------------------------------------------- */
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Card Name")
	FName m_CardName;

	UPROPERTY(EditAnywhere, DisplayName = "Card Description")
	FString m_CardDescription;
	
	UPROPERTY(EditAnywhere, DisplayName = "Card Image")
	UTexture2D* m_CardImage;
	
	UPROPERTY(EditAnywhere, DisplayName = "Card Cost")
	int m_CardCost;

	UPROPERTY(EditAnywhere, DisplayName = "Card Priority")
	int m_CardPriority;
	
	UPROPERTY(EditAnywhere, DisplayName = "Card Type", AssetRegistrySearchable)
	FGameplayTag m_CardType;

	UPROPERTY(EditAnywhere, DisplayName = "Card Properties", Instanced ,AssetRegistrySearchable)
	TArray<UCardPropertyBase*> m_CardProperties;
	
	/* ------------------------------------------ METHODS ------------------------------------------- */
public:
	
	DECLARE_GETTER(CardName,m_CardName, FName);
	DECLARE_GETTER(CardDescription,m_CardDescription,FString);
	DECLARE_GETTER(CardImage,m_CardImage,UTexture2D*);
	DECLARE_GETTER(CardCost,m_CardCost,int);
	DECLARE_GETTER(CardPriority,m_CardPriority,int);
	DECLARE_GETTER(CardType,m_CardType,FGameplayTag);
	DECLARE_GETTER(CardProperties,m_CardProperties,TArray<UCardPropertyBase*>);

	/* return nullptr if the property dosen't exist */
	UFUNCTION(BlueprintCallable)
	UCardPropertyBase* GetCardPropertyByClass(TSubclassOf<UCardPropertyBase> cardPropertyClass);
};
