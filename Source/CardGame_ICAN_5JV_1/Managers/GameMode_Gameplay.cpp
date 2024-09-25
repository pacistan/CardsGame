#include "GameMode_Gameplay.h"
#include "GridManager.h"
#include "ShaderPrintParameters.h"
#include "CardGame_ICAN_5JV_1/FSM/FSM_Gameplay.h"


AGameMode_Gameplay::AGameMode_Gameplay(const FObjectInitializer& fObj) : Super(fObj)
{
	m_FSM = CreateDefaultSubobject<UFSM_Gameplay>(TEXT("Finite State Machine"));
}

