/********************************************************
 *	GamePadButtons.h									*
 *														*
 *	XFX GamePadButtons definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_INPUT_GAMEPADBUTTONS_
#define _XFX_INPUT_GAMEPADBUTTONS_

#include "Enums.h"
#include <Vector2.h>

namespace XFX
{
	namespace Input
	{
		/// <summary>
		/// Identifies whether the buttons on an Xbox Controller are pressed or released.
		/// </summary>
		struct GamePadButtons
		{
			ButtonState_t A;
			ButtonState_t B;
			ButtonState_t Back;
			ButtonState_t Black;
			ButtonState_t LeftStick;
			ButtonState_t RightStick;
			ButtonState_t Start;
			ButtonState_t White;
			ButtonState_t X;
			ButtonState_t Y;
			
			bool GamePadButtons::operator!=(const GamePadButtons other)
			{
				return !((A == other.A) && (B == other.B) && (Back == other.Back) && 
					(Black == other.Black) && (LeftStick == other.LeftStick) &&
					(RightStick == other.RightStick) && (Start == other.Start) &&
					(White == other.White) && (X == other.X) && (Y == other.Y));		
			}
			
			bool GamePadButtons::operator==(const GamePadButtons other)
			{
				return ((A == other.A) && (B == other.B) && (Back == other.Back) && 
					(Black == other.Black) && (LeftStick == other.LeftStick) &&
					(RightStick == other.RightStick) && (Start == other.Start) &&
					(White == other.White) && (X == other.X) && (Y == other.Y));
			}
		};
	
		/// <summary>
		/// Identifies which directions on the directional pad of an Xbox Controller are being pressed.
		/// </summary>
		struct GamePadDPad
		{
			ButtonState_t Down;
			ButtonState_t Left;
			ButtonState_t Right;
			ButtonState_t Up;

			GamePadDPad(ButtonState_t upValue, ButtonState_t downValue, ButtonState_t leftValue, ButtonState_t rightValue);
			GamePadDPad();
			GamePadDPad(const GamePadDPad &other);

			bool Equals(const GamePadDPad other);
			int GetHashCode();
			
			bool GamePadDPad::operator!=(const GamePadDPad other)
			{
				return !Equals(other);
			}
			
			bool GamePadDPad::operator==(const GamePadDPad other)
			{
				return Equals(other);
			}
		};

		/// <summary>
		/// Structure that represents the position of left and right sticks (thumbsticks) on an Xbox Controller.
		/// </summary>
		struct GamePadThumbSticks
		{
			Vector2 Left;
			Vector2 Right;

			GamePadThumbSticks(Vector2 leftThumbstick, Vector2 rightThumbstick);
			GamePadThumbSticks();
			GamePadThumbSticks(const GamePadThumbSticks &obj);

			bool Equals(const GamePadThumbSticks obj);
			int GetHashCode();

			bool operator!=(GamePadThumbSticks other);
			bool operator==(GamePadThumbSticks other);
		};

		/// <summary>
		/// Structure that defines the position of the left and right triggers on an Xbox Controller.
		/// </summary>
		struct GamePadTriggers
		{
			float Left;
			float Right;

			GamePadTriggers(float left, float right);
			GamePadTriggers();
			GamePadTriggers(const GamePadTriggers &obj);

			bool Equals(const GamePadTriggers obj);
			int GetHashCode();

			bool operator!=(const GamePadTriggers other);
			bool operator==(const GamePadTriggers other);
		};
	}
}

#endif //_XFX_INPUT_GAMEPADBUTTONS_
