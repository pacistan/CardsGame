// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardActor.generated.h"

class UWidgetComponent;
class UCardData_Base;

UCLASS()
class CARDGAME_ICAN_5JV_1_API ACardActor : public AActor
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Card Mesh")
	UStaticMeshComponent* m_CardMesh;

	UPROPERTY(EditAnywhere, DisplayName = "Card Widget")
	UWidgetComponent* m_CardWidget;
	
	UPROPERTY(EditInstanceOnly, DisplayName = "Card Data")
	TSoftClassPtr<UCardData_Base> m_CardData;

	UPROPERTY(EditInstanceOnly, DisplayName = "Card Owner")
	TObjectPtr<APawn> m_CardOwner;
	
	/* ------------------------------------------ METHODS -------------------------------------------*/
public:

	
	
};
