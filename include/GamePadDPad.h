/********************************************************
 *	GamePadDPad.h										*
 *														*
 *	XFX GamePadDPad definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef GAMEPADDPAD_H
#define GAMEPADDPAD_H

#include "ButtonState.h"

namespace XFX
{
	namespace Input
	{
		struct GamePadDPad
		{
			ButtonState Down;
			ButtonState Left;
			ButtonState Right;
			ButtonState Up;
	
			int operator!=(const GamePadDPad &other)
			{
				return !((Down == other.Down) && (Left == other.Left) &&
					(Right == other.Right) && (Up == other.Up));
			}
			int operator==(const GamePadDPad &other)
			{
				return ((Down == other.Down) && (Left == other.Left) &&
					(Right == other.Right) && (Up == other.Up));
			}
		};
	}
}

#endif //GAMEPADDPAD_H
