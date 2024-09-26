// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardPropertyBase.h"
#include "CardProperty_Move.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Move")
class CARDGAME_ICAN_5JV_1_API UCardProperty_Move : public UCardPropertyBase
{
	GENERATED_BODY()
	/* ------------------------------------------ MEMBERS -------------------------------------------*/
protected:
	// TODO : Call the movement of the unit target when activated
	// TODO : Target is a tile ?
	virtual bool Behvaviors() override;
};
