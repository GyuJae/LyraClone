// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraClone.h"
#include "Modules/ModuleManager.h"
#include "GyuLogChannels.h"

class FGyuGameModule : public FDefaultGameModuleImpl
{
public: 
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FGyuGameModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
	UE_LOG(LogGyu, Warning, TEXT("StartupModule!!"));
}

void FGyuGameModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
}

// IMPLEMENT_PRIMARY_GAME_MODULE �������� �Ѱ���!!
// IMPLEMENT_MODULE�� ���� �Ѱ� �����ؾ���
IMPLEMENT_PRIMARY_GAME_MODULE(FGyuGameModule, LyraClone, "LyraClone" );


