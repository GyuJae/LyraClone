// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraClone.h"
#include "Modules/ModuleManager.h"

class FGyuGameModule : public FDefaultGameModuleImpl
{
public: 
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FGyuGameModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
	UE_LOG(LogTemp, Warning, TEXT("StartupModule!!"));
}

void FGyuGameModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
}

// IMPLEMENT_PRIMARY_GAME_MODULE 엔진에서 한개만!!
// IMPLEMENT_MODULE은 모듈당 한개 존재해야함
IMPLEMENT_PRIMARY_GAME_MODULE(FGyuGameModule, LyraClone, "LyraClone" );


