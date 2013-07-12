/*****************************************************************************
 *	GamePadDPad.h															 *
 *																			 *
 *	XFX::Input::GamePadDPad structure definition file						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_INPUT_GAMEPADDPAD_
#define _XFX_INPUT_GAMEPADDPAD_

#include "Enums.h"
#include <System/Object.h>

using namespace System;

namespace XFX
{
	namespace Input
	{
		/**
		 * Identifies which directions on the directional pad of an Xbox Controller are being pressed.
		 */
		struct GamePadDPad : Object
		{
			const ButtonState_t Down;
			const ButtonState_t Left;
			const ButtonState_t Right;
			const ButtonState_t Up;

			GamePadDPad(const ButtonState_t upValue, const ButtonState_t downValue, const ButtonState_t leftValue, const ButtonState_t rightValue);
			GamePadDPad();
			GamePadDPad(const GamePadDPad &obj);

			bool Equals(Object const * const obj) const;
			bool Equals(const GamePadDPad obj) const;
			int GetHashCode() const;
			static const Type& GetType();
			const String ToString() const;
			
			bool operator!=(const GamePadDPad& right) const;
			bool operator==(const GamePadDPad& right) const;

			inline GamePadDPad operator=(const GamePadDPad& right)
			{
				return (right == *this) ? *this : GamePadDPad(right);
			}
		};
	}
}

#endif //_XFX_INPUT_GAMEPADDPAD_
