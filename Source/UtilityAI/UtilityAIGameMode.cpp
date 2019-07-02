// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UtilityAIGameMode.h"
#include "UtilityAIPlayerController.h"
#include "UtilityAICharacter.h"
#include "UObject/ConstructorHelpers.h"

AUtilityAIGameMode::AUtilityAIGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUtilityAIPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}