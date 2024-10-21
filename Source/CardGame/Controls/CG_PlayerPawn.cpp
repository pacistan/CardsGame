#include "CG_PlayerPawn.h"
#include "CardGame/Card/CGCardActor.h"
#include "CardGame/Card/CardData/CGCardData_Base.h"
#include "CardGame/Card/CardData/CardProperties/CGCardProperty_Summon.h"
#include "CardGame/Card/Deck/CG_DeckActor.h"
#include "CardGame/Card/Deck/CG_DeckComponent.h"
#include "CardGame/FSM/States/CGState_DrawPhase.h"
#include "CardGame/GameplayElements/CGTile.h"
#include "CardGame/GameplayElements/TileObject/CGTileObjectBase.h"
#include "CardGame/Managers/CGGameMode.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ACG_PlayerPawn::ACG_PlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	DeckComponent = CreateDefaultSubobject<UCG_DeckComponent>(TEXT("Deck"));
}

void ACG_PlayerPawn::DrawCard(const FOnDrawEnd& DrawEndDelegate)
{
	if(GetWorld())
	{
		const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		const FVector CameraLocation = CameraManager->GetCameraLocation();
		const FRotator CameraRotation = CameraManager->GetCameraRotation();
		const FRotator StartRotator = UKismetMathLibrary::FindLookAtRotation(CameraLocation + (CameraRotation.Vector() * DistanceFromCamera), CameraLocation);
		auto newCard = DeckComponent->CreateCard(DeckActorLocation, StartRotator);
		if(newCard == nullptr) return;
		PlayerHand.Add(newCard);
		for(int i = 0; i < PlayerHand.Num() - 1; i++ )
		{
			PlayerHand[i]->InitiateMovement();
		}
		newCard->InitiateMovement(false, this, DrawEndDelegate);
	}
}

void ACG_PlayerPawn::RegisterPlayerToGameMode_Implementation()
{
	if (HasAuthority())
	{
		Cast<ACGGameMode>(GetWorld()->GetAuthGameMode())->RegisterPlayerPawn(this);
	}
}

bool ACG_PlayerPawn::RegisterPlayerToGameMode_Validate()
{
	return true;
}

void ACG_PlayerPawn::PlayCard(ACGTile* Tile)
{
	const auto Card = PlayerHand[SelectedCardIndex]->GetCardData().Get();

	if(Card == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No card Data"));
		return;
	}
	if(Card->GetCardType() == FGameplayTag::RequestGameplayTag(FName("TileObject.Type.Unit")))
	{
		Tile->SummonOnTile(Card->GetUnitToSpawn(), this);
	}

	
	if(SelectedCardIndex >= 0 && SelectedCardIndex < PlayerHand.Num())
	{
		PlayerHand[SelectedCardIndex]->OnCardPlayed();
		PlayedCardIndexs.Add(SelectedCardIndex);
		SelectedCardIndex = -1;
	}
}

void ACG_PlayerPawn::SelectCard(ACGCardActor* Card)
{
	if(SelectedCardIndex >= 0 && SelectedCardIndex < PlayerHand.Num())
	{
		PlayerHand[SelectedCardIndex]->OnUnselect();
	}
	SelectedCardIndex = GetCardIndex(Card);
}

void ACG_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerHand = *new TArray<ACGCardActor*>();
	PlayerHand.Reserve(5);
	CurrentMaxNumCardToDraw = DefaultMaxNumCardToDraw;
	DeckActorLocation = Cast<ACGGameMode>(GetWorld()->GetAuthGameMode())->GetDeck(0)->GetActorLocation();
	PlayedCardIndexs = TArray<int32>();
	PlayedCardIndexs.Reserve(5);
}

void ACG_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


