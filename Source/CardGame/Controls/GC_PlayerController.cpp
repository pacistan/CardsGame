#include "GC_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CardGame/Card/CGCardActor.h"

void AGC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_SelectCard, ETriggerEvent::Triggered, this, &AGC_PlayerController::OnSelectCard);
		EnhancedInputComponent->BindAction(IA_DragCard, ETriggerEvent::Ongoing, this, &AGC_PlayerController::OnDragCard);
		EnhancedInputComponent->BindAction(IA_ReleaseCard, ETriggerEvent::Completed, this, &AGC_PlayerController::OnReleaseCard);
	}
}

void AGC_PlayerController::OnSelectCard()
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
		}
	}
}

void AGC_PlayerController::OnDragCard()
{
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Drag Card"));
	//	DEBUG_LOG_SCREEN_SIMPLE(TEXT("DragCard"));
	if (IsValid(SelectedCard))
	{
		const FVector NewLocation = GetMouseLocationInWorld();
		SelectedCard->SetActorLocation(NewLocation);
	}
}

void AGC_PlayerController::OnReleaseCard()
{
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Release Card"));
	//DEBUG_LOG_SCREEN_SIMPLE(TEXT("ReleaseCard"));
	SelectedCard = nullptr;
}

FVector AGC_PlayerController::GetMouseLocationInWorld() const
{
	FVector WorldLocation, WorldDirection;
	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	const FVector NewLocation = WorldLocation + (WorldDirection * DistanceFromCamera);
	return NewLocation;
}

void AGC_PlayerController::AddDefaultMappingContext() const
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(IMC_Default, 0);
	}
}

void AGC_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	AddDefaultMappingContext();
}