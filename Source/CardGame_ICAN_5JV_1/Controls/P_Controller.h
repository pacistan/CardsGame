#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P_Controller.generated.h"

class UInputMappingContext;
class UInputAction;
class ACardActor;

UCLASS()
class CARDGAME_ICAN_5JV_1_API AP_Controller : public APlayerController
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/

public:

	UPROPERTY(EditAnywhere,Category = "PlayerPawn|Input", meta=(DisplayName = "Card Distance from Camera"))
	float m_DistanceFromCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Default Mapping Context"))
	UInputMappingContext* m_IMC_Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Left Click Press Action"))
	UInputAction* m_IA_SelectCard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Left Click Drag Action"))
	UInputAction* m_IA_DragCard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Left Click Release Action"))
	UInputAction* m_IA_ReleaseCard;

	UPROPERTY()
	TObjectPtr<ACardActor> m_SelectedCard;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
private:
	UFUNCTION()
	void OnSelectCard();

	UFUNCTION()
	void OnDragCard();

	UFUNCTION()
	void OnReleaseCard();
	FVector GetMouseLocationInWorld();

	UFUNCTION()
	void AddDefaultMappingContext();

	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
};
