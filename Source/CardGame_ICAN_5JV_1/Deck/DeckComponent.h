// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeckComponent.generated.h"


class ACardActor;
class UCardData_Base;
class UDeckData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARDGAME_ICAN_5JV_1_API UDeckComponent : public UActorComponent
{
	GENERATED_BODY()
	
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UDeckData> m_DefaultDeckData;

	UPROPERTY()
	TArray<TObjectPtr<UCardData_Base>> m_Cards;

	UPROPERTY()
	TSubclassOf<ACardActor> m_CardUnitPrefab;

	UPROPERTY()
	TSubclassOf<ACardActor> m_CardSpellPrefab;

	UPROPERTY()
	TSubclassOf<ACardActor> m_CardActionPrefab;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	UDeckComponent();

	UFUNCTION()
	bool CreateCard(ACardActor* CreatedCard);
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;
};
