/********************************************************
 *	Mouse.h												*
 *														*
 *	XFX Mouse definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_INPUT_MOUSE_
#define _XFX_INPUT_MOUSE_

#include "Enums.h"
#include <System/Types.h>

using namespace System;

namespace XFX
{
	namespace Input
	{
		/// <summary>
		/// 
		/// </summary>
		struct MouseState
		{
			ButtonState_t LeftButton;
			ButtonState_t MiddleButton;
			ButtonState_t RightButton;
			int X;
			ButtonState_t XButton1;
			ButtonState_t XButton2;
			int Y;
			
			bool operator!=(const MouseState other);
			bool operator==(const MouseState other);
		};
		
		/// <summary>
		/// Allows retrieval of position and button clicks from a mouse input device.
		/// </summary>
		class Mouse
		{
		public:
			static MouseState GetState();
			static void SetPosition(int x, int y);
		};
	}
}

#endif //_XFX_INPUT_MOUSE_
