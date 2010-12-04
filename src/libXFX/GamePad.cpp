// Copyright (C) 2010-2012, Halofreak_1990
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

extern "C"{
#ifdef ENABLE_XBOX
#include "xinput.h"
#else
#endif
}

#include <MathHelper.h>
#include <Input/GamePad.h>

namespace XFX
{
	namespace Input
	{
		GamePadState g_State;
		
		GamePadState GamePad::GetState(PlayerIndex_t playerIndex)
		{
			//Update IsConnected
			g_State.IsConnected = g_Pads[playerIndex].hPresent;
			
			//Update Button presses
			if(g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_A]) 
				g_State.Buttons.A = ButtonState::Pressed;
			else
				g_State.Buttons.A = ButtonState::Released;
			if(g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_B]) 
				g_State.Buttons.B = ButtonState::Pressed;
			else
				g_State.Buttons.B = ButtonState::Released;
			if(g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_BACK)
				g_State.Buttons.Back = ButtonState::Pressed;
			else
				g_State.Buttons.Back = ButtonState::Released;
			if(g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_BLACK]) 
				g_State.Buttons.Black = ButtonState::Pressed;
			else
				g_State.Buttons.Black = ButtonState::Released;
			if(g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_LEFT_THUMB]) 
				g_State.ThumbSticks.Left = ButtonState::Pressed;
			else
				g_State.ThumbSticks.Left = ButtonState::Released;
			if(g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_RIGHT_THUMB]) 
				g_State.ThumbSticks.Right = ButtonState::Pressed;
			else
				g_State.ThumbSticks.Right = ButtonState::Released;
			if(g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_START)
				g_State.Buttons.Start = ButtonState::Pressed;
			else
				g_State.Buttons.Start = ButtonState::Released;
			if(g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_WHITE]) 
				g_State.Buttons.B = ButtonState::Pressed;
			else
				g_State.Buttons.B = ButtonState::Released;
			if(g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_X]) 
				g_State.Buttons.X = ButtonState::Pressed;
			else
				g_State.Buttons.X = ButtonState::Released;
			if(g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_Y]) 
				g_State.Buttons.Y = ButtonState::Pressed;
			else
				g_State.Buttons.Y = ButtonState::Released;
				
			//Update DPad
			if(g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_DPAD_DOWN)
				g_State.DPad.Down = ButtonState::Pressed;
			else
				g_State.DPad.Down = ButtonState::Released;
			if(g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_DPAD_LEFT)
				g_State.DPad.Left = ButtonState::Pressed;
			else
				g_State.DPad.Left = ButtonState::Released;
			if(g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_DPAD_RIGHT)
				g_State.DPad.Right = ButtonState::Pressed;
			else
				g_State.DPad.Right = ButtonState::Released;
			if(g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_DPAD_UP)
				g_State.DPad.Up = ButtonState::Pressed;
			else
				g_State.DPad.Up = ButtonState::Released;
				
			//Update ThumbStick values
			g_State.ThumbSticks.Left.X = g_Pads[playerIndex].sLThumbX;
			g_State.ThumbSticks.Left.Y = -g_Pads[playerIndex].sLThumbY;
			g_State.ThumbSticks.Right.X = g_Pads[playerIndex].sRThumbX;
			g_State.ThumbSticks.Right.Y = -g_Pads[playerIndex].sRThumbY;
			
			return g_State;
		}
		
		int GamePad::SetVibration(PlayerIndex_t playerIndex, float leftMotor, float rightMotor)
		{
			//If the controller is Disconnected, why bother?
			if(GetState(playerIndex).IsConnected == false)
			{
				return -1;
			}
			else
			{
				int iWhichPad = 0;

				byte leftSpeed = (byte)(MathHelper::Clamp(leftMotor, 0.0f, 1.0f) * 255);
				byte rightSpeed = (byte)(MathHelper::Clamp(rightMotor, 0.0f, 1.0f) * 255);
				
				switch(playerIndex)
				{
				case PlayerIndex::One:
					iWhichPad = 3;
					break;
				case PlayerIndex::Two:
					iWhichPad = 4;
					break;
				case PlayerIndex::Three:
					iWhichPad = 1;
					break;
				case PlayerIndex::Four:
					iWhichPad = 2;
					break;
				default:
					throw InvalidOperationException();
					return false;
				}

				usbd_device dev;
				dev.p_ohci  = &(xin->my_ohci);
				dev.address = iWhichPad;  // This will choose the first gamepad it finds, only for debug

				byte data1[6] = { 0, 6, 0, leftSpeed, 0, rightSpeed };    // rumble data
				usb_bulk_msg(&dev, 6, (void*)data1);  // simple bulk send function (in pad.c/.h)
			}
		}

		bool GamePadState::operator ==(GamePadState other)
		{
			return ((IsConnected == other.IsConnected) && (ThumbSticks == other.ThumbSticks) &&
				(Triggers == other.Triggers) && (DPad == other.DPad) && (Buttons == other.Buttons));
		}

		bool GamePadState::operator !=(GamePadState other)
		{
			return !(*this == other);
		}
	}
}
