/*****************************************************************************
 *	GamePadThumbSticks.h													 *
 *																			 *
 *	XFX::Input::GamePadThumbSticks structure definition file				 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_INPUT_GAMEPADTHUMBSTICKS_
#define _XFX_INPUT_GAMEPADTHUMBSTICKS_

#include "Enums.h"
#include <Vector2.h>

using namespace System;

namespace XFX
{
	namespace Input
	{
		/**
		 * Structure that represents the position of left and right sticks (thumbsticks) on an Xbox Controller.
		 */
		struct GamePadThumbSticks : Object
		{
			const Vector2 Left;
			const Vector2 Right;

			GamePadThumbSticks(const Vector2 leftThumbstick, const Vector2 rightThumbstick);
			GamePadThumbSticks();
			GamePadThumbSticks(const GamePadThumbSticks &obj);

			bool Equals(Object const * const obj) const;
			bool Equals(const GamePadThumbSticks obj) const;
			int GetHashCode() const;
			static const Type& GetType();
			const String ToString() const;

			bool operator!=(const GamePadThumbSticks& right) const;
			bool operator==(const GamePadThumbSticks& right) const;

			inline GamePadThumbSticks operator=(const GamePadThumbSticks& right)
			{
				return (right == *this) ? *this : GamePadThumbSticks(right);
			}
		};
	}
}

#endif //_XFX_INPUT_GAMEPADTHUMBSTICKS_
