/********************************************************
 *	GamePadThumbSticks.h								*
 *														*
 *	XFX GamePadThumbSticks definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef GAMEPADTHUMBSTICKS_H
#define GAMEPADTHUMBSTICKS_H

#include "Vector2.h"

namespace XFX
{
	namespace Input
	{
		struct GamePadThumbSticks
		{
			Vector2 Left;
			Vector2 Right;

			int GamePadThumbSticks::operator!=(const GamePadThumbSticks &other)
			{
				return !((Left == other.Left) && (Right == other.Right));
			}
			
			int GamePadThumbSticks::operator==(const GamePadThumbSticks &other)
			{
				return ((Left == other.Left) && (Right == other.Right));
			}
		};
	}
}

#endif //GAMEPADTHUMBSTICKS_H
