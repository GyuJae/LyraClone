// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GyuPawnData.generated.h"

/**
 * 
 */
UCLASS()
class LYRACLONE_API UGyuPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public: 
	UGyuPawnData(const FObjectInitializer& ObjectInitializer);

public:
	// Pawn Class.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gyu|Pawn")
	TSubclassOf<APawn> PawnClass;
};
