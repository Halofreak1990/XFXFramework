// Copyright (C) 2010-2012, Halofreak_1990
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
#ifdef ENABLE_XBOX
#include <hal/input.h>
#else
#endif
}

#include <input/Keyboard.h>

namespace XFX
{
	namespace Input
	{
		int GetArrLength(unsigned char arr[])
		{
			return sizeof(arr) / sizeof(unsigned char);
		}
		
		XKEYBOARD_STROKE Stroke;

		//It's a waste of memory to create a new KeyboardState each time the input states are updated.
		//Therefore, we create a static one and update it each time an update is requested.
		static KeyboardState result;
		
		//Initializes the KeyboardState class
		KeyboardState::KeyboardState()
		{
		}
		
		//Initializes the KeyboardState class with the specified keys pressed
		KeyboardState::KeyboardState(unsigned char keys[])
		{
			
		}
		
		unsigned char *KeyboardState::GetPressedKeys()
		{
			
		}
		
		//Returns whether the specified key is currently pressed
		bool KeyboardState::IsKeyDown(unsigned char key)
		{
			if(XInputGetKeystroke(&Stroke) == 0){
				if((Stroke.ucFlags & key) == 0){
					return true;
				}	
				return false;	
			}
			//We should never get here unless the input system doesn't work
			return -1;
		}
		
		//Returns whether the specified key is NOT pressed
		bool KeyboardState::IsKeyUp(unsigned char key)
		{
			if(XInputGetKeystroke(&Stroke) == 0){
				if((Stroke.ucFlags & key) != 0){
					return true;
				}	
				return false;	
			}
			//We should never get here unless the input system doesn't work
			return -1;
		}
		
		//Gets the state of the keyboard
		KeyboardState Keyboard::GetState()
		{
			return result;
		}
	}
}
