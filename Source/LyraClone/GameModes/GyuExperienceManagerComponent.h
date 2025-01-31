// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "GyuExperienceManagerComponent.generated.h"

class UGyuExperienceDefinition;

DECLARE_MULTICAST_DELEGATE_OneParam(FGyuExperienceLoaded, const UGyuExperienceDefinition* /*Experience*/);

enum class EGyuExperienceLoadState
{
	Unloaded,
	Loading,
	Loaded,
	Deactivating
};

/**
 * 
 */
UCLASS()
class LYRACLONE_API UGyuExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()

public:
	// Returns true if the experience is fully loaded
	bool IsExperienceLoaded() const;

	// Ensures the delegate is called once the experience has been loaded
// If the experience has already loaded, calls the delegate immediately
	void CallOrRegister_OnExperienceLoaded(FGyuExperienceLoaded::FDelegate&& Delegate);
	
private:
	UPROPERTY()
	TObjectPtr<const UGyuExperienceDefinition> CurrentExperience;

	EGyuExperienceLoadState LoadState = EGyuExperienceLoadState::Unloaded;

	/** Delegate called when the experience has finished loading */
	FGyuExperienceLoaded OnExperienceLoaded;


};
