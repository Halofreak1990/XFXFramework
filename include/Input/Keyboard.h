/********************************************************
 *	Keyboard.h											*
 *														*
 *	XFX Keyboard definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_INPUT_KEYBOARD_
#define _XFX_INPUT_KEYBOARD_

#include "Enums.h"
#include "Keys.h"

namespace XFX
{
	namespace Input
	{
		/// <summary>
		/// Represents a state of keystrokes recorded by a keyboard input device.
		/// </summary>
		struct KeyboardState
		{
			KeyboardState();
			KeyboardState(unsigned char keys[]);
				
			unsigned char* GetPressedKeys();
			bool IsKeyDown(unsigned char key);
			bool IsKeyUp(unsigned char key);
		};

		/// <summary>
		/// Allows retrieval of keystrokes from a keyboard input device.
		/// </summary>
		class Keyboard
		{
		public:
			static KeyboardState GetState();
		};
	}
}

#endif //_XFX_INPUT_KEYBOARD_
