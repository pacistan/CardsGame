#include "CGCardActor.h"
#include "CardData/CGCardData_Base.h"
#include "CardData/CardProperties/CGCardPropertyBase.h"
#include "CardGame/Controls/CG_PlayerPawn.h"
#include "CardGame/FSM/States/CGState_DrawPhase.h"
#include "CardGame/GameplayElements/CGTile.h"
#include "CardGame/Interfaces/Hoverable.h"
#include "CardGame/Managers/CGGridManager.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


ACGCardActor::ACGCardActor(FObjectInitializer const& ObjectInitializer) : Super(ObjectInitializer)
{
	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	CardWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Card Widget"));
}

void ACGCardActor::OnCardPlayed()
{
	CurrentCardState = ECardState::PLAYED;
	InitiateMovement(true);
	CardMesh->SetMaterial(0, PlayedMat.Get());
}

void ACGCardActor::OnUnselect()
{
	CardMesh->SetMaterial(0, NormalMat.Get());
	CurrentCardState = ECardState::INACTIVE;
	InitiateMovement(true);
}

void ACGCardActor::InitiateMovement(bool IsHoveringOperation, ACG_PlayerPawn* PawnOwner, const FOnDrawEnd& DrawEndDelegate)
{
	if(PawnOwner != nullptr)
		CardOwner = PawnOwner;
	const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	const FVector CameraLocation = CameraManager->GetCameraLocation();
	const FRotator CameraRotation = CameraManager->GetCameraRotation();
	const FVector CameraRightVector = FRotationMatrix(CameraRotation).GetScaledAxis(EAxis::Y);
	const FVector CameraUpVector = FRotationMatrix(CameraRotation).GetScaledAxis(EAxis::Z);

	float HoveredPositionOffset;
	int32 HoveredLayerNumber;
	switch(CurrentCardState)
	{
	case ECardState::INACTIVE:
		EndScale = BaseScale;
		HoveredLayerNumber = CardOwner->GetCardIndex(this);
		HoveredPositionOffset = 0;
		break;
	case ECardState::HOVERED:
		EndScale = BaseScale * HoveredScaleOffset;
		HoveredLayerNumber = 30;
		HoveredPositionOffset = HoveredOffsetZ;
		break;
	case ECardState::SELECTED:
		EndScale = BaseScale * SelectedScaleOffset;
		HoveredLayerNumber = 20;
		HoveredPositionOffset = HoveredOffsetZ;
		break;
	case ECardState::PLAYED:
		EndScale = BaseScale * PlayedScaleOffSet;
		HoveredLayerNumber = 10 + CardOwner->GetCardIndex(this);
		HoveredPositionOffset = HoveredOffsetZ;
		break;
	case ECardState::ISEXAMINED:
		HoveredOffsetZ = 0;
		break;
	}
	
	StartPosition = GetActorLocation();
	StartRotator = GetActorRotation();
	StartScale = GetActorScale();
	
	EndPosition = FVector(CameraLocation + (CameraRotation.Vector() * (CardOwner->GetDistanceFromCamera() - HoveredLayerNumber))
		+ CameraRightVector * CardOwner->GetHandPositionOffset().X
		+ CameraRightVector * CardOffset * CardOwner->GetCardIndex(this)
		- CameraRightVector * CardOffset * (CardOwner->GetCurrentHandSize() - 1) / 2.0f
		+ CameraUpVector * CardOwner->GetHandPositionOffset().Y
		- CameraUpVector * CardHeightOffset * FMath::Abs(CardOwner->GetCardIndex(this) - (CardOwner->GetCurrentHandSize() - 1) / 2.0f)
		- CameraUpVector * HandHeightOffset
		+ CameraUpVector * HoveredPositionOffset);

	EndRotator = StartRotator;
	EndRotator.Roll = FMath::Lerp(
		CardTiltOffset * static_cast<float>(CardOwner->GetCurrentHandSize() - 1) / 2,
		-CardTiltOffset * static_cast<float>(CardOwner->GetCurrentHandSize() - 1) / 2,
		CardOwner->GetCardIndex(this) / static_cast<float>(CardOwner->GetCurrentHandSize() - 1));

	float Duration = IsHoveringOperation ? HoveringTransitionDuration : CardDrawAnimDuration; 
	InterpolationValue = 0;

	
	
	const FTimerDelegate TimerDel = FTimerDelegate::CreateLambda([this, DrawEndDelegate, Duration]()
	{
		DrawAnimTickRate(DrawEndDelegate, Duration);
	});
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, CardDrawAnimRefreshRate, true);
}

void ACGCardActor::RemoveCardFromPlayArray()
{
	CurrentCardState = ECardState::INACTIVE;
	InitiateMovement( true);
	CardMesh->SetMaterial(0, NormalMat.Get());
}

void ACGCardActor::DrawAnimTickRate(const FOnDrawEnd& DrawEndDelegate, float Duration)
{
	if(!GetWorld())
	{
		return;
	}
	InterpolationValue = FMath::Clamp(InterpolationValue +  CardDrawAnimRefreshRate / Duration, 0, 1);
	const FVector newPosition = FMath::Lerp(StartPosition, EndPosition, CardDrawAnimCurve->FloatCurve.Eval(InterpolationValue));
	const FRotator newRotation = FMath::Lerp(StartRotator, EndRotator, CardDrawAnimCurve->FloatCurve.Eval(InterpolationValue));
	const FVector newScale = FMath::Lerp(StartScale, EndScale, CardDrawAnimCurve->FloatCurve.Eval(InterpolationValue));
	
	SetActorLocation(newPosition);
	SetActorRotation(newRotation);
	SetActorScale3D(newScale);
	

	

	if(InterpolationValue >= 1 )
	{
		SetActorLocation(EndPosition);
		SetActorRotation(EndRotator);
		SetActorScale3D(EndScale);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		DrawEndDelegate.ExecuteIfBound(CardOwner);
	}
}

void ACGCardActor::BeginPlay()
{
	Super::BeginPlay();
	BaseScale = GetActorScale();
}

void ACGCardActor::OnHoverStart(ACG_PlayerPawn* Pawn)
{
	if(CurrentCardState == ECardState::INACTIVE)
	{
		CurrentCardState = ECardState::HOVERED;
		InitiateMovement(true);
	}
}

void ACGCardActor::OnHoverStop(ACG_PlayerPawn* Pawn)
{
	if(CurrentCardState == ECardState::HOVERED)
	{
		CurrentCardState = ECardState::INACTIVE;
		InitiateMovement(true);
	}
}

void ACGCardActor::OnSelect(ACG_PlayerPawn* Pawn)
{
	if(CurrentCardState == ECardState::HOVERED)
	{
		CurrentCardState = ECardState::SELECTED;
		InitiateMovement( true);
		CardOwner->SelectCard(this);
		CardMesh->SetMaterial(0, SelectedMat.Get());
		ACGGridManager* GridManager = Cast<ACGGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACGGridManager::StaticClass()));

		ETileType TileType;
		switch(CardOwner->GetPlayerMultIndex())
		{
		case 1:
			TileType = ETileType::Player1;
			break;
		case 2:
			TileType = ETileType::Player2;
			break;
		case 3:
			TileType = ETileType::Player3;
			break;
		case 4:
			TileType = ETileType::Player4;
			break;
		}
		
		GridManager->HighlightTiles(TileType);
	}
	else if(CurrentCardState == ECardState::PLAYED)
	{
		CardOwner->UnplayCard(this);
	}
}

void ACGCardActor::OnRelease(ACG_PlayerPawn* Pawn)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f"), FVector::Distance(GetActorLocation(), AnchorPosition))
	//if(FVector::Distance(GetActorLocation(), AnchorPosition) > 1000)
	//{
	//	CardOwner->RemoveCardFromHand(this);
	//	CardMesh->SetVisibility(false);
	//	CardOwner->UpdateCards();
	//}
	//else
	//{
	//	IsHovered = false;
	//	InitiateMovement(nullptr, FOnDrawEnd(), true);
	//}
}



void ACGCardActor::OnExamine(ACG_PlayerPawn* Pawn)
{
}






