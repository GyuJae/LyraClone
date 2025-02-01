// Fill out your copyright notice in the Description page of Project Settings.


#include "GyuGameModeBase.h"
#include "GyuGameState.h"
#include "LyraClone/Player/GyuPlayerController.h"
#include "LyraClone/Player/GyuPlayerState.h"
#include "LyraClone/Character/GyuCharacter.h"
#include "GyuExperienceManagerComponent.h"
#include "LyraClone/GyuLogChannels.h"
#include "LyraClone/Character/GyuPawnData.h"
#include "GyuExperienceDefinition.h"
#include "LyraClone/System/GyuAssetManager.h"
#include "LyraClone/Character/GyuPawnExtensionComponent.h"


AGyuGameModeBase::AGyuGameModeBase()
{
	GameStateClass = AGyuGameState::StaticClass();
	PlayerControllerClass = AGyuPlayerController::StaticClass();
	PlayerStateClass = AGyuPlayerState::StaticClass();
	DefaultPawnClass = AGyuCharacter::StaticClass();
}

const UGyuPawnData* AGyuGameModeBase::GetPawnDataForController(const AController* InController) const
{
	// See if pawn data is already set on the player state
	if (InController != nullptr)
	{
		if (const AGyuPlayerState* LyraPS = InController->GetPlayerState<AGyuPlayerState>())
		{
			if (const UGyuPawnData* PawnData = LyraPS->GetPawnData<UGyuPawnData>())
			{
				return PawnData;
			}
		}
	}

	// If not, fall back to the the default for the current experience
	check(GameState);
	UGyuExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UGyuExperienceManagerComponent>();
	check(ExperienceComponent);

	if (ExperienceComponent->IsExperienceLoaded())
	{
		const UGyuExperienceDefinition* Experience = ExperienceComponent->GetCurrentExperienceChecked();
		if (Experience->DefaultPawnData != nullptr)
		{
			return Experience->DefaultPawnData;
		}

		// Experience is loaded and there's still no pawn data, fall back to the default for now
		return UGyuAssetManager::Get().GetDefaultPawnData();
	}

	// Experience not loaded yet, so there is no pawn data to be had
	return nullptr;
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

UClass* AGyuGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (const UGyuPawnData* PawnData = GetPawnDataForController(InController))
	{
		if (PawnData->PawnClass)
		{
			return PawnData->PawnClass;
		}
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
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
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// Never save the default player pawns into a map.
	SpawnInfo.bDeferConstruction = true;

	if (UClass* PawnClass = GetDefaultPawnClassForController(NewPlayer))
	{
		if (APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnInfo))
		{
			if (UGyuPawnExtensionComponent* PawnExtComp = UGyuPawnExtensionComponent::FindPawnExtensionComponent(SpawnedPawn))
			{
				if (const UGyuPawnData* PawnData = GetPawnDataForController(NewPlayer))
				{
					PawnExtComp->SetPawnData(PawnData);
				}
				else
				{
					UE_LOG(LogGyu, Error, TEXT("Game mode was unable to set PawnData on the spawned pawn [%s]."), *GetNameSafe(SpawnedPawn));
				}
			}

			SpawnedPawn->FinishSpawning(SpawnTransform);

			return SpawnedPawn;
		}
		else
		{
			UE_LOG(LogGyu, Error, TEXT("Game mode was unable to spawn Pawn of class [%s] at [%s]."), *GetNameSafe(PawnClass), *SpawnTransform.ToHumanReadableString());
		}
	}
	else
	{
		UE_LOG(LogGyu, Error, TEXT("Game mode was unable to spawn Pawn due to NULL pawn class."));
	}

	return nullptr;
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
	// Spawn any players that are already attached
	//@TODO: Here we're handling only *player* controllers, but in GetDefaultPawnClassForController_Implementation we skipped all controllers
	// GetDefaultPawnClassForController_Implementation might only be getting called for players anyways
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Cast<APlayerController>(*Iterator);
		if ((PC != nullptr) && (PC->GetPawn() == nullptr))
		{
			if (PlayerCanRestart(PC))
			{
				RestartPlayer(PC);
			}
		}
	}
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
