#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CG_FSM.generated.h"

class ACGGameMode;
class UGCBaseState;

UCLASS()
class CARDGAME_API UCG_FSM : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<UCGBaseState> CurrentState;

	UPROPERTY()
	TObjectPtr<ACGGameMode> Owner;

	/* ------------------------------------------ FUNCTIONS -----------------------------------------*/
public:
	UCG_FSM();

	UFUNCTION()
	void Initialize(ACGGameMode* GameMode);
	
	UFUNCTION(BlueprintCallable)
	bool ChangeStateWithClass(TSubclassOf<UCGBaseState> NewStateClass);

	TObjectPtr<UCGBaseState> GetCurrentState() const {return CurrentState;}
	
	UFUNCTION()
	void Tick(float DeltaTime) const;

};
