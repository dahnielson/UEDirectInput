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

#include "Joystick.h"

DEFINE_LOG_CATEGORY_STATIC(LogJoystick, Log, All);

static FString GuidToString(const GUID Guid)
{
	WCHAR* WcharGuid = nullptr;
	switch (StringFromCLSID(Guid, &WcharGuid))
	{
	case E_OUTOFMEMORY:
		return TEXT("");
	default:
		break;
	}

	FString StringGuid = WcharGuid;
	CoTaskMemFree(WcharGuid);
	return StringGuid;
}

static HWND GetWindowHandle()
{
	HWND hWnd = nullptr;

	const FWindowsApplication* WindowsApplication = static_cast<FWindowsApplication*>(FSlateApplication::Get().GetPlatformApplication().Get());
	check(WindowsApplication);

	const TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().GetActiveTopLevelWindow();
	if (ParentWindow.IsValid()  && (ParentWindow->GetNativeWindow().IsValid()))
	{
		hWnd = static_cast<HWND>(ParentWindow->GetNativeWindow()->GetOSWindowHandle());
	}

	return hWnd;
}

static BOOL CALLBACK StaticEnumerateAxes(LPCDIDEVICEOBJECTINSTANCE objectInstance, LPVOID pvRef)
{
	const auto Instance = static_cast<FJoystick*>(pvRef);
	return Instance->EnumerateAxes(objectInstance);
}

BOOL FJoystick::EnumerateAxes(LPCDIDEVICEOBJECTINSTANCE ObjectInstance)
{
	UE_LOG(LogJoystick, Display, TEXT("%s 0x%02X, 0x%02X '%s' : %d N / %d, actuator %d"),
		*GuidToString(ObjectInstance->guidType),
		ObjectInstance->wUsagePage,
		ObjectInstance->wUsage,
		ObjectInstance->tszName,
		ObjectInstance->dwFFMaxForce,
		ObjectInstance->dwFFForceResolution,
		ObjectInstance->dwFlags & DIDOI_FFACTUATOR
		);
	
	if (ObjectInstance->wUsagePage == 0x01)
	{
		switch (ObjectInstance->wUsage)
		{
		case 0x30: // X
			AxisInstances[0] = ObjectInstance;
			break;
		case 0x31: // Y
			AxisInstances[1] = ObjectInstance;
			break;
		case 0x32: // Z
			AxisInstances[2] = ObjectInstance;
			break;
		case 0x33: // Rx
			AxisInstances[3] = ObjectInstance;
			break;
		case 0x34: // Ry
			AxisInstances[4] = ObjectInstance;
			break;
		case 0x35: // Rz
			AxisInstances[5] = ObjectInstance;
			break;
		case 0x36: // Slider
			AxisInstances[6] = ObjectInstance;
			break;
		case 0x37: // Dial
			AxisInstances[7] = ObjectInstance;
			break;
		default:
			UE_LOG(LogJoystick, Warning, TEXT("Unknown axis 0x%02X"), ObjectInstance->wUsage);
			break;
		}
	}
	else
	{
		UE_LOG(LogJoystick, Warning, TEXT("Unsupported HID page 0x%02X, usage 0x%02X"), ObjectInstance->wUsagePage, ObjectInstance->wUsage);		
	}

	return DIENUM_CONTINUE;
}

FJoystick::FJoystick(LPDIRECTINPUTDEVICE8 device) :
	Device(device),
	Available(false)
{
	ZeroMemory(&Instance, sizeof(DIDEVICEINSTANCE));
	ZeroMemory(&Capabilities, sizeof(DIDEVCAPS));
	ZeroMemory(&CurrentState, sizeof(DIJOYSTATE2));
	ZeroMemory(&PreviousState, sizeof(DIJOYSTATE2));

	Instance.dwSize = sizeof(DIDEVICEINSTANCE);
	Capabilities.dwSize = sizeof(DIDEVCAPS);

	if (TryAcquireDevice())
	{
		GetDeviceInfo();
		GetCapabilities();
		GetObjects();
		CreateEffect(0);
	}

	UE_LOG(LogJoystick, Display, TEXT("%s %s has %d axes, %d buttons and %d POVs"), *GetInstanceName(), *GetInstanceGuidAsString(), GetNumAxes(), GetNumButtons(), GetNumPovs());
}

void FJoystick::Release() const
{
	Device->Unacquire();
	Effect->Release();
	Device->Release();
}

GUID FJoystick::GetProductGui() const
{
	return Instance.guidProduct;
}

FString FJoystick::GetProductGuidAsString() const
{
	return GuidToString(Instance.guidProduct);
}

FString FJoystick::GetProductName() const
{
	return FString(Instance.tszProductName);
}

GUID FJoystick::GetInstanceGuid() const
{
	return Instance.guidInstance;
}

FString FJoystick::GetInstanceGuidAsString() const
{
	return GuidToString(Instance.guidInstance);
}

FString FJoystick::GetInstanceName() const
{
	return FString(Instance.tszInstanceName);
}

GUID FJoystick::GetForceDriverGuid() const
{
	return Instance.guidFFDriver;
}

FString FJoystick::GetForceDriverGuidAsString() const
{
	return GuidToString(Instance.guidFFDriver);
}

bool FJoystick::TryAcquireDevice()
{
	Device->Unacquire();

	switch (Device->SetCooperativeLevel(GetWindowHandle(), DISCL_BACKGROUND | DISCL_EXCLUSIVE))
	{
	case DIERR_INVALIDPARAM:
		UE_LOG(LogJoystick, Error, TEXT("SetCooperativeLevel: Invalid parameter"));
		break;
	case DIERR_NOTINITIALIZED:
		UE_LOG(LogJoystick, Error, TEXT("SetCooperativeLevel: Not initialized"));
		break;
	case E_HANDLE:
		UE_LOG(LogJoystick, Error, TEXT("SetCooperativeLevel: Handle"));
		break;
	default:
		break;
	}

	switch (Device->SetDataFormat(&c_dfDIJoystick2))
	{
	case DIERR_ACQUIRED:
		UE_LOG(LogJoystick, Error, TEXT("SetDataFormat: Acquired"));
		break;
	case DIERR_INVALIDPARAM:
		UE_LOG(LogJoystick, Error, TEXT("SetDataFormat: Invalid parameter"));
		break;
	case DIERR_NOTINITIALIZED:
		UE_LOG(LogJoystick, Error, TEXT("SetDataFormat: Not initialized"));
		break;
	default:
		break;
	}

	switch (Device->Acquire())
	{
	case DIERR_INVALIDPARAM:
		UE_LOG(LogJoystick, Error, TEXT("Acquire: Invalid parameter"));
		Available = false;
		return false;
	case DIERR_NOTINITIALIZED:
		UE_LOG(LogJoystick, Error, TEXT("Acquire: Not initialized"));
		Available = false;
		return false;
	case DIERR_OTHERAPPHASPRIO:
		UE_LOG(LogJoystick, Error, TEXT("Acquire: Other application has priority"));
		Available = false;
		return false;
	default:
		Available = true;
		return true;
	}
}

bool FJoystick::GetDeviceInfo()
{
	switch (Device->GetDeviceInfo(&Instance))
	{
	case DIERR_INVALIDPARAM:
		UE_LOG(LogJoystick, Error, TEXT("GetDeviceInfo: Invalid parameter"));
		return false;
	case DIERR_NOTINITIALIZED:
		UE_LOG(LogJoystick, Error, TEXT("GetDeviceInfo: Not initialized"));
		return false;
	case E_POINTER:
		UE_LOG(LogJoystick, Error, TEXT("GetDeviceInfo: Pointer"));
		return false;
	default:
		return true;
	}
}

bool FJoystick::GetCapabilities()
{
	switch (Device->GetCapabilities(&Capabilities))
	{
	case DIERR_INVALIDPARAM:
		UE_LOG(LogJoystick, Error, TEXT("GetCapabilities: Invalid parameter"));
		return false;
	case DIERR_NOTINITIALIZED:
		UE_LOG(LogJoystick, Error, TEXT("GetCapabilities: Not initialized"));
		return false;
	case E_POINTER:
		UE_LOG(LogJoystick, Error, TEXT("GetCapabilities: Pointer"));
		return false;
	default:
		return true;
	}
}

void FJoystick::GetObjects()
{
	Device->EnumObjects(&StaticEnumerateAxes, this, DIDFT_AXIS); // DIDFT_AXIS | DIDFT_FFACTUATOR
}

bool FJoystick::Poll()
{
	switch (Device->Poll())
	{
	case DIERR_INPUTLOST:
		UE_LOG(LogJoystick, Error, TEXT("Poll: Input lost"));
		TryAcquireDevice();
		return false;
	case DIERR_NOTINITIALIZED:
		UE_LOG(LogJoystick, Error, TEXT("Poll: Not initialized"));
		TryAcquireDevice();
		return false;
	case DIERR_NOTACQUIRED:
		UE_LOG(LogJoystick, Error, TEXT("Poll: Not acquired"));
		TryAcquireDevice();
		return false;
	case DIERR_OTHERAPPHASPRIO:
		UE_LOG(LogJoystick, Error, TEXT("Poll: Other application has priority"));
		return false;
	default:
		break;
	}

	CopyMemory(&PreviousState, &CurrentState, sizeof(DIJOYSTATE2));
	ZeroMemory(&CurrentState, sizeof(DIJOYSTATE2));

	switch (Device->GetDeviceState(sizeof(DIJOYSTATE2), &CurrentState))
	{
	case DIERR_INPUTLOST:
		UE_LOG(LogJoystick, Error, TEXT("GetDeviceState: Input lost"));
		TryAcquireDevice();
		return false;
	case DIERR_INVALIDPARAM:
		UE_LOG(LogJoystick, Error, TEXT("GetDeviceState: Invalid parameter"));
		TryAcquireDevice();
		return false;
	case DIERR_NOTINITIALIZED:
		UE_LOG(LogJoystick, Error, TEXT("GetDeviceState: Not initialized"));
		TryAcquireDevice();
		return false;
	case DIERR_NOTACQUIRED:
		UE_LOG(LogJoystick, Error, TEXT("GetDeviceState: Not acquired"));
		TryAcquireDevice();
		return false;
	case E_PENDING:
		UE_LOG(LogJoystick, Error, TEXT("GetDeviceState: Pending"));
		return false;
	default:
		break;
	}

	return true;
}

int32 FJoystick::GetAxisValue(const uint32 Axis) const
{
	int32 Value;

	switch (Axis)
	{
	case 0:
		Value = CurrentState.lX;
		break;
	case 1:
		Value = CurrentState.lY;
		break;
	case 2:
		Value = CurrentState.lZ;
		break;
	case 3:
		Value = CurrentState.lRx;
		break;
	case 4:
		Value = CurrentState.lRy;
		break;
	case 5:
		Value = CurrentState.lRz;
		break;
	case 6:
		Value = CurrentState.rglSlider[0];
		break;
	case 7:
		Value = CurrentState.rglSlider[1];
		break;
	default:
		Value = 0;
		break;
	}

	return Value;
}

int32 FJoystick::GetButtonValue(const uint32 Button) const
{
	if (Button < GetNumButtons())
		return (CurrentState.rgbButtons[Button] & 0x80) ? 1 : 0;

	return 0;
}

int32 FJoystick::GetPovValue(const uint32 Pov) const
{
	if (Pov < GetNumPovs())
		return static_cast<int>(CurrentState.rgdwPOV[Pov]);

	return 0;
}

bool FJoystick::IsAxisChanged(const uint32 Axis) const
{
	switch (Axis)
	{
	case 0:
		return CurrentState.lX != PreviousState.lX;
	case 1:
		return CurrentState.lY != PreviousState.lY;
	case 2:
		return CurrentState.lZ != PreviousState.lZ;
	case 3:
		return CurrentState.lRx != PreviousState.lRx;
	case 4:
		return CurrentState.lRy != PreviousState.lRy;
	case 5:
		return CurrentState.lRz != PreviousState.lRz;
	case 6:
		return CurrentState.rglSlider[0] != PreviousState.rglSlider[0];
	case 7:
		return CurrentState.rglSlider[1] != PreviousState.rglSlider[1];
	default:
		return false;
	}
}

bool FJoystick::IsButtonChanged(const uint32 Button) const
{
	if (Button < GetNumButtons())
		return CurrentState.rgbButtons[Button] != PreviousState.rgbButtons[Button];

	return false;
}

bool FJoystick::IsPovChanged(const uint32 Pov) const
{
	if (Pov < GetNumPovs())
		return CurrentState.rgdwPOV[Pov] != PreviousState.rgdwPOV[Pov];

	return false;
}

FString FJoystick::GetAxisName(const uint32 Axis) const
{
	if (Axis > 7 || AxisInstances[Axis] == nullptr)
		return "";

	return AxisInstances[Axis]->tszName;
}

uint32 FJoystick::GetAxisMaxForce(const uint32 Axis) const
{
	if (Axis > 7 || AxisInstances[Axis] == nullptr)
		return 0;

	return AxisInstances[Axis]->dwFFMaxForce;
}

uint32 FJoystick::GetAxisForceResolution(const uint32 Axis) const
{
	if (Axis > 7 || AxisInstances[Axis] == nullptr)
		return 0;

	return AxisInstances[Axis]->dwFFForceResolution;
}

bool FJoystick::IsForceActuator(uint32 Axis) const
{
	if (Axis > 7 || AxisInstances[Axis] == nullptr)
		return false;

	return AxisInstances[Axis]->dwFlags & DIDOI_FFACTUATOR;
}

bool FJoystick::CreateEffect(uint32 Axis)
{
	DWORD dwAxis;
	switch (Axis)
	{
	case 0:
		dwAxis = DIJOFS_X;
		break;
	case 1:
		dwAxis = DIJOFS_Y;
		break;
	case 2:
		dwAxis = DIJOFS_Z;
		break;
	case 3:
		dwAxis = DIJOFS_RX;
		break;
	case 4:
		dwAxis = DIJOFS_RY;
		break;
	case 5:
		dwAxis = DIJOFS_RZ;
		break;
	case 6:
		dwAxis = DIJOFS_SLIDER(0);
		break;
	case 7:
		dwAxis = DIJOFS_SLIDER(1);
		break;
	default:
		UE_LOG(LogJoystick, Warning, TEXT("Force feedback axis %d does not exist on %s"), Axis, *GetInstanceName());
		return false;
	}

	DICONSTANTFORCE diConstantForce;
	diConstantForce.lMagnitude = 0;

	LONG direction = 0;

	ZeroMemory(&EffectConfig, sizeof(DIEFFECT));
	EffectConfig.dwSize = sizeof(DIEFFECT); 
	EffectConfig.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	EffectConfig.dwDuration = INFINITE;
	EffectConfig.dwSamplePeriod = 0;
	EffectConfig.dwGain = DI_FFNOMINALMAX;
	EffectConfig.dwTriggerButton = DIEB_NOTRIGGER;
	EffectConfig.dwTriggerRepeatInterval = 0;
	EffectConfig.cAxes = 1;
	EffectConfig.rgdwAxes = &dwAxis;
	EffectConfig.rglDirection = &direction;
	EffectConfig.lpEnvelope = nullptr;
	EffectConfig.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
	EffectConfig.lpvTypeSpecificParams = &diConstantForce;  

	switch (Device->CreateEffect(GUID_ConstantForce, &EffectConfig, &Effect, nullptr))
	{
	case DIERR_DEVICEFULL:
		UE_LOG(LogJoystick, Error, TEXT("CreateEffect: Device full : %s"), *GetInstanceGuidAsString());
		return false;
	case DIERR_DEVICENOTREG:
		UE_LOG(LogJoystick, Error, TEXT("CreateEffect: Device not registered : %s"), *GetInstanceGuidAsString());
		return false;
	case DIERR_INVALIDPARAM:
		UE_LOG(LogJoystick, Error, TEXT("CreateEffect: Invalid parameter"));
		return false;
	case DIERR_NOTINITIALIZED:
		UE_LOG(LogJoystick, Error, TEXT("CreateEffect: Not initialized"));
		return false;
	default:
		break;
	}

	switch (Effect->Start(INFINITE, 0))
	{
	case DIERR_INCOMPLETEEFFECT:
		UE_LOG(LogJoystick, Error, TEXT("Start: Incomplete effect"));
		return false;
	case DIERR_INVALIDPARAM:
		UE_LOG(LogJoystick, Error, TEXT("Start: Invalid parameter"));
		return false;
	case DIERR_NOTEXCLUSIVEACQUIRED:
		UE_LOG(LogJoystick, Error, TEXT("Start: Not exclusive acquired"));
		return false;
	case DIERR_NOTINITIALIZED:
		UE_LOG(LogJoystick, Error, TEXT("Start: Not initialized"));
		return false;
	case DIERR_UNSUPPORTED:
		UE_LOG(LogJoystick, Error, TEXT("Start: Unsupported"));
		return false;
	default:
		return true;
	}
}

bool FJoystick::UpdateEffect(const int Magnitude)
{
	DICONSTANTFORCE diConstantForce;
	diConstantForce.lMagnitude = Magnitude;

	EffectConfig.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
	EffectConfig.lpvTypeSpecificParams = &diConstantForce;

	switch (Effect->SetParameters(&EffectConfig, DIEP_TYPESPECIFICPARAMS | DIEP_START))
	{
	case DIERR_NOTINITIALIZED:
		UE_LOG(LogJoystick, Error, TEXT("SetParameters: Not initialized"));
		return false;
	case DIERR_INCOMPLETEEFFECT:
		UE_LOG(LogJoystick, Error, TEXT("SetParameters: Incomplete effect"));
		return false;
	case DIERR_INPUTLOST:
		UE_LOG(LogJoystick, Error, TEXT("SetParameters: Input lost"));
		return false;
	case DIERR_INVALIDPARAM:
		UE_LOG(LogJoystick, Error, TEXT("SetParameters: Invalid parameter"));
		return false;
	case DIERR_EFFECTPLAYING:
		UE_LOG(LogJoystick, Error, TEXT("SetParameters: Effect playing"));
		return false;
	default:
		return true;
	}
}

bool FJoystick::StopEffect() const
{
	switch (Effect->Stop())
	{
	case DIERR_NOTEXCLUSIVEACQUIRED:
		UE_LOG(LogJoystick, Error, TEXT("Stop: Not exclusive acquired"));
		return false;
	case DIERR_NOTINITIALIZED:
		UE_LOG(LogJoystick, Error, TEXT("Stop: Not initialized"));
		return false;
	default:
		return true;
	}
}
