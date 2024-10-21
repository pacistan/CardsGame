// Fill out your copyright notice in the Description page of Project Settings.


#include "CGPlayerStart.h"


bool ACGPlayerStart::IsClaimed() const
{
	return ClaimingController != nullptr;
}

bool ACGPlayerStart::TryClaim(AController* OccupyingController)
{
	if (OccupyingController != nullptr && !IsClaimed()) {
		ClaimingController = OccupyingController;
		return true;
	}
	return false;
}

