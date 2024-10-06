#include "CGGameMode.h"
#include "CardGame/FSM/CGFSM.h"


ACGGameMode::ACGGameMode(const FObjectInitializer& fObj) : Super(fObj)
{
	m_FSM = CreateDefaultSubobject<UCGFSM>(TEXT("Finite State Machine"));
}

