// Fill out your copyright notice in the Description page of Project Settings.


#include "GyuGameModeBase.h"
#include "GyuGameState.h"
#include "LyraClone/Player/GyuPlayerController.h"
#include "LyraClone/Player/GyuPlayerState.h"
#include "LyraClone/Character/GyuCharacter.h"
#include "GyuExperienceManagerComponent.h"
#include "LyraClone/GyuLogChannels.h"

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

void AGyuGameModeBase::InitGameState()
{
	Super::InitGameState();

	UGyuExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UGyuExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->CallOrRegister_OnExperienceLoaded(FGyuExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void AGyuGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
}

APawn* AGyuGameModeBase::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	UE_LOG(LogGyu, Warning, TEXT("SpawnDefaultPawnAtTransform_Implementation is called!"));
	return Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
}

void AGyuGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{
	FPrimaryAssetId ExperienceId;

	UWorld* World = GetWorld();

	if (!ExperienceId.IsValid())
	{
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType("GyuExperienceDefinition"), FName("B_GyuDefaultExperience"));
	}

	OnMatchAssignmentGiven(ExperienceId);

}

void AGyuGameModeBase::OnExperienceLoaded(const UGyuExperienceDefinition* CurrentExperience)
{
}

bool AGyuGameModeBase::IsExperienceLoaded() const
{
	check(GameState);
	UGyuExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UGyuExperienceManagerComponent>();
	check(ExperienceComponent);

	return ExperienceComponent->IsExperienceLoaded();
}

void AGyuGameModeBase::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId)
{
	UGyuExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UGyuExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->SetCurrentExperience(ExperienceId);
}
