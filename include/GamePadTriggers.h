/********************************************************
 *	GamePadTriggers.h									*
 *														*
 *	XFX GamePadTriggers definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef GAMEPADTRIGGERS_H
#define GAMEPADTRIGGERS_H

namespace XFX
{
	namespace Input
	{
		struct GamePadTriggers
		{
			float Left;
			float Right;

			int operator!=(const GamePadTriggers &other)
			{
				return !((Left == other.Left) && (Right == other.Right));
			}
			int operator==(const GamePadTriggers &other)
			{
				return ((Left == other.Left) && (Right == other.Right));
			}
		};
	}
}

#endif //GAMEPADTRIGGERS_H
