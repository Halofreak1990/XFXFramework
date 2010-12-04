/********************************************************
 *	GamePadButtons.h									*
 *														*
 *	XFX GamePadButtons definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _GAMEPADBUTTONS_
#define _GAMEPADBUTTONS_

#include "Enums.h"

namespace XFX
{
	namespace Input
	{
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
			
			bool GamePadButtons::operator!=(const GamePadButtons &other)
			{
				return !((A == other.A) && (B == other.B) && (Back == other.Back) && 
					(Black == other.Black) && (LeftStick == other.LeftStick) &&
					(RightStick == other.RightStick) && (Start == other.Start) &&
					(White == other.White) && (X == other.X) && (Y == other.Y));		
			}
			
			bool GamePadButtons::operator==(const GamePadButtons &other)
			{
				return ((A == other.A) && (B == other.B) && (Back == other.Back) && 
					(Black == other.Black) && (LeftStick == other.LeftStick) &&
					(RightStick == other.RightStick) && (Start == other.Start) &&
					(White == other.White) && (X == other.X) && (Y == other.Y));
			}
		};
	
		struct GamePadDPad
		{
			ButtonState_t Down;
			ButtonState_t Left;
			ButtonState_t Right;
			ButtonState_t Up;
			
			bool GamePadDPad::operator!=(const GamePadDPad &other)
			{
				return !((Down == other.Down) && (Left == other.Left) &&
					(Right == other.Right) && (Up == other.Up));
			}
			
			bool GamePadDPad::operator==(const GamePadDPad &other)
			{
				return ((Down == other.Down) && (Left == other.Left) &&
					(Right == other.Right) && (Up == other.Up));
			}
		};
	}
}

#endif //_GAMEPADBUTTONS_
