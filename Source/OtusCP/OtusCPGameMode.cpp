// Copyright Epic Games, Inc. All Rights Reserved.

#include "OtusCPGameMode.h"
#include "OtusCPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOtusCPGameMode::AOtusCPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_PlayerController"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = PlayerControllerBPClass.Class;
}
