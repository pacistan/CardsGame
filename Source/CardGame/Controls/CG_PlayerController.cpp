#include "CG_PlayerController.h"

#include "CG_PlayerPawn.h"
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

void ACG_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		if(const auto Hoverable = Cast<IHoverableInterface>(HitResult.GetActor()))
		{
			if(CurrentHoveredElement != Hoverable)
			{
				if(CurrentHoveredElement != nullptr)
					CurrentHoveredElement->OnHoverStop(PlayerPawn);
				CurrentHoveredElement = Hoverable;
				CurrentHoveredElement->OnHoverStart(PlayerPawn);
			}
		}
		else
		{
			if(CurrentHoveredElement != nullptr)
			{
				CurrentHoveredElement->OnHoverStop(PlayerPawn);
				CurrentHoveredElement = nullptr;
			}
		}
	}
	else
	{
		if(CurrentHoveredElement != nullptr)
		{
			CurrentHoveredElement->OnHoverStop(PlayerPawn);
			CurrentHoveredElement = nullptr;
		}
	}
}

void ACG_PlayerController::OnSelectCard()
{
	//GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Select Card"));
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, HitResult);

	if (HitResult.bBlockingHit)
	{
		if(const auto Hoverable = Cast<IHoverableInterface>(HitResult.GetActor()))
		{
			Hoverable->OnSelect(PlayerPawn);
			SelectedCard = Hoverable;
		}
	}
}

void ACG_PlayerController::OnDragCard()
{
	//GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Drag Card"));
	if (SelectedCard != nullptr)
	{
		float x;
		float y;
		GetMousePosition(x, y);
		FVector WorldLocation, WorldDirection;
		DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

		// Calculate the target position
		FVector TargetLocation = WorldLocation + (WorldDirection * DistanceFromCamera);
		SelectedCard->OnDrag(PlayerPawn, TargetLocation);
	}
}

void ACG_PlayerController::OnReleaseCard()
{
	//GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Release Card"));
	if(SelectedCard != nullptr)
	{
		SelectedCard->OnRelease(PlayerPawn);	
	}
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
	PlayerPawn = Cast<ACG_PlayerPawn>(GetPawn());
	AddDefaultMappingContext();
	bShowMouseCursor = true;
}