// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheRoomGameMode.h"
#include "TheRoomCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheRoomGameMode::ATheRoomGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
