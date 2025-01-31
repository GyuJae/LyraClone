// Fill out your copyright notice in the Description page of Project Settings.


#include "GyuPlayerState.h"
#include "LyraClone/GameModes/GyuGameState.h"
#include "LyraClone/GameModes/GyuExperienceManagerComponent.h"
#include "LyraClone/GameModes/GyuExperienceDefinition.h"
#include "LyraClone/GameModes/GyuGameModeBase.h"
#include "LyraClone/GyuLogChannels.h"
#include "LyraClone/Character/GyuPawnData.h"

void AGyuPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	UGyuExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UGyuExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->CallOrRegister_OnExperienceLoaded(FGyuExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
	
}

void AGyuPlayerState::SetPawnData(const UGyuPawnData* InPawnData)
{
	check(InPawnData);
	check(!PawnData);

	PawnData = InPawnData;
}

void AGyuPlayerState::OnExperienceLoaded(const UGyuExperienceDefinition* CurrentExperience)
{
	if (AGyuGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AGyuGameModeBase>())
	{
		if (const UGyuPawnData* NewPawnData = GameMode->GetPawnDataForController(GetOwningController()))
		{
			SetPawnData(NewPawnData);
		}
		else
		{
			UE_LOG(LogGyu, Error, TEXT("ALyraPlayerState::OnExperienceLoaded(): Unable to find PawnData to initialize player state [%s]!"), *GetNameSafe(this));
		}
	}
}
