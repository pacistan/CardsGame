// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CGFSM.generated.h"

class UCGBaseState;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARDGAME_API UCGFSM : public UActorComponent
{
	GENERATED_UCLASS_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
public:
	
protected:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UCGBaseState> CurrentState;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCGBaseState> StartState;
	
	/* ------------------------------------------ FUNCTIONS -----------------------------------------*/
public:
	UFUNCTION(BlueprintCallable)
	bool ChangeStateWithClass(TSubclassOf<UCGBaseState> NewStateClass);

	
	/* ------------------------------------------ OVERRIDE -----------------------------------------*/
public:

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
