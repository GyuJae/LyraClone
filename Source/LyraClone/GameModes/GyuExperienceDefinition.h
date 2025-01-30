// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GyuExperienceDefinition.generated.h"

class UGyuPawnData;

/**
 * 
 */
UCLASS()
class LYRACLONE_API UGyuExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UGyuExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// List of Game Feature Plugins this experience wants to have active
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<FString> GameFeaturesToEnable;

	/** The default pawn class to spawn for players */
	//@TODO: Make soft?
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TObjectPtr<const UGyuPawnData> DefaultPawnData;
};
