// Copyright (C) 2010-2012, XFX Team
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

#include <Graphics/Color.h>
#include <Graphics/DepthStencilBuffer.h>
#include <Graphics/GraphicsDevice.h>
#include <Matrix.h>
#include <Quaternion.h>

#ifdef ENABLE_XBOX
#include "pbKit.h"
#else
#include "gl.h"
#endif

using namespace System;
using namespace XFX;

namespace XFX
{
	namespace Graphics
	{
		TextureCollection GraphicsDevice::Textures()
		{
			return textures;
		}

#if ENABLE_XBOX
		GraphicsDevice::GraphicsDevice(GraphicsAdapter adapter, DeviceType_t deviceType, CreateOptions_t creationOptions, PresentationParameters presentationParameters)
		{
			_adapter = adapter;
			if(_deviceType != DeviceType::Hardware)
				throw DeviceNotSupportedException("Only DeviceType::Hardware is supported.");

			_deviceType = devicetype;
			clearColor = Color::Black;
		}
#else
		GraphicsDevice::GraphicsDevice(GraphicsAdapter adapter, DeviceType_t deviceType, IntPtr renderWindowHandle, PresentationParameters presentationParameters)
		{
			_adapter = adapter;
			_deviceType = devicetype;
			clearColor = Color::Black;
		}
#endif
		
		GraphicsDevice::GraphicsDevice()
		{
			
		}
		
		GraphicsDevice::~GraphicsDevice()
		{
			Dispose(false);
		}
		
		void GraphicsDevice::Clear(Color color)
		{
#ifdef ENABLE_XBOX
			DWORD		*p;
			DWORD		format;
			DWORD		depth;
			
			int		x1,y1,x2,y2;
			
			//Set the coordinates for the rectangle to be cleared
			x1 = 0;
			y1 = 0;
			x2 = x1 + _depthStencilBuffer.Width();
			y2 = y1 + _depthStencilBuffer.Height();
			
			switch(_depthStencilBuffer.Format())
			{
				case DepthFormat::Depth24Stencil4: {format = 0x03; depth = 0xffffff0;}
				case DepthFormat::Depth24Stencil8: {format = 0x03; depth = 0xffffff00;}
				case DepthFormat::Depth32: {format = 0x03; depth = 0xffffffff;}
				case DepthFormat::Unknown:
				default: return;
			}
			
			p=pb_begin();
			pb_push(p++,NV20_TCL_PRIMITIVE_3D_CLEAR_VALUE_HORIZ,2);		//sets rectangle coordinates
			*(p++)=((x2-1)<<16)|x1;
			*(p++)=((y2-1)<<16)|y1;
			pb_push(p++,NV20_TCL_PRIMITIVE_3D_CLEAR_VALUE_DEPTH,3);		//sets data used to fill in rectangle
			*(p++)=depth;				//depth to clear
			*(p++)=color.PackedValue();	//color
			*(p++)=format;				//triggers the HW rectangle fill (only on D&S)
			pb_end(p);

			if(color != clearColor)
				clearColor = color;
#else
			if(color != clearColor)
			{
				glClearColor((float)color.R/255f, (float)color.G/255f, (float)color.B/255f, (float)color.A/255f);
				clearColor = color;
			}
			glClear(GL_COLOR_BUFFER_BIT);
			glLoadIdentity();
#endif
		}

		void GraphicsDevice::Clear(ClearOptions_t options, Color color, float depth, int stencil)
		{
			if(isDisposed)
				throw ObjectDisposedException();

			switch(options)
			{
			case ClearOptions::Depth:
				{
#if ENABLE_XBOX
#else
#endif
				}
			case ClearOptions::Stencil:
				{
#if ENABLE_XBOX
#else
#endif
				}
			case ClearOptions::Target:
				{
#if ENABLE_XBOX
#else
#endif
				}

			}
		}
		
		void GraphicsDevice::Dispose()
		{
			Dispose(true);
		}
		
		void GraphicsDevice::Dispose(bool disposing)
		{
			if(disposing)
			{
				
			}
		}
	}
}
