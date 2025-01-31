// Fill out your copyright notice in the Description page of Project Settings.


#include "GyuGameState.h"
#include "GyuExperienceManagerComponent.h"

AGyuGameState::AGyuGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ExperienceManagerComponent = CreateDefaultSubobject<UGyuExperienceManagerComponent>(TEXT("ExperienceManagerComponent"));

}
