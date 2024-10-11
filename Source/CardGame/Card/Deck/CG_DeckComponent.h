#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CG_DeckComponent.generated.h"

class ACGCardActor;
class UCGCardData_Base;
class UCG_DeckData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARDGAME_API UCG_DeckComponent : public UActorComponent
{
	GENERATED_BODY()

	/* ------------------------------------------ MEMBERS -------------------------------------------*/
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UCG_DeckData> DefaultDeckData;

	UPROPERTY()
	TArray<TObjectPtr<UCGCardData_Base>> Cards;

	UPROPERTY()
	TSubclassOf<ACGCardActor> CardUnitPrefab;

	UPROPERTY()
	TSubclassOf<ACGCardActor> CardSpellPrefab;

	UPROPERTY()
	TSubclassOf<ACGCardActor> CardActionPrefab;

	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	UCG_DeckComponent();

	UFUNCTION()
	bool CreateCard(ACGCardActor* CreatedCard);
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;
};
