/*
* Track Evolution
* Copyright (c) 2021-2022 Anders Dahnielson. All rights reserved.
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
