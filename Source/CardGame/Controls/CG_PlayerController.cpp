#include "CG_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CardGame/Card/CGCardActor.h"
#include "CardGame/FSM/States/CGState_MainPhase.h"
#include "CardGame/FSM/States/CG_FSM.h"
#include "CardGame/Managers/CGGameMode.h"

void ACG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_SelectCard, ETriggerEvent::Triggered, this, &ACG_PlayerController::OnSelectCard);
		EnhancedInputComponent->BindAction(IA_DragCard, ETriggerEvent::Ongoing, this, &ACG_PlayerController::OnDragCard);
		EnhancedInputComponent->BindAction(IA_ReleaseCard, ETriggerEvent::Completed, this, &ACG_PlayerController::OnReleaseCard);
	}
}

void ACG_PlayerController::OnSelectCard()
{
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Select Card"));
	//	DEBUG_LOG_SCREEN_SIMPLE(TEXT("SelectCard"));
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, HitResult);

	if (HitResult.bBlockingHit)
	{
		if (ACGCardActor* HitCard = Cast<ACGCardActor>(HitResult.GetActor()))
		{
			SelectedCard = HitCard;
			const auto GameMode = Cast<ACGGameMode>(GetWorld()->GetAuthGameMode());
			if(GameMode->GetFSM()->GetCurrentState().GetClass() == UCGState_MainPhase::StaticClass())
			{
				Cast<UCGState_MainPhase>(GameMode->GetFSM()->GetCurrentState())->OnTurnEnd();
			}
		}
	}
}

void ACG_PlayerController::OnDragCard()
{
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Drag Card"));
	//	DEBUG_LOG_SCREEN_SIMPLE(TEXT("DragCard"));
	if (IsValid(SelectedCard))
	{
		const FVector NewLocation = GetMouseLocationInWorld();
		SelectedCard->SetActorLocation(NewLocation);
	}
}

void ACG_PlayerController::OnReleaseCard()
{
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Release Card"));
	//DEBUG_LOG_SCREEN_SIMPLE(TEXT("ReleaseCard"));
	SelectedCard = nullptr;
}

FVector ACG_PlayerController::GetMouseLocationInWorld() const
{
	FVector WorldLocation, WorldDirection;
	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	const FVector NewLocation = WorldLocation + (WorldDirection * DistanceFromCamera);
	return NewLocation;
}

void ACG_PlayerController::AddDefaultMappingContext() const
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(IMC_Default, 0);
	}
}

void ACG_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	AddDefaultMappingContext();
}