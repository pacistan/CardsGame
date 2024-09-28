// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FSM_Gameplay.generated.h"

class UBaseState;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARDGAME_ICAN_5JV_1_API UFSM_Gameplay : public UActorComponent
{
	GENERATED_UCLASS_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
public:
	
protected:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UBaseState> m_CurrentState;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBaseState> m_StartState;
	
	/* ------------------------------------------ FUNCTIONS -----------------------------------------*/
public:
	UFUNCTION(BlueprintCallable)
	bool ChangeStateWithClass(TSubclassOf<UBaseState> NewStateClass);

	
	/* ------------------------------------------ OVERRIDE -----------------------------------------*/
public:

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
