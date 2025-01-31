// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GyuGameModeBase.generated.h"

class UGyuExperienceDefinition;

/**
 * 
 */
UCLASS()
class LYRACLONE_API AGyuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGyuGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override; 
	virtual void InitGameState() override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;


protected: 
	void HandleMatchAssignmentIfNotExpectingOne();

	void OnExperienceLoaded(const UGyuExperienceDefinition* CurrentExperience);

	bool IsExperienceLoaded() const;
};
