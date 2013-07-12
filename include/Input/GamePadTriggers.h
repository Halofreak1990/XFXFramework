/*****************************************************************************
 *	GamePadTriggers.h														 *
 *																			 *
 *	XFX::Input::GamePadTriggers structure definition file					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_INPUT_GAMEPADTRIGGERS_
#define _XFX_INPUT_GAMEPADTRIGGERS_

#include <System/Object.h>

using namespace System;

namespace XFX
{
	namespace Input
	{
		/**
		 * Structure that defines the position of the left and right triggers on an Xbox Controller.
		 */
		struct GamePadTriggers : Object
		{
			const float Left;
			const float Right;

			GamePadTriggers(const float left, const float right);
			GamePadTriggers();
			GamePadTriggers(const GamePadTriggers &obj);

			bool Equals(Object const * const obj) const;
			bool Equals(const GamePadTriggers obj) const;
			int GetHashCode() const;
			static const Type& GetType();
			const String ToString() const;

			bool operator!=(const GamePadTriggers& right) const;
			bool operator==(const GamePadTriggers& right) const;

			inline GamePadTriggers operator=(const GamePadTriggers& right)
			{
				return (right == *this) ? *this : GamePadTriggers(right);
			}
		};
	}
}

#endif //_XFX_INPUT_GAMEPADTRIGGERS_
