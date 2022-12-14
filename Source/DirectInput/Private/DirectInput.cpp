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

#include "DirectInput.h"
#include "DirectInputDevice.h"
#include "Bindings.h"

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#define LOCTEXT_NAMESPACE "DirectInputPlugin"

IDInputDevice::IDInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) :
	MessageHandler(InMessageHandler)
{
};

TSharedPtr<class IInputDevice> FDirectInputModule::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	DirectInputDevice = MakeShareable(new FDirectInputDevice(InMessageHandler));
	return DirectInputDevice;
}

void FDirectInputModule::StartupModule()
{
	IInputDeviceModule::StartupModule();

	const FName NAME_DirectInput(TEXT("DirectInput"));

	EKeys::AddMenuCategoryDisplayInfo(NAME_DirectInput, LOCTEXT("DirectInputSubCateogry", "DirectInput"), TEXT("GraphEditor.KeyEvent_16x"));
	
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Axis1, LOCTEXT("DirectInput_Axis1", "Axis 1"), FKeyDetails::ButtonAxis, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Axis2, LOCTEXT("DirectInput_Axis1", "Axis 2"), FKeyDetails::ButtonAxis, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Axis3, LOCTEXT("DirectInput_Axis1", "Axis 3"), FKeyDetails::ButtonAxis, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Axis4, LOCTEXT("DirectInput_Axis1", "Axis 4"), FKeyDetails::ButtonAxis, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Axis5, LOCTEXT("DirectInput_Axis1", "Axis 5"), FKeyDetails::ButtonAxis, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Axis6, LOCTEXT("DirectInput_Axis1", "Axis 6"), FKeyDetails::ButtonAxis, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Axis7, LOCTEXT("DirectInput_Axis1", "Axis 7"), FKeyDetails::ButtonAxis, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Axis8, LOCTEXT("DirectInput_Axis1", "Axis 8"), FKeyDetails::ButtonAxis, NAME_DirectInput));

	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button1, LOCTEXT("DirectInput_Button1", "Button 1"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button2, LOCTEXT("DirectInput_Button2", "Button 2"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button3, LOCTEXT("DirectInput_Button3", "Button 3"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button4, LOCTEXT("DirectInput_Button4", "Button 4"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button5, LOCTEXT("DirectInput_Button5", "Button 5"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button6, LOCTEXT("DirectInput_Button6", "Button 6"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button7, LOCTEXT("DirectInput_Button7", "Button 7"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button8, LOCTEXT("DirectInput_Button8", "Button 8"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button9, LOCTEXT("DirectInput_Button9", "Button 9"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button10, LOCTEXT("DirectInput_Button10", "Button 10"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button11, LOCTEXT("DirectInput_Button11", "Button 11"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button12, LOCTEXT("DirectInput_Button12", "Button 12"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button13, LOCTEXT("DirectInput_Button13", "Button 13"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button14, LOCTEXT("DirectInput_Button14", "Button 14"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button15, LOCTEXT("DirectInput_Button15", "Button 15"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button16, LOCTEXT("DirectInput_Button16", "Button 16"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button17, LOCTEXT("DirectInput_Button17", "Button 17"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button18, LOCTEXT("DirectInput_Button18", "Button 18"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button19, LOCTEXT("DirectInput_Button19", "Button 19"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button20, LOCTEXT("DirectInput_Button20", "Button 20"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button21, LOCTEXT("DirectInput_Button21", "Button 21"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button22, LOCTEXT("DirectInput_Button22", "Button 22"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button23, LOCTEXT("DirectInput_Button23", "Button 23"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button24, LOCTEXT("DirectInput_Button24", "Button 24"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button25, LOCTEXT("DirectInput_Button25", "Button 25"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button26, LOCTEXT("DirectInput_Button26", "Button 26"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button27, LOCTEXT("DirectInput_Button27", "Button 27"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button28, LOCTEXT("DirectInput_Button28", "Button 28"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button29, LOCTEXT("DirectInput_Button29", "Button 29"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button30, LOCTEXT("DirectInput_Button30", "Button 30"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button31, LOCTEXT("DirectInput_Button31", "Button 31"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button32, LOCTEXT("DirectInput_Button32", "Button 32"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button33, LOCTEXT("DirectInput_Button33", "Button 33"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button34, LOCTEXT("DirectInput_Button34", "Button 34"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button35, LOCTEXT("DirectInput_Button35", "Button 35"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button36, LOCTEXT("DirectInput_Button36", "Button 36"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button37, LOCTEXT("DirectInput_Button37", "Button 37"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button38, LOCTEXT("DirectInput_Button38", "Button 38"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button39, LOCTEXT("DirectInput_Button39", "Button 39"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button40, LOCTEXT("DirectInput_Button40", "Button 40"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button41, LOCTEXT("DirectInput_Button41", "Button 41"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button42, LOCTEXT("DirectInput_Button42", "Button 42"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button43, LOCTEXT("DirectInput_Button43", "Button 43"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button44, LOCTEXT("DirectInput_Button44", "Button 44"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button45, LOCTEXT("DirectInput_Button45", "Button 45"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button46, LOCTEXT("DirectInput_Button46", "Button 46"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button47, LOCTEXT("DirectInput_Button47", "Button 47"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button48, LOCTEXT("DirectInput_Button48", "Button 48"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button49, LOCTEXT("DirectInput_Button49", "Button 49"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button50, LOCTEXT("DirectInput_Button50", "Button 50"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button51, LOCTEXT("DirectInput_Button51", "Button 51"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button52, LOCTEXT("DirectInput_Button52", "Button 52"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button53, LOCTEXT("DirectInput_Button53", "Button 53"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button54, LOCTEXT("DirectInput_Button54", "Button 54"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button55, LOCTEXT("DirectInput_Button55", "Button 55"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button56, LOCTEXT("DirectInput_Button56", "Button 56"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button57, LOCTEXT("DirectInput_Button57", "Button 57"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button58, LOCTEXT("DirectInput_Button58", "Button 58"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button59, LOCTEXT("DirectInput_Button59", "Button 59"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button60, LOCTEXT("DirectInput_Button60", "Button 60"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button61, LOCTEXT("DirectInput_Button61", "Button 61"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button62, LOCTEXT("DirectInput_Button62", "Button 62"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button63, LOCTEXT("DirectInput_Button63", "Button 63"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button64, LOCTEXT("DirectInput_Button64", "Button 64"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button65, LOCTEXT("DirectInput_Button65", "Button 65"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button66, LOCTEXT("DirectInput_Button66", "Button 66"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button67, LOCTEXT("DirectInput_Button67", "Button 67"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button68, LOCTEXT("DirectInput_Button68", "Button 68"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button69, LOCTEXT("DirectInput_Button69", "Button 69"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button70, LOCTEXT("DirectInput_Button70", "Button 70"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button71, LOCTEXT("DirectInput_Button71", "Button 71"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button72, LOCTEXT("DirectInput_Button72", "Button 72"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button73, LOCTEXT("DirectInput_Button73", "Button 73"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button74, LOCTEXT("DirectInput_Button74", "Button 74"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button75, LOCTEXT("DirectInput_Button75", "Button 75"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button76, LOCTEXT("DirectInput_Button76", "Button 76"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button77, LOCTEXT("DirectInput_Button77", "Button 77"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button78, LOCTEXT("DirectInput_Button78", "Button 78"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button79, LOCTEXT("DirectInput_Button79", "Button 79"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button80, LOCTEXT("DirectInput_Button80", "Button 80"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button81, LOCTEXT("DirectInput_Button81", "Button 81"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button82, LOCTEXT("DirectInput_Button82", "Button 82"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button83, LOCTEXT("DirectInput_Button83", "Button 83"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button84, LOCTEXT("DirectInput_Button84", "Button 84"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button85, LOCTEXT("DirectInput_Button85", "Button 85"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button86, LOCTEXT("DirectInput_Button86", "Button 86"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button87, LOCTEXT("DirectInput_Button87", "Button 87"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button88, LOCTEXT("DirectInput_Button88", "Button 88"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button89, LOCTEXT("DirectInput_Button89", "Button 89"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button90, LOCTEXT("DirectInput_Button90", "Button 90"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button91, LOCTEXT("DirectInput_Button91", "Button 91"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button92, LOCTEXT("DirectInput_Button92", "Button 92"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button93, LOCTEXT("DirectInput_Button93", "Button 93"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button94, LOCTEXT("DirectInput_Button94", "Button 94"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button95, LOCTEXT("DirectInput_Button95", "Button 95"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button96, LOCTEXT("DirectInput_Button96", "Button 96"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button97, LOCTEXT("DirectInput_Button97", "Button 97"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button98, LOCTEXT("DirectInput_Button98", "Button 98"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button99, LOCTEXT("DirectInput_Button99", "Button 99"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button100, LOCTEXT("DirectInput_Button100", "Button 100"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button101, LOCTEXT("DirectInput_Button101", "Button 101"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button102, LOCTEXT("DirectInput_Button102", "Button 102"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button103, LOCTEXT("DirectInput_Button103", "Button 103"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button104, LOCTEXT("DirectInput_Button104", "Button 104"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button105, LOCTEXT("DirectInput_Button105", "Button 105"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button106, LOCTEXT("DirectInput_Button106", "Button 106"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button107, LOCTEXT("DirectInput_Button107", "Button 107"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button108, LOCTEXT("DirectInput_Button108", "Button 108"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button109, LOCTEXT("DirectInput_Button109", "Button 109"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button110, LOCTEXT("DirectInput_Button110", "Button 110"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button111, LOCTEXT("DirectInput_Button111", "Button 111"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button112, LOCTEXT("DirectInput_Button112", "Button 112"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button113, LOCTEXT("DirectInput_Button113", "Button 113"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button114, LOCTEXT("DirectInput_Button114", "Button 114"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button115, LOCTEXT("DirectInput_Button115", "Button 115"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button116, LOCTEXT("DirectInput_Button116", "Button 116"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button117, LOCTEXT("DirectInput_Button117", "Button 117"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button118, LOCTEXT("DirectInput_Button118", "Button 118"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button119, LOCTEXT("DirectInput_Button119", "Button 119"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button120, LOCTEXT("DirectInput_Button120", "Button 120"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button121, LOCTEXT("DirectInput_Button121", "Button 121"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button122, LOCTEXT("DirectInput_Button122", "Button 122"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button123, LOCTEXT("DirectInput_Button123", "Button 123"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button124, LOCTEXT("DirectInput_Button124", "Button 124"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button125, LOCTEXT("DirectInput_Button125", "Button 125"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button126, LOCTEXT("DirectInput_Button126", "Button 126"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button127, LOCTEXT("DirectInput_Button127", "Button 127"), FKeyDetails::GamepadKey, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Button128, LOCTEXT("DirectInput_Button128", "Button 128"), FKeyDetails::GamepadKey, NAME_DirectInput));
	
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Pov1, LOCTEXT("DirectInput_Pov1", "POV 1"), FKeyDetails::Axis1D, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Pov2, LOCTEXT("DirectInput_Pov1", "POV 2"), FKeyDetails::Axis1D, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Pov3, LOCTEXT("DirectInput_Pov1", "POV 3"), FKeyDetails::Axis1D, NAME_DirectInput));
	EKeys::AddKey(FKeyDetails(FDirectInputKeys::Pov4, LOCTEXT("DirectInput_Pov1", "POV 4"), FKeyDetails::Axis1D, NAME_DirectInput));
}

void FDirectInputModule::ShutdownModule()
{
	IInputDeviceModule::ShutdownModule();
}

IMPLEMENT_MODULE(FDirectInputModule, DirectInput)
