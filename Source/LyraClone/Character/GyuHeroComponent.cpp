// Fill out your copyright notice in the Description page of Project Settings.


#include "GyuHeroComponent.h"

UGyuHeroComponent::UGyuHeroComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}
