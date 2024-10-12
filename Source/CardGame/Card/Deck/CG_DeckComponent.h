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
	TObjectPtr<UCG_DeckData> DefaultDeckData;

	UPROPERTY()
	TObjectPtr<UCG_DeckData> SelectedDeck;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACGCardActor> CardUnitPrefab;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACGCardActor> CardSpellPrefab;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACGCardActor> CardActionPrefab;

	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
public:
	UCG_DeckComponent();

	UFUNCTION()
	ACGCardActor* CreateCard(const FVector& SpawnLocation, const FRotator& SpawnRotation) ;
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;
};
