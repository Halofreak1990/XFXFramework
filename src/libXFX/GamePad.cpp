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
#include <System/String.h>

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

		GamePadState GamePad::GetState(const PlayerIndex_t playerIndex)
		{
			XInput_GetEvents();

			//Update IsConnected
			g_State.IsConnected = g_Pads[playerIndex].hPresent;
			
			//Update Button presses
			g_State.Buttons = GamePadButtons(
				((g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_A]) ? Buttons::A : 0) |
				((g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_B]) ? Buttons::B : 0) |
				((g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_BACK) ? Buttons::Back : 0) |
				((g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_BLACK]) ? Buttons::Black : 0) |
				((g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_LEFT_THUMB) ? Buttons::LeftStick : 0) |
				((g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_RIGHT_THUMB) ? Buttons::RightStick : 0) |
				((g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_START) ? Buttons::Start : 0) |
				((g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_WHITE]) ? Buttons::White : 0) |
				((g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_X]) ? Buttons::X : 0) |
				((g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_Y]) ? Buttons::Y : 0));
				
			g_State.Triggers = GamePadTriggers(g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_LEFT_TRIGGER],
												g_Pads[playerIndex].PressedButtons.ucAnalogButtons[XPAD_RIGHT_TRIGGER]);

			//Update DPad
			g_State.DPad = GamePadDPad(
				(g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_DPAD_UP) ? ButtonState::Pressed : ButtonState::Released,
				(g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_DPAD_DOWN) ? ButtonState::Pressed : ButtonState::Released,
				(g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_DPAD_LEFT) ? ButtonState::Pressed : ButtonState::Released,
				(g_Pads[playerIndex].CurrentButtons.usDigitalButtons & XPAD_DPAD_RIGHT) ? ButtonState::Pressed : ButtonState::Released);
			
			Vector2 leftThumbStick = Vector2(g_Pads[playerIndex].sLThumbX, g_Pads[playerIndex].sLThumbY);
			Vector2 rightThumbStick = Vector2(g_Pads[playerIndex].sRThumbX, g_Pads[playerIndex].sRThumbY);

			g_State.ThumbSticks = GamePadThumbSticks(leftThumbStick, rightThumbStick);

			return g_State; 
		}
		
		bool GamePad::SetVibration(const PlayerIndex_t playerIndex, const float leftMotor, const float rightMotor)
		{
			//If the controller is Disconnected, why bother?
			if(GetState(playerIndex).IsConnected == false)
			{
				return false;
			}
			else
			{
				byte leftSpeed = (byte)(MathHelper::Clamp(leftMotor, 0.0f, 1.0f) * 255);
				byte rightSpeed = (byte)(MathHelper::Clamp(rightMotor, 0.0f, 1.0f) * 255);

				//Can't do anything yet, since we can't send anything through the OpenXDK Input lib
				return true;
			}
		}

		GamePadState::GamePadState()
		{
		}

		GamePadState::GamePadState(const GamePadThumbSticks thumbSticks, const GamePadTriggers triggers, const GamePadButtons buttons, const GamePadDPad dpad)
			: Buttons(buttons), DPad(dpad), ThumbSticks(thumbSticks), Triggers(triggers)
		{
		}

		GamePadState::GamePadState(const GamePadState &obj)
			: Buttons(obj.Buttons), DPad(obj.DPad), IsConnected(obj.IsConnected), ThumbSticks(obj.ThumbSticks), Triggers(obj.Triggers)
		{
		}

		bool GamePadState::Equals(const Object* obj) const
		{
			return is(obj, this) ? this->Equals(*(GamePadState*)obj) : false;
		}

		bool GamePadState::Equals(const GamePadState obj) const
		{
			return (*this == obj);
		}

		int GamePadState::GetHashCode() const
		{
			return (Buttons.GetHashCode() + DPad.GetHashCode() ^ ThumbSticks.GetHashCode() ^ Triggers.GetHashCode());
		}

		int GamePadState::GetType() const
		{
		}

		bool GamePadState::IsButtonDown(const Buttons_t button) const
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

		bool GamePadState::IsButtonUp(const Buttons_t button) const
		{
			return !IsButtonDown(button);
		}

		const char* GamePadState::ToString() const
		{
			return String::Format("{{IsConnected:%b}}", IsConnected);
		}

		bool GamePadState::operator ==(const GamePadState& right) const
		{
			return ((Buttons == right.Buttons) && (DPad == right.DPad) &&
					(ThumbSticks == right.ThumbSticks) && (Triggers == right.Triggers));
		}

		bool GamePadState::operator !=(const GamePadState& right) const
		{
			return ((Buttons != right.Buttons) || (DPad != right.DPad) ||
					(ThumbSticks != right.ThumbSticks) || (Triggers != right.Triggers));
		}

		GamePadButtons::GamePadButtons(const uint /* Buttons_t */ buttons)
			: A((((buttons & Buttons::A) != 0) ? ButtonState::Pressed : ButtonState::Released)),
			B((((buttons & Buttons::B) != 0) ? ButtonState::Pressed : ButtonState::Released)),
			Back((((buttons & Buttons::Back) != 0) ? ButtonState::Pressed : ButtonState::Released)),
			Black((((buttons & Buttons::Black) != 0) ? ButtonState::Pressed : ButtonState::Released)),
			LeftStick((((buttons & Buttons::LeftStick) != 0) ? ButtonState::Pressed : ButtonState::Released)),
			RightStick((((buttons & Buttons::RightStick) != 0) ? ButtonState::Pressed : ButtonState::Released)),
			Start((((buttons & Buttons::Start) != 0) ? ButtonState::Pressed : ButtonState::Released)),
			White((((buttons & Buttons::White) != 0) ? ButtonState::Pressed : ButtonState::Released)),
			X((((buttons & Buttons::X) != 0) ? ButtonState::Pressed : ButtonState::Released)),
			Y((((buttons & Buttons::Y) != 0) ? ButtonState::Pressed : ButtonState::Released))
		{
		}

		GamePadButtons::GamePadButtons()
			: A(ButtonState::Released), B(ButtonState::Released),
			Back(ButtonState::Released), Black(ButtonState::Released),
			LeftStick(ButtonState::Released), RightStick(ButtonState::Released),
			Start(ButtonState::Released), White(ButtonState::Released),
			X(ButtonState::Released), Y(ButtonState::Released)
		{
		}

		GamePadButtons::GamePadButtons(const GamePadButtons &obj)
			: A(obj.A), B(obj.B), Back(obj.Back), Black(obj.Black),
			LeftStick(obj.LeftStick), RightStick(obj.RightStick),
			Start(obj.Start), White(obj.White), X(obj.X), Y(obj.Y)
		{
		}

		bool GamePadButtons::Equals(const Object* obj) const
		{
			return is(obj, this) ? this->Equals(*(GamePadButtons*)obj) : false;
		}

		bool GamePadButtons::Equals(const GamePadButtons other) const
		{
			return (*this == other);
		}

		int GamePadButtons::GetHashCode() const
		{
			return (A + B + Back + Black + LeftStick + RightStick + 
				Start + White + X + Y);
		}

		int GamePadButtons::GetType() const
		{
		}

		const char* GamePadButtons::ToString() const
		{
			String str = "";
			if (A == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "A";
			}
			if (B == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "B";
			}
			if (X == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "X";
			}
			if (Y == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "Y";
			}
			if (White == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "White";
			}
			if (Black == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "Black";
			}
			if (LeftStick == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "LeftStick";
			}
			if (RightStick == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "RightStick";
			}
			if (Start == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "Start";
			}
			if (Back == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "Back";
			}
			if (str.Length == 0)
			{
				str = "None";
			}

			return String::Format("{{Buttons:%s}}", str.ToString());
		}

		bool GamePadButtons::operator!=(const GamePadButtons& other) const
		{
			return ((A != other.A) || (B != other.B) || (Back != other.Back) ||
				(Black != other.Black) || (LeftStick != other.LeftStick) ||
				(RightStick != other.RightStick) || (Start != other.Start) ||
				(White != other.White) || (X != other.X) || (Y != other.Y));		
		}
		
		bool GamePadButtons::operator==(const GamePadButtons& other) const
		{
			return ((A == other.A) && (B == other.B) && (Back == other.Back) && 
				(Black == other.Black) && (LeftStick == other.LeftStick) &&
				(RightStick == other.RightStick) && (Start == other.Start) &&
				(White == other.White) && (X == other.X) && (Y == other.Y));
		}

		GamePadDPad::GamePadDPad()
			: Down(ButtonState::Released), Left(ButtonState::Released), Right(ButtonState::Released), Up(ButtonState::Released)
		{
		}

		GamePadDPad::GamePadDPad(const ButtonState_t upValue, const ButtonState_t downValue, const ButtonState_t leftValue, const ButtonState_t rightValue)
			: Down(downValue), Left(leftValue), Right(rightValue), Up(upValue)
		{
		}

		GamePadDPad::GamePadDPad(const GamePadDPad &obj)
			: Down(obj.Down), Left(obj.Left), Right(obj.Right), Up(obj.Up)
		{
		}

		bool GamePadDPad::Equals(const Object* obj) const
		{
			return is(obj, this) ? this->Equals(*(GamePadDPad*)obj) : false;
		}

		bool GamePadDPad::Equals(const GamePadDPad obj) const
		{
			return (*this == obj);
		}

		int GamePadDPad::GetHashCode() const
		{
			return Down + Left + Right + Up;
		}

		int GamePadDPad::GetType() const
		{
		}

		const char* GamePadDPad::ToString() const
		{
			String str = "";
			if (Up == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "Up";
			}
			if (Down == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "Down";
			}
			if (Left == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "Left";
			}
			if (Right == ButtonState::Pressed)
			{
				str = str + ((str.Length != 0) ? " " : "") + "Right";
			}
			if (str.Length == 0)
			{
				str = "None";
			}

			return String::Format("{{DPad:%s}}", str.ToString());
		}

		bool GamePadDPad::operator !=(const GamePadDPad& right) const
		{
			return ((Down != right.Down) || (Left != right.Left) ||
					(Right != right.Right) || (Up != right.Up));
		}

		bool GamePadDPad::operator ==(const GamePadDPad& right) const
		{
			return ((Down == right.Down) && (Left == right.Left) &&
					(Right == right.Right) && (Up == right.Up));
		}

		GamePadThumbSticks::GamePadThumbSticks(const Vector2 leftThumbstick, const Vector2 rightThumbstick)
			: Left(leftThumbstick), Right(rightThumbstick)
		{
		}

		GamePadThumbSticks::GamePadThumbSticks()
			: Left(Vector2::Zero), Right(Vector2::Zero)
		{
		}

		GamePadThumbSticks::GamePadThumbSticks(const GamePadThumbSticks &obj)
			: Left(obj.Left), Right(obj.Right)
		{
		}

		bool GamePadThumbSticks::Equals(const Object* obj) const
		{
			return is(obj, this) ? this->Equals(*(GamePadThumbSticks*)obj) : false;
		}

		bool GamePadThumbSticks::Equals(const GamePadThumbSticks obj) const
		{
			return (*this == obj);
		}

		int GamePadThumbSticks::GetHashCode() const
		{
			return Left.GetHashCode() ^ Right.GetHashCode();
		}

		int GamePadThumbSticks::GetType() const
		{
		}

		const char* GamePadThumbSticks::ToString() const
		{
			return String::Format("{{Left:%s Right%s}}", Left.ToString(), Right.ToString());
		}

		bool GamePadThumbSticks::operator!=(const GamePadThumbSticks& other) const
		{
			return (Left != other.Left) || (Right != other.Right);
		}

		bool GamePadThumbSticks::operator==(const GamePadThumbSticks& other) const
		{
			return (Left == other.Left) && (Right == other.Right);
		}

		GamePadTriggers::GamePadTriggers(const float left, const float right)
			: Left(left), Right(right)
		{
		}

		GamePadTriggers::GamePadTriggers()
			: Left(0), Right(0)
		{
		}

		GamePadTriggers::GamePadTriggers(const GamePadTriggers &obj)
			: Left(obj.Left), Right(obj.Right)
		{
		}

		bool GamePadTriggers::Equals(const Object* obj) const
		{
			return is(obj, this) ? this->Equals(*(GamePadTriggers*)obj) : false;
		}

		bool GamePadTriggers::Equals(const GamePadTriggers obj) const
		{
			return (*this == obj);
		}

		int GamePadTriggers::GetHashCode() const
		{
			return (int)Left ^ (int)Right;
		}

		int GamePadTriggers::GetType() const
		{
		}

		const char* GamePadTriggers::ToString() const
		{
			return String::Format("{{Left:%f Right:%f}}", Left, Right);
		}

		bool GamePadTriggers::operator!=(const GamePadTriggers& other) const
		{
			return (Left != other.Left) || (Right != other.Right);
		}

		bool GamePadTriggers::operator==(const GamePadTriggers& other) const
		{
			return (Left == other.Left) && (Right == other.Right);
		}
	}
}
