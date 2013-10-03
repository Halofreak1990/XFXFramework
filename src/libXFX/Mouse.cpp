// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

extern "C" {
#include <hal/mouse.h>
}

#include <Input/Mouse.h>

namespace XFX
{
	namespace Input
	{
		extern "C"{
			extern struct xmouse_data XMOUSE_current;
		}
		
		// It's a waste of memory to create a new MouseState each time the input states are updated.
		// Therefore, we create a static one and update it each time an update is requested.
		static MouseState result;
		
		/* MouseState Operators */
		bool MouseState::operator!=(const MouseState& other) const
		{
			return !((LeftButton == other.LeftButton) && (MiddleButton == other.MiddleButton) &&
				(RightButton == other.RightButton) && (X == other.X) && (XButton1 == other.XButton1) &&
				(XButton2 == other.XButton2) && (Y == other.Y));
		}
		
		bool MouseState::operator==(const MouseState& other) const
		{
			return ((LeftButton == other.LeftButton) && (MiddleButton == other.MiddleButton) &&
				(RightButton == other.RightButton) && (X == other.X) && (XButton1 == other.XButton1) &&
				(XButton2 == other.XButton2) && (Y == other.Y));
		}
		/* END Mousestate Operators */
		
		MouseState Mouse::GetState()
		{
			result.X += XMOUSE_current.x;
			result.Y += XMOUSE_current.y;
			XMOUSE_current.x = 0;
			XMOUSE_current.y = 0;
			
			if((XMOUSE_current.buttons & XMOUSE_BUTTON_1))
			{
				result.LeftButton = ButtonState::Pressed;
			}
			else
			{
				result.LeftButton = ButtonState::Released;
			}

			if((XMOUSE_current.buttons & XMOUSE_BUTTON_3))
			{
				result.MiddleButton = ButtonState::Pressed;
			}
			else
			{
				result.MiddleButton = ButtonState::Released;
			}

			if((XMOUSE_current.buttons & XMOUSE_BUTTON_2))
			{
				result.RightButton = ButtonState::Pressed;
			}
			else
			{
				result.RightButton = ButtonState::Released;
			}

			if((XMOUSE_current.buttons & XMOUSE_BUTTON_4))
			{
				result.XButton1 = ButtonState::Pressed;
			}
			else
			{
				result.XButton1 = ButtonState::Released;
			}

			if((XMOUSE_current.buttons & XMOUSE_BUTTON_5))
			{
				result.XButton2 = ButtonState::Pressed;
			}
			else
			{
				result.XButton2 = ButtonState::Released;
			}
			
			return result;
		}
		
		void Mouse::SetPosition(int x, int y)
		{
			result.X = x;
			result.Y = y;

			// TODO: update 'hardware' cursor
		}
	}
}
