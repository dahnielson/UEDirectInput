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

#include "DirectInputDevice.h"
#include "Bindings.h"
#include "Joystick.h"

DEFINE_LOG_CATEGORY_STATIC(LogDirectInputDevice, Log, All);

IDirectInput8* GInputObject = nullptr;
TArray<FJoystick> GInputDevices;

static BOOL CALLBACK StaticEnumerateDevice(LPCDIDEVICEINSTANCE deviceInstance, LPVOID pvRef)
{
	for (FJoystick& Joy : GInputDevices)
	{
		if (IsEqualGUID(deviceInstance->guidInstance, Joy.GetInstanceGuid()))
			return DIENUM_CONTINUE;
	}

	// const auto Device = static_cast<FDirectInputDevice*>(pvRef);

	LPDIRECTINPUTDEVICE8 InputDevice;
	if (GInputObject->CreateDevice(deviceInstance->guidInstance, &InputDevice, nullptr) == DI_OK)
	{
		GInputDevices.Emplace(InputDevice);
	}
	return DIENUM_CONTINUE;
}

FDirectInputDevice::FDirectInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) :
	IDInputDevice(InMessageHandler),
	TimeSinceLastCheck(0)
{
	AxisNames.AddDefaulted(8);
	ButtonNames.AddDefaulted(128);
	PovNames.AddDefaulted(4);

	AxisNames[0] = FDirectInputKeyNames::Axis1;
	AxisNames[1] = FDirectInputKeyNames::Axis2;
	AxisNames[2] = FDirectInputKeyNames::Axis3;
	AxisNames[3] = FDirectInputKeyNames::Axis4;
	AxisNames[4] = FDirectInputKeyNames::Axis5;
	AxisNames[5] = FDirectInputKeyNames::Axis6;
	AxisNames[6] = FDirectInputKeyNames::Axis7;
	AxisNames[7] = FDirectInputKeyNames::Axis8;

	ButtonNames[0] = FDirectInputKeyNames::Button1;
	ButtonNames[1] = FDirectInputKeyNames::Button2;
	ButtonNames[2] = FDirectInputKeyNames::Button3;
	ButtonNames[3] = FDirectInputKeyNames::Button4;
	ButtonNames[4] = FDirectInputKeyNames::Button5;
	ButtonNames[5] = FDirectInputKeyNames::Button6;
	ButtonNames[6] = FDirectInputKeyNames::Button7;
	ButtonNames[7] = FDirectInputKeyNames::Button8;
	ButtonNames[8] = FDirectInputKeyNames::Button9;
	ButtonNames[9] = FDirectInputKeyNames::Button10;
	ButtonNames[10] = FDirectInputKeyNames::Button11;
	ButtonNames[11] = FDirectInputKeyNames::Button12;
	ButtonNames[12] = FDirectInputKeyNames::Button13;
	ButtonNames[13] = FDirectInputKeyNames::Button14;
	ButtonNames[14] = FDirectInputKeyNames::Button15;
	ButtonNames[15] = FDirectInputKeyNames::Button16;
	ButtonNames[16] = FDirectInputKeyNames::Button17;
	ButtonNames[17] = FDirectInputKeyNames::Button18;
	ButtonNames[18] = FDirectInputKeyNames::Button19;
	ButtonNames[19] = FDirectInputKeyNames::Button20;
	ButtonNames[20] = FDirectInputKeyNames::Button21;
	ButtonNames[21] = FDirectInputKeyNames::Button22;
	ButtonNames[22] = FDirectInputKeyNames::Button23;
	ButtonNames[23] = FDirectInputKeyNames::Button24;
	ButtonNames[24] = FDirectInputKeyNames::Button25;
	ButtonNames[25] = FDirectInputKeyNames::Button26;
	ButtonNames[26] = FDirectInputKeyNames::Button27;
	ButtonNames[27] = FDirectInputKeyNames::Button28;
	ButtonNames[28] = FDirectInputKeyNames::Button29;
	ButtonNames[29] = FDirectInputKeyNames::Button30;
	ButtonNames[30] = FDirectInputKeyNames::Button31;
	ButtonNames[31] = FDirectInputKeyNames::Button32;
	ButtonNames[32] = FDirectInputKeyNames::Button33;
	ButtonNames[33] = FDirectInputKeyNames::Button34;
	ButtonNames[34] = FDirectInputKeyNames::Button35;
	ButtonNames[35] = FDirectInputKeyNames::Button36;
	ButtonNames[36] = FDirectInputKeyNames::Button37;
	ButtonNames[37] = FDirectInputKeyNames::Button38;
	ButtonNames[38] = FDirectInputKeyNames::Button39;
	ButtonNames[39] = FDirectInputKeyNames::Button40;
	ButtonNames[40] = FDirectInputKeyNames::Button41;
	ButtonNames[41] = FDirectInputKeyNames::Button42;
	ButtonNames[42] = FDirectInputKeyNames::Button43;
	ButtonNames[43] = FDirectInputKeyNames::Button44;
	ButtonNames[44] = FDirectInputKeyNames::Button45;
	ButtonNames[45] = FDirectInputKeyNames::Button46;
	ButtonNames[46] = FDirectInputKeyNames::Button47;
	ButtonNames[47] = FDirectInputKeyNames::Button48;
	ButtonNames[48] = FDirectInputKeyNames::Button49;
	ButtonNames[49] = FDirectInputKeyNames::Button50;
	ButtonNames[50] = FDirectInputKeyNames::Button51;
	ButtonNames[51] = FDirectInputKeyNames::Button52;
	ButtonNames[52] = FDirectInputKeyNames::Button53;
	ButtonNames[53] = FDirectInputKeyNames::Button54;
	ButtonNames[54] = FDirectInputKeyNames::Button55;
	ButtonNames[55] = FDirectInputKeyNames::Button56;
	ButtonNames[56] = FDirectInputKeyNames::Button57;
	ButtonNames[57] = FDirectInputKeyNames::Button58;
	ButtonNames[58] = FDirectInputKeyNames::Button59;
	ButtonNames[59] = FDirectInputKeyNames::Button60;
	ButtonNames[60] = FDirectInputKeyNames::Button61;
	ButtonNames[61] = FDirectInputKeyNames::Button62;
	ButtonNames[62] = FDirectInputKeyNames::Button63;
	ButtonNames[63] = FDirectInputKeyNames::Button64;
	ButtonNames[64] = FDirectInputKeyNames::Button65;
	ButtonNames[65] = FDirectInputKeyNames::Button66;
	ButtonNames[66] = FDirectInputKeyNames::Button67;
	ButtonNames[67] = FDirectInputKeyNames::Button68;
	ButtonNames[68] = FDirectInputKeyNames::Button69;
	ButtonNames[69] = FDirectInputKeyNames::Button70;
	ButtonNames[70] = FDirectInputKeyNames::Button71;
	ButtonNames[71] = FDirectInputKeyNames::Button72;
	ButtonNames[72] = FDirectInputKeyNames::Button73;
	ButtonNames[73] = FDirectInputKeyNames::Button74;
	ButtonNames[74] = FDirectInputKeyNames::Button75;
	ButtonNames[75] = FDirectInputKeyNames::Button76;
	ButtonNames[76] = FDirectInputKeyNames::Button77;
	ButtonNames[77] = FDirectInputKeyNames::Button78;
	ButtonNames[78] = FDirectInputKeyNames::Button79;
	ButtonNames[79] = FDirectInputKeyNames::Button80;
	ButtonNames[80] = FDirectInputKeyNames::Button81;
	ButtonNames[81] = FDirectInputKeyNames::Button82;
	ButtonNames[82] = FDirectInputKeyNames::Button83;
	ButtonNames[83] = FDirectInputKeyNames::Button84;
	ButtonNames[84] = FDirectInputKeyNames::Button85;
	ButtonNames[85] = FDirectInputKeyNames::Button86;
	ButtonNames[86] = FDirectInputKeyNames::Button87;
	ButtonNames[87] = FDirectInputKeyNames::Button88;
	ButtonNames[88] = FDirectInputKeyNames::Button89;
	ButtonNames[89] = FDirectInputKeyNames::Button90;
	ButtonNames[90] = FDirectInputKeyNames::Button91;
	ButtonNames[91] = FDirectInputKeyNames::Button92;
	ButtonNames[92] = FDirectInputKeyNames::Button93;
	ButtonNames[93] = FDirectInputKeyNames::Button94;
	ButtonNames[94] = FDirectInputKeyNames::Button95;
	ButtonNames[95] = FDirectInputKeyNames::Button96;
	ButtonNames[96] = FDirectInputKeyNames::Button97;
	ButtonNames[97] = FDirectInputKeyNames::Button98;
	ButtonNames[98] = FDirectInputKeyNames::Button99;
	ButtonNames[99] = FDirectInputKeyNames::Button100;
	ButtonNames[100] = FDirectInputKeyNames::Button101;
	ButtonNames[101] = FDirectInputKeyNames::Button102;
	ButtonNames[102] = FDirectInputKeyNames::Button103;
	ButtonNames[103] = FDirectInputKeyNames::Button104;
	ButtonNames[104] = FDirectInputKeyNames::Button105;
	ButtonNames[105] = FDirectInputKeyNames::Button106;
	ButtonNames[106] = FDirectInputKeyNames::Button107;
	ButtonNames[107] = FDirectInputKeyNames::Button108;
	ButtonNames[108] = FDirectInputKeyNames::Button109;
	ButtonNames[109] = FDirectInputKeyNames::Button110;
	ButtonNames[110] = FDirectInputKeyNames::Button111;
	ButtonNames[111] = FDirectInputKeyNames::Button112;
	ButtonNames[112] = FDirectInputKeyNames::Button113;
	ButtonNames[113] = FDirectInputKeyNames::Button114;
	ButtonNames[114] = FDirectInputKeyNames::Button115;
	ButtonNames[115] = FDirectInputKeyNames::Button116;
	ButtonNames[116] = FDirectInputKeyNames::Button117;
	ButtonNames[117] = FDirectInputKeyNames::Button118;
	ButtonNames[118] = FDirectInputKeyNames::Button119;
	ButtonNames[119] = FDirectInputKeyNames::Button120;
	ButtonNames[120] = FDirectInputKeyNames::Button121;
	ButtonNames[121] = FDirectInputKeyNames::Button122;
	ButtonNames[122] = FDirectInputKeyNames::Button123;
	ButtonNames[123] = FDirectInputKeyNames::Button124;
	ButtonNames[124] = FDirectInputKeyNames::Button125;
	ButtonNames[125] = FDirectInputKeyNames::Button126;
	ButtonNames[126] = FDirectInputKeyNames::Button127;
	ButtonNames[127] = FDirectInputKeyNames::Button128;

	PovNames[0] = FDirectInputKeyNames::Pov1;
	PovNames[1] = FDirectInputKeyNames::Pov2;
	PovNames[2] = FDirectInputKeyNames::Pov3;
	PovNames[3] = FDirectInputKeyNames::Pov4;
	
	if (DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&GInputObject, nullptr) == DI_OK)
	{
		// Only enumerate devices meant for driving or flying that are currently attached
		GInputObject->EnumDevices(DI8DEVTYPE_DRIVING | DI8DEVTYPE_FLIGHT, &StaticEnumerateDevice, this, DIEDFL_ATTACHEDONLY);
	}
}

FDirectInputDevice::~FDirectInputDevice()
{
	GInputDevices.Empty();
}

void FDirectInputDevice::Tick(float DeltaTime)
{
	TimeSinceLastCheck += DeltaTime;
	if (GInputObject != nullptr && TimeSinceLastCheck > 60)
	{
		TimeSinceLastCheck = 0;
		GInputObject->EnumDevices(DI8DEVTYPE_DRIVING, &StaticEnumerateDevice, this, DIEDFL_ATTACHEDONLY);
	}
}

void FDirectInputDevice::SendControllerEvents()
{
	// Don't run if in editor
	if (GEngine->IsEditor())
	{
		return;
	}

	int32 ControllerId = 0;
	for (FJoystick& Joy : GInputDevices)
	{
		FInputDeviceScope InputScope(this, DirectInputInterfaceName, ControllerId, Joy.GetInstanceName());
		
		Joy.Poll();

		for (uint32 Axis = 0; Axis < Joy.GetNumAxes(); Axis++)
		{
			if (Joy.IsAxisChanged(Axis))
			{
				const int32 Value = Joy.GetAxisValue(Axis);
				//UE_LOG(LogDirectInputDevice, Log, TEXT("ControllerId %d Axis %d : %d"), ControllerId, Axis, Value);
				MessageHandler->OnControllerAnalog(AxisNames[Axis], ControllerId, Value);
			}
		}
		
		for (uint32 Button = 0; Button < Joy.GetNumButtons(); Button++)
		{
			if (Joy.IsButtonChanged(Button))
			{
				if (Joy.GetButtonValue(Button))
				{
					//UE_LOG(LogDirectInputDevice, Log, TEXT("ControllerId %d Button %d : pressed"), ControllerId, Button);
					MessageHandler->OnControllerButtonPressed(ButtonNames[Button], ControllerId, false);
				}
				else
				{
					//UE_LOG(LogDirectInputDevice, Log, TEXT("ControllerId %d Button %d : released"), ControllerId, Button);
					MessageHandler->OnControllerButtonReleased(ButtonNames[Button], ControllerId, false);
				}
			}
		}

		for (uint32 Pov = 0; Pov < Joy.GetNumPovs(); Pov++)
		{
			if (Joy.IsPovChanged(Pov))
			{
				const uint32 Value = Joy.GetPovValue(Pov);
				//UE_LOG(LogDirectInputDevice, Log, TEXT("ControllerId %d POV %d : %d"), ControllerId, Pov, Value);
				MessageHandler->OnControllerAnalog(PovNames[Pov], ControllerId, Value);
			}
		}

		ControllerId++;
	}
}

void FDirectInputDevice::SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}

bool FDirectInputDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return false;
}

void FDirectInputDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
	switch (ChannelType)
	{
	case FForceFeedbackChannelType::LEFT_LARGE:
		if (ControllerId < GInputDevices.Num())
		{
			GInputDevices[ControllerId].UpdateEffect(Value);
		}
		break;
	case FForceFeedbackChannelType::LEFT_SMALL:
		// NOP
		break;
	case FForceFeedbackChannelType::RIGHT_LARGE:
		// NOP
		break;
	case FForceFeedbackChannelType::RIGHT_SMALL:
		// NOP
		break;
	default:
		break;
	}
}

void FDirectInputDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values)
{
	if (ControllerId < GInputDevices.Num())
	{
		GInputDevices[ControllerId].UpdateEffect(Values.LeftLarge);
	}
}
