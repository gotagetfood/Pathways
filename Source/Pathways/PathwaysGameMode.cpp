// Copyright Epic Games, Inc. All Rights Reserved.

#include "PathwaysGameMode.h"
#include "PathwaysCharacter.h"
#include "UObject/ConstructorHelpers.h"

APathwaysGameMode::APathwaysGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
