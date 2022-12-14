/*
* Track Evolution
* Copyright (c) 2021-2022 Anders Dahnielson. All rights reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "InputDevice/Public/IInputDevice.h"
#include "InputDevice/Public/IInputDeviceModule.h"

class IDInputDevice : public IInputDevice
{
public:
	IDInputDevice(const TSharedRef<FGenericApplicationMessageHandler> &InMessageHandler);
	virtual ~IDInputDevice() override {};
	
protected:
	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
};

class FDirectInputModule : public IInputDeviceModule
{
	virtual TSharedPtr<class IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler> &InMessageHandler) override;
	TSharedPtr<class IDInputDevice> DirectInputDevice;
	
public:
	TSharedPtr<class IDInputDevice>& GetDirectInputDevice() { return DirectInputDevice; }
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static inline FDirectInputModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FDirectInputModule>("DirectInput");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("DirectInput");
	}
};
