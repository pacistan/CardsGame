// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class CARDGAME_ICAN_5JV_1_API APlayerPawn : public APawn
{
	GENERATED_BODY()

	/* ------------------------------------------ MEMBERS -------------------------------------------*/

	/** Default MappingContext */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Default Mapping Context"))
	UInputMappingContext* m_IMC_Default;

	/** Left Click Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Left Click Action"))
	UInputAction* m_IA_SelectCard;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
private:
	UFUNCTION()
	void OnLeftClick();
	
public:
	APlayerPawn();
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
