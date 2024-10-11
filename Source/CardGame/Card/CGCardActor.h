// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGCardActor.generated.h"

class UWidgetComponent;
class UStaticMeshComponent;
class UCGCardData_Base;

UCLASS()
class CARDGAME_API ACGCardActor : public AActor
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Card Mesh")
	UStaticMeshComponent* CardMesh;

	UPROPERTY(EditAnywhere, DisplayName = "Card Widget")
	UWidgetComponent* CardWidget;
	
	UPROPERTY(EditInstanceOnly, DisplayName = "Card Data")
	TSoftObjectPtr<UCGCardData_Base> CardData;

	UPROPERTY(EditInstanceOnly, DisplayName = "Card Owner")
	TObjectPtr<APawn> CardOwner;
	
	/* ------------------------------------------ METHODS -------------------------------------------*/
public:
	ACGCardActor(FObjectInitializer const& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void OnSelected();

	UFUNCTION(BlueprintCallable)
	void OnDeselected();

	UFUNCTION(BlueprintCallable)
	void OnCardPlayed();
};
