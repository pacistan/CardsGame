#include "P_Controller.h"
#include "EnhancedInputComponent.h"
#include "CardGame_ICAN_5JV_1/Card/CardActor.h"
#include "CardGame_ICAN_5JV_1/Macro/LogMacro.h"

void AP_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(m_IA_SelectCard, ETriggerEvent::Triggered, this, &AP_Controller::OnSelectCard);
		EnhancedInputComponent->BindAction(m_IA_DragCard, ETriggerEvent::Ongoing, this, &AP_Controller::OnDragCard);
		EnhancedInputComponent->BindAction(m_IA_ReleaseCard, ETriggerEvent::Completed, this, &AP_Controller::OnReleaseCard);
	}
}

void AP_Controller::OnSelectCard()
{
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Select Card"));
	//	DEBUG_LOG_SCREEN_SIMPLE(TEXT("SelectCard"));
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, HitResult);

	if (HitResult.bBlockingHit)
	{
		ACardActor* HitCard = Cast<ACardActor>(HitResult.GetActor());
		if (HitCard)
		{
			m_SelectedCard = HitCard;
		}
	}
}

void AP_Controller::OnDragCard()
{
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Drag Card"));
	//	DEBUG_LOG_SCREEN_SIMPLE(TEXT("DragCard"));
	if (IsValid(m_SelectedCard))
	{
		FVector NewLocation = GetMouseLocationInWorld();
		m_SelectedCard->SetActorLocation(NewLocation);
	}
}

void AP_Controller::OnReleaseCard()
{
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("Release Card"));
	//DEBUG_LOG_SCREEN_SIMPLE(TEXT("ReleaseCard"));
	m_SelectedCard = nullptr;
}

FVector AP_Controller::GetMouseLocationInWorld()
{
	FVector WorldLocation, WorldDirection;
	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FVector NewLocation = WorldLocation + (WorldDirection * m_DistanceFromCamera);
	return NewLocation;
}
