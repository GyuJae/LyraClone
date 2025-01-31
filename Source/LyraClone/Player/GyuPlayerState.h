// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GyuPlayerState.generated.h"

class UGyuPawnData;
class UGyuExperienceDefinition;

/**
 * 
 */
UCLASS()
class LYRACLONE_API AGyuPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	//~AActor interface
	virtual void PostInitializeComponents() override;

private:
	void OnExperienceLoaded(const UGyuExperienceDefinition* CurrentExperience);

protected:

	UPROPERTY()
	TObjectPtr<const UGyuPawnData> PawnData;
};
