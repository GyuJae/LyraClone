// Fill out your copyright notice in the Description page of Project Settings.


#include "GyuExperienceManagerComponent.h"

bool UGyuExperienceManagerComponent::IsExperienceLoaded() const
{
	return (LoadState == EGyuExperienceLoadState::Loaded) && (CurrentExperience != nullptr);
}

void UGyuExperienceManagerComponent::CallOrRegister_OnExperienceLoaded(FGyuExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		OnExperienceLoaded.Add(MoveTemp(Delegate));
	}
}
