// Copyright (C) 2010-2012, XFX Team
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

extern "C"
{
#include <hal/input.h>
}

#include <MathHelper.h>
#include <Input/GamePad.h>
#include <System/Array.h>
#include <System/Exception.h>

using namespace System;

/******************* KNOWN BUGS ******
 *
 *	The OpenXDK Input Library doesn't properly pick up reconnecting a controller after it being disconnected.
 *	Therefore, the IsConnected property in GamePadState doesn't get changed back to true once the controller
 *	has been reconnected. The input library will need to be revised, and code to set the vibration motors needs
 *	to be added. Once that's done, the XFX Input namespace is completely finished.
 *
 ************************/

namespace XFX
{
	namespace Input
	{
		GamePadState g_State;
		
		GamePadState GamePad::GetState(PlayerIndex_t playerIndex)
		{
			XInput_GetEvents();

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
			if (g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_LEFT_THUMB)
				g_State.Buttons.LeftStick = ButtonState::Pressed;
			else
				g_State.Buttons.LeftStick = ButtonState::Released;
			if (g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_RIGHT_THUMB)
				g_State.Buttons.RightStick = ButtonState::Pressed;
			else
				g_State.Buttons.RightStick = ButtonState::Released;
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
			g_State.ThumbSticks.Left.Y = g_Pads[playerIndex].sLThumbY;
			g_State.ThumbSticks.Right.X = g_Pads[playerIndex].sRThumbX;
			g_State.ThumbSticks.Right.Y = g_Pads[playerIndex].sRThumbY;
			
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
				byte leftSpeed = (byte)(MathHelper::Clamp(leftMotor, 0.0f, 1.0f) * 255);
				byte rightSpeed = (byte)(MathHelper::Clamp(rightMotor, 0.0f, 1.0f) * 255);

				//Can't do anything yet, since we can't send anything through the OpenXDK Input lib
				return 1;
			}
		}

		GamePadState::GamePadState(GamePadThumbSticks thumbSticks, GamePadTriggers triggers, GamePadButtons buttons, GamePadDPad dpad)
		{
			ThumbSticks = thumbSticks;
			Triggers = triggers;
			Buttons = buttons;
			DPad = dpad;
		}

		GamePadState::GamePadState(Vector2 leftThumbStick, Vector2 rightThumbStick, float leftTrigger, float rightTrigger, Buttons_t buttons[])
		{
			ThumbSticks.Left = leftThumbStick;
			ThumbSticks.Right = rightThumbStick;
			Triggers.Left = leftTrigger;
			Triggers.Right = rightTrigger;
			if(buttons != null)
			{
				for (int i = 0; i < Array::Length(buttons); i++)
				{
					switch(buttons[i])
					{
					case Buttons::A:
						Buttons.A = ButtonState::Pressed;
						break;
					case Buttons::B:
						Buttons.B = ButtonState::Pressed;
						break;
					case Buttons::Back:
						Buttons.Back = ButtonState::Pressed;
						break;
					case Buttons::Black:
						Buttons.Black = ButtonState::Pressed;
						break;
					case Buttons::DPadDown:
						DPad.Down = ButtonState::Pressed;
						break;
					case Buttons::DPadLeft:
						DPad.Left = ButtonState::Pressed;
						break;
					case Buttons::DPadRight:
						DPad.Right = ButtonState::Pressed;
						break;
					case Buttons::DPadUp:
						DPad.Up = ButtonState::Pressed;
						break;
					case Buttons::LeftStick:
						Buttons.LeftStick = ButtonState::Pressed;
						break;
					case Buttons::RightStick:
						Buttons.RightStick = ButtonState::Pressed;
						break;
					case Buttons::Start:
						Buttons.Start = ButtonState::Pressed;
						break;
					case Buttons::White:
						Buttons.White = ButtonState::Pressed;
						break;
					case Buttons::X:
						Buttons.X = ButtonState::Pressed;
						break;
					case Buttons::Y:
						Buttons.Y = ButtonState::Pressed;
						break;
					default:
						break;
					}
				}
			}
		}

		bool GamePadState::IsButtonDown(Buttons_t button)
		{
			switch(button)
			{
			case Buttons::A:
				return Buttons.A == ButtonState::Pressed;
			case Buttons::B:
				return Buttons.B == ButtonState::Pressed;
			case Buttons::Back:
				return Buttons.Back == ButtonState::Pressed;
			case Buttons::Black:
				return Buttons.Black == ButtonState::Pressed;
			case Buttons::DPadDown:
				return DPad.Down == ButtonState::Pressed;
			case Buttons::DPadLeft:
				return DPad.Left == ButtonState::Pressed;
			case Buttons::DPadRight:
				return DPad.Right == ButtonState::Pressed;
			case Buttons::DPadUp:
				return DPad.Up == ButtonState::Pressed;
			case Buttons::LeftStick:
				return Buttons.LeftStick == ButtonState::Pressed;
			case Buttons::LeftThumbstickDown:
				return (ThumbSticks.Left.Y < -64);
			case Buttons::LeftThumbstickLeft:
				return (ThumbSticks.Left.X < -64);
			case Buttons::LeftThumbstickRight:
				return (ThumbSticks.Left.X > 64);
			case Buttons::LeftThumbstickUp:
				return (ThumbSticks.Left.Y > 64);
			case Buttons::LeftTrigger:
				return (Triggers.Left > 0);
			case Buttons::RightStick:
				return Buttons.RightStick == ButtonState::Pressed;
			case Buttons::RightThumbstickDown:
				return (ThumbSticks.Right.Y < -64);
			case Buttons::RightThumbstickLeft:
				return (ThumbSticks.Right.X < -64);
			case Buttons::RightThumbstickRight:
				return (ThumbSticks.Right.X > 64);
			case Buttons::RightThumbstickUp:
				return (ThumbSticks.Right.Y > 64);
			case Buttons::RightTrigger:
				return (Triggers.Right > 0);
			case Buttons::Start:
				return Buttons.Start == ButtonState::Pressed;
			case Buttons::White:
				return Buttons.White == ButtonState::Pressed;
			case Buttons::X:
				return Buttons.X == ButtonState::Pressed;
			case Buttons::Y:
				return Buttons.Y == ButtonState::Pressed;
			}
			return false;
		}

		bool GamePadState::IsButtonUp(Buttons_t button)
		{
			switch(button)
			{
			case Buttons::A:
				return Buttons.A == ButtonState::Released;
			case Buttons::B:
				return Buttons.B == ButtonState::Released;
			case Buttons::Back:
				return Buttons.Back == ButtonState::Released;
			case Buttons::Black:
				return Buttons.Black == ButtonState::Released;
			case Buttons::DPadDown:
				return DPad.Down == ButtonState::Released;
			case Buttons::DPadLeft:
				return DPad.Left == ButtonState::Released;
			case Buttons::DPadRight:
				return DPad.Right == ButtonState::Released;
			case Buttons::DPadUp:
				return DPad.Up == ButtonState::Released;
			case Buttons::LeftStick:
				return Buttons.LeftStick == ButtonState::Released;
			case Buttons::LeftThumbstickDown:
				return !(ThumbSticks.Left.Y < -64);
			case Buttons::LeftThumbstickLeft:
				return !(ThumbSticks.Left.X < -64);
			case Buttons::LeftThumbstickRight:
				return !(ThumbSticks.Left.X > 64);
			case Buttons::LeftThumbstickUp:
				return !(ThumbSticks.Left.Y > 64);
			case Buttons::LeftTrigger:
				return !(Triggers.Left > 0);
			case Buttons::RightStick:
				return Buttons.RightStick == ButtonState::Released;
			case Buttons::RightThumbstickDown:
				return !(ThumbSticks.Right.Y < -64);
			case Buttons::RightThumbstickLeft:
				return !(ThumbSticks.Right.X < -64);
			case Buttons::RightThumbstickRight:
				return !(ThumbSticks.Right.X > 64);
			case Buttons::RightThumbstickUp:
				return !(ThumbSticks.Right.Y > 64);
			case Buttons::RightTrigger:
				return !(Triggers.Right > 0);
			case Buttons::Start:
				return Buttons.Start == ButtonState::Released;
			case Buttons::White:
				return Buttons.White == ButtonState::Released;
			case Buttons::X:
				return Buttons.X == ButtonState::Released;
			case Buttons::Y:
				return Buttons.Y == ButtonState::Released;
			}
			return false;
		}

		bool GamePadState::operator ==(const GamePadState other)
		{
			return ((IsConnected == other.IsConnected) && (ThumbSticks == other.ThumbSticks) &&
				(Triggers == other.Triggers) && (DPad == other.DPad) && (Buttons == other.Buttons));
		}

		bool GamePadState::operator !=(const GamePadState other)
		{
			return !(*this == other);
		}

		GamePadThumbSticks::GamePadThumbSticks(Vector2 leftThumbstick, Vector2 rightThumbstick)
		{
			Left = leftThumbstick;
			Right = rightThumbstick;
		}

		GamePadThumbSticks::GamePadThumbSticks()
		{
			Left = Vector2::Zero;
			Right = Vector2::Zero;
		}

		GamePadThumbSticks::GamePadThumbSticks(const GamePadThumbSticks &obj)
		{
			Left = obj.Left;
			Right = obj.Right;
		}

		bool GamePadThumbSticks::Equals(const GamePadThumbSticks obj)
		{
			return (Left == obj.Left) && (Right == obj.Right);
		}

		int GamePadThumbSticks::GetHashCode()
		{
			return Left.GetHashCode() ^ Right.GetHashCode();
		}

		bool GamePadThumbSticks::operator!=(const GamePadThumbSticks other)
		{
			return !Equals(other);
		}

		bool GamePadThumbSticks::operator==(const GamePadThumbSticks other)
		{
			return Equals(other);
		}

		GamePadTriggers::GamePadTriggers(float left, float right)
		{
			Left = left;
			Right = right;
		}

		GamePadTriggers::GamePadTriggers()
		{
		}

		GamePadTriggers::GamePadTriggers(const GamePadTriggers &obj)
		{
			Left = obj.Left;
			Right = obj.Right;
		}

		bool GamePadTriggers::Equals(const GamePadTriggers obj)
		{
			return (Left == obj.Left) && (Right == obj.Right);
		}

		int GamePadTriggers::GetHashCode()
		{
			return (int)Left ^ (int)Right;
		}

		bool GamePadTriggers::operator!=(const GamePadTriggers other)
		{
			return !Equals(other);
		}

		bool GamePadTriggers::operator==(const GamePadTriggers other)
		{
			return Equals(other);
		}
	}
}
