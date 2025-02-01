// Fill out your copyright notice in the Description page of Project Settings.

#include "GyuAssetManager.h"
#include "LyraClone/GyuLogChannels.h"
#include "LyraClone/Character/GyuPawnData.h"
#include "LyraClone/GyuGameplayTags.h"

UGyuAssetManager::UGyuAssetManager()
{
}

UGyuAssetManager& UGyuAssetManager::Get()
{
	check(GEngine);

	if (UGyuAssetManager* Singleton = Cast<UGyuAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}
	
	UE_LOG(LogGyu, Fatal, TEXT("Invalid AssetManager in GameInstance"));
	return *NewObject<UGyuAssetManager>();
}

bool UGyuAssetManager::ShouldLogAssetLoads()
{
	const TCHAR* CommandLineContent = FCommandLine::Get();
	static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

UObject* UGyuAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		TUniquePtr<FScopeLogTime> LogTimePtr;

		if (ShouldLogAssetLoads())
		{
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("Synchronously loaded asset [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}

		if (UAssetManager::IsInitialized())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false);
		}

		// Use LoadObject if asset manager isn't ready yet.
		return AssetPath.TryLoad();
	}

	return nullptr;
}

const UGyuPawnData* UGyuAssetManager::GetDefaultPawnData() const
{
	return GetAsset(DefaultPawnData);
}

void UGyuAssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensureAlways(Asset))
	{
		FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);
		LoadedAssets.Add(Asset);
	}
}

void UGyuAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FGyuGameplayTags::InitializeNativeTags();
}
