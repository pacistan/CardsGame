#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CG_DeckData.generated.h"

class UCGCardData_Base;

UCLASS()
class CARDGAME_API UCG_DeckData : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UCGCardData_Base>> Cards;

public:
	UFUNCTION()
	TArray<UCGCardData_Base*> GetCards() {return Cards;}
};
