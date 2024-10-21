#include "CG_PlayerController.h"

#include "CG_PlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CardGame/Card/CGCardActor.h"
#include "CardGame/FSM/States/CGState_MainPhase.h"
#include "CardGame/FSM/States/CG_FSM.h"
#include "CardGame/Interfaces/Clickable.h"
#include "CardGame/Interfaces/Draggable.h"
#include "CardGame/Interfaces/Selectable.h"
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
	if(PlayerPawn == nullptr) return;

	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	
	FHitResult HitResult;
	FVector WorldLocation, WorldDirection;
	DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldLocation, WorldDirection);

	// Do a line trace based on the deprojected location and direction
	FVector TraceEnd = WorldLocation + (WorldDirection * 1000000);
	GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, TraceEnd, ECC_Visibility);
	IHoverable* HoverableActor = Cast<IHoverable>(HitResult.GetActor());
	if (HitResult.bBlockingHit)
	{
		if(HoverableActor)
		{
			if(CurrentHoveredElement.GetInterface() != HoverableActor)
			{
				if(CurrentHoveredElement.GetObject() != nullptr)
				{
					CurrentHoveredElement->OnHoverStop(PlayerPawn);
				}

				CurrentHoveredElement.SetInterface(HoverableActor);
				CurrentHoveredElement.SetObject(HitResult.GetActor());	
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
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, HitResult);

	if (HitResult.bBlockingHit)
	{
		if(const auto Selectable = Cast<ISelectable>(HitResult.GetActor()))
		{
			if(CurrentSelectedElement != nullptr)
			{
				Cast<ISelectable>(CurrentSelectedElement)->OnRelease(PlayerPawn);
			}
			Selectable->OnSelect(PlayerPawn);
			CurrentSelectedElement = HitResult.GetActor();
		}
		if(const auto Draggable = Cast<IDraggable>(HitResult.GetActor()))
		{
			Draggable->OnGrab(PlayerPawn);
			CurrentSelectedElement = HitResult.GetActor();
		}
		if(const auto Clickable = Cast<IClickable>(HitResult.GetActor()))
		{
			Clickable->OnClick(PlayerPawn);
		}
	}
}

void ACG_PlayerController::OnDragCard()
{
	//GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Drag Card"));
	if (CurrentDraggedElement != nullptr)
	{
		float x;
		float y;
		GetMousePosition(x, y);
		FVector WorldLocation, WorldDirection;
		DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

		// Calculate the target position
		FVector TargetLocation = WorldLocation + (WorldDirection * DistanceFromCamera);
		Cast<IDraggable>(CurrentDraggedElement)->OnDrag(PlayerPawn, TargetLocation);
	}
}

void ACG_PlayerController::OnReleaseCard()
{
	//GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Release Card"));
	if(CurrentDraggedElement != nullptr)
	{
		Cast<IDraggable>(CurrentDraggedElement)->OnRelease(PlayerPawn);	
	}
	CurrentDraggedElement = nullptr;
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