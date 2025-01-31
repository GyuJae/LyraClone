// Fill out your copyright notice in the Description page of Project Settings.


#include "GyuGameModeBase.h"
#include "GyuGameState.h"
#include "LyraClone/Player/GyuPlayerController.h"
#include "LyraClone/Player/GyuPlayerState.h"
#include "LyraClone/Character/GyuCharacter.h"

AGyuGameModeBase::AGyuGameModeBase()
{
	GameStateClass = AGyuGameState::StaticClass();
	PlayerControllerClass = AGyuPlayerController::StaticClass();
	PlayerStateClass = AGyuPlayerState::StaticClass();
	DefaultPawnClass = AGyuCharacter::StaticClass();
}

void AGyuGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// Wait for the next frame to give time to initialize startup settings
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void AGyuGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{
}
