#pragma once

#include "CoreMinimal.h"
#include "CardGame/Card/CGCardActor.h"
#include "CardGame/FSM/States/CGState_DrawPhase.h"
#include "CardGame/Macro/CGGetSetMacro.h"
#include "GameFramework/Pawn.h"
#include "CGPlayerPawn.generated.h"

class AStaticMeshActor;
class ACGCardActor;
class UCG_DeckComponent;
class UInputMappingContext;
class UInputAction;
class UCGState_DrawPhase;
class FOnDrawEnd;


UCLASS()
class CARDGAME_API ACGPlayerPawn : public APawn
{
	GENERATED_BODY()

	
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	float DistanceFromCamera;
	
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UCG_DeckComponent> DeckComponent;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	int32 DefaultMaxNumCardToDraw;

	UPROPERTY()
	int32 CurrentMaxNumCardToDraw;

	UPROPERTY()
	FVector DeckActorLocation;
	
	UPROPERTY()
	TArray<TObjectPtr<ACGCardActor>> PlayerHand;

	UPROPERTY()
	TArray<int32> PlayedCardIndexs;

	UPROPERTY()
	int32 SelectedCardIndex;
	
	/* ------------------------------------------ FUNCTIONS -------------------------------------------*/
	
public:
	ACGPlayerPawn();

	UFUNCTION()
	void DrawCard(const FOnDrawEnd& DrawEndDelegate);

	DECLARE_GETTER(CurrentMaxNumCardToDraw, CurrentMaxNumCardToDraw, int32);
	DECLARE_GETTER(DistanceFromCamera, DistanceFromCamera, float);

	int32 GetCardIndex(ACGCardActor* Card)
	{
		if(PlayerHand.Contains(Card))
		{
			for(int i =0; i < PlayerHand.Num(); i++)
			{
				if(Card == PlayerHand[i]) return i;
			}
		}
		return -1;
	}

	int32 GetCurrentHandSize() const { return PlayerHand.Num();}

	UFUNCTION()
	void RemoveCardFromHand(ACGCardActor* Card) { if(PlayerHand.Contains(Card)) PlayerHand.Remove(Card);}

	UFUNCTION()
	void UpdateCards()
	{
		for(const auto& Card : PlayerHand)
		{
			Card->InitiateMovement();
		}
	}

	UFUNCTION()
	void UnplayCard(ACGCardActor* Card)
	{
		int32 CardIndex = GetCardIndex(Card);
		bool isCardFound = false;
		for(int i = 0; i < PlayedCardIndexs.Num(); i++)
		{
			if(i > PlayedCardIndexs.Num()) break;
			if(!isCardFound && PlayedCardIndexs[i] == CardIndex)
			{
				isCardFound = true;
				PlayerHand[PlayedCardIndexs[i]]->RemoveCardFromPlayArray();
				PlayedCardIndexs.RemoveAt(i);
				i--;
			}
			else if(isCardFound)
			{
				PlayerHand[PlayedCardIndexs[i]]->RemoveCardFromPlayArray();
				PlayedCardIndexs.RemoveAt(i);
				i--;
			}
		}
		if(PlayedCardIndexs.Contains(CardIndex))
		{
			PlayedCardIndexs.Remove(CardIndex);
		}
	}
	
	UFUNCTION()
	void PlayCard()
	{
		if(SelectedCardIndex >= 0 && SelectedCardIndex < PlayerHand.Num())
		{
			PlayerHand[SelectedCardIndex]->OnCardPlayed();
			PlayedCardIndexs.Add(SelectedCardIndex);
			SelectedCardIndex = -1;
		}
	}

	UFUNCTION()
	void SelectCard(ACGCardActor* Card)
	{
		if(SelectedCardIndex >= 0 && SelectedCardIndex < PlayerHand.Num())
		{
			PlayerHand[SelectedCardIndex]->OnUnselect();
		}
		SelectedCardIndex = GetCardIndex(Card);
	}
	
protected:


	UFUNCTION(Server, Reliable, WithValidation)
	void RegisterPlayerToGameMode();
	
	/* ------------------------------------------ OVERRIDES -------------------------------------------*/
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
