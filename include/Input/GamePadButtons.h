/*****************************************************************************
 *	GamePadButtons.h														 *
 *																			 *
 *	XFX::Input::GamePadButtons definition file  							 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_INPUT_GAMEPADBUTTONS_
#define _XFX_INPUT_GAMEPADBUTTONS_

#include "Enums.h"
#include <System/Object.h>
#include <Vector2.h>

using namespace System;

namespace XFX
{
	namespace Input
	{
		// Identifies whether the buttons on an Xbox Controller are pressed or released.
		struct GamePadButtons : Object
		{
			const ButtonState_t A;
			const ButtonState_t B;
			const ButtonState_t Back;
			const ButtonState_t Black;
			const ButtonState_t LeftStick;
			const ButtonState_t RightStick;
			const ButtonState_t Start;
			const ButtonState_t White;
			const ButtonState_t X;
			const ButtonState_t Y;
			
			GamePadButtons(const uint /* Buttons */ buttons);
			GamePadButtons();
			GamePadButtons(const GamePadButtons &obj);

			bool Equals(Object const * const obj) const;
			bool Equals(const GamePadButtons obj) const;
			int GetHashCode() const;
			static int GetType();
			const String& ToString() const;

			bool operator !=(const GamePadButtons& right) const;
			bool operator ==(const GamePadButtons& right) const;

			inline GamePadButtons operator=(const GamePadButtons& right)
			{
				return (right == *this) ? *this : GamePadButtons(right);
			}
		};
	
		// Identifies which directions on the directional pad of an Xbox Controller are being pressed.
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
			static int GetType();
			const String& ToString() const;
			
			bool operator!=(const GamePadDPad& right) const;
			bool operator==(const GamePadDPad& right) const;

			inline GamePadDPad operator=(const GamePadDPad& right)
			{
				return (right == *this) ? *this : GamePadDPad(right);
			}
		};

		// Structure that represents the position of left and right sticks (thumbsticks) on an Xbox Controller.
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
			static int GetType();
			const String& ToString() const;

			bool operator!=(const GamePadThumbSticks& right) const;
			bool operator==(const GamePadThumbSticks& right) const;

			inline GamePadThumbSticks operator=(const GamePadThumbSticks& right)
			{
				return (right == *this) ? *this : GamePadThumbSticks(right);
			}
		};

		// Structure that defines the position of the left and right triggers on an Xbox Controller.
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
			static int GetType();
			const String& ToString() const;

			bool operator!=(const GamePadTriggers& right) const;
			bool operator==(const GamePadTriggers& right) const;

			inline GamePadTriggers operator=(const GamePadTriggers& right)
			{
				return (right == *this) ? *this : GamePadTriggers(right);
			}
		};
	}
}

#endif //_XFX_INPUT_GAMEPADBUTTONS_
