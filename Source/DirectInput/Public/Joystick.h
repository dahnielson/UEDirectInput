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

#include "Windows/WindowsApplication.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class FJoystick
{
public:
	FJoystick(LPDIRECTINPUTDEVICE8 device);
	~FJoystick() = default;
	void Release() const;

	GUID GetProductGui() const;
	FString GetProductGuidAsString() const;
	FString GetProductName() const;
	
	GUID GetInstanceGuid() const;
	FString GetInstanceGuidAsString() const;
	FString GetInstanceName() const;

	GUID GetForceDriverGuid() const;
	FString GetForceDriverGuidAsString() const;
	
	uint32 GetNumAxes() const { return Capabilities.dwAxes; }
	uint32 GetNumButtons() const { return Capabilities.dwButtons; }
	uint32 GetNumPovs() const { return Capabilities.dwPOVs; }

	bool IsAvailable() const { return Available; }

	bool Poll();

	int32 GetAxisValue(uint32 Axis) const;
	int32 GetButtonValue(uint32 Button) const;
	int32 GetPovValue(uint32 Pov) const;

	bool IsAxisChanged(uint32 Axis) const;
	bool IsButtonChanged(uint32 Button) const;
	bool IsPovChanged(uint32 Pov) const;

	FString GetAxisName(uint32 Axis) const;
	uint32 GetAxisMaxForce(uint32 Axis) const;
	uint32 GetAxisForceResolution(uint32 Axis) const;
	bool IsForceActuator(uint32 Axis) const;

	bool UpdateEffect(int Magnitude);
	
	BOOL EnumerateAxes(LPCDIDEVICEOBJECTINSTANCE ObjectInstance);

private:
	bool TryAcquireDevice();
	bool GetDeviceInfo();
	bool GetCapabilities();
	void GetObjects();

	bool CreateEffect(uint32 Axis);
	bool StopEffect() const;

	LPDIRECTINPUTEFFECT Effect;
	LPDIRECTINPUTDEVICE8 Device;
	DIDEVICEINSTANCE Instance;
	DIDEVCAPS Capabilities;

	bool Available;

	DIJOYSTATE2 CurrentState;
	DIJOYSTATE2 PreviousState;

	DIEFFECT EffectConfig;

	LPCDIDEVICEOBJECTINSTANCE AxisInstances[8];
};
