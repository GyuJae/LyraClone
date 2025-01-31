// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GyuGameState.generated.h"

class UGyuExperienceManagerComponent;

/**
 * 
 */
UCLASS()
class LYRACLONE_API AGyuGameState : public AGameStateBase
{
	GENERATED_BODY()

public: 
	AGyuGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:
	// Handles loading and managing the current gameplay experience
	UPROPERTY()
	TObjectPtr<UGyuExperienceManagerComponent> ExperienceManagerComponent;
};
