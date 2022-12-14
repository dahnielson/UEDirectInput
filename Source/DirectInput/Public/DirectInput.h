/* 
 * Copyright (c) 2022 Anders Dahnielson <anders@dahnielson.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of 
 * this software and associated documentation files (the "Software"), to deal in the 
 * Software without restriction, including without limitation the rights to use, copy, 
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, subject to the 
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
