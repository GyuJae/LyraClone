// Fill out your copyright notice in the Description page of Project Settings.


#include "GyuPlayerState.h"
#include "LyraClone/GameModes/GyuGameState.h"
#include "LyraClone/GameModes/GyuExperienceManagerComponent.h"
#include "LyraClone/GameModes/GyuExperienceDefinition.h"

void AGyuPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	UGyuExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UGyuExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->CallOrRegister_OnExperienceLoaded(FGyuExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
	
}

void AGyuPlayerState::OnExperienceLoaded(const UGyuExperienceDefinition* CurrentExperience)
{
}
