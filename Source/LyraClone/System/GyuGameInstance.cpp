// Fill out your copyright notice in the Description page of Project Settings.


#include "GyuGameInstance.h"
#include "Components/GameFrameworkComponentManager.h"
#include "LyraClone/GyuGameplayTags.h"

void UGyuGameInstance::Init()
{
	Super::Init();

	// Register our custom init states
	UGameFrameworkComponentManager* ComponentManager = GetSubsystem<UGameFrameworkComponentManager>(this);

	if (ensure(ComponentManager))
	{
		const FGyuGameplayTags& GameplayTags = FGyuGameplayTags::Get();

		ComponentManager->RegisterInitState(GameplayTags.InitState_Spawned, false, FGameplayTag());
		ComponentManager->RegisterInitState(GameplayTags.InitState_DataAvailable, false, GameplayTags.InitState_Spawned);
		ComponentManager->RegisterInitState(GameplayTags.InitState_DataInitialized, false, GameplayTags.InitState_DataAvailable);
		ComponentManager->RegisterInitState(GameplayTags.InitState_GameplayReady, false, GameplayTags.InitState_DataInitialized);
	}
}

void UGyuGameInstance::Shutdown()
{
	Super::Shutdown();
}
