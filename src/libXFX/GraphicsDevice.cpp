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
#include <System/FrameworkResources.h>
#include <System/String.h>
#include <Matrix.h>
#include <Quaternion.h>
#include <Rectangle.h>
#include <Vector2.h>
#include <Vector4.h>

extern "C" {
#include "pbKit.h"
}

#include <sassert.h>

using namespace System;
using namespace XFX;

namespace XFX
{
	namespace Graphics
	{
		DepthStencilBuffer GraphicsDevice::getDepthStencilBuffer()
		{
			return _depthStencilBuffer;
		}

		void GraphicsDevice::setDepthStencilBuffer(DepthStencilBuffer buffer)
		{
			_depthStencilBuffer = buffer;
		}

		PresentationParameters* GraphicsDevice::getPresentationParameters()
		{
			return p_cachedParameters;
		}

		void GraphicsDevice::setPresentationParameters(PresentationParameters* presentationParameters)
		{
			DWORD* p = pb_begin();

			viewport.X = 0;
			viewport.Y = 0;
			viewport.Width = presentationParameters->BackBufferWidth;
			viewport.Height = presentationParameters->BackBufferHeight;

			if (presentationParameters->BackBufferFormat == SurfaceFormat::Color ||
				presentationParameters->BackBufferFormat == SurfaceFormat::Bgr32 ||
				presentationParameters->BackBufferFormat == SurfaceFormat::Rgba32)
			{
				
			}

			if (presentationParameters->EnableAutoDepthStencil)
			{
				if (presentationParameters->AutoDepthStencilFormat == DepthFormat::Depth16)
					;
			}
		}

		TextureCollection GraphicsDevice::getTextures()
		{
			return textures;
		}

		Viewport GraphicsDevice::getViewport() const
		{
			return viewport;
		}

		void GraphicsDevice::setViewport(Viewport value)
		{
			if (viewport != value)
			{
				viewport = value;
				pb_set_viewport(viewport.X, viewport.Y, viewport.Width, viewport.Height, viewport.MinDepth, viewport.MaxDepth);
			}
		}

		GraphicsDevice::GraphicsDevice(GraphicsAdapter* adapter, const DeviceType_t deviceType, PresentationParameters* presentationParameters)
		{
			//sassert(adapter != null, String::Format("adapter; %s", FrameworkResources::ArgumentNull_Generic));

			//sassert(presentationParameters != null, String::Format("presentationParameters; %s", FrameworkResources::ArgumentNull_Generic));

			//graphicsDeviceCapabilities = adapter->

			//_adapter = adapter;

			sassert(deviceType == DeviceType::Hardware, "Only DeviceType::Hardware is supported.");

			_deviceType = deviceType;
			clearColor = Color::Black;

			pb_init();
		}
		
		GraphicsDevice::~GraphicsDevice()
		{
			Dispose(false);
			delete _adapter;
			delete presentationParameters;
		}
		
		void GraphicsDevice::Clear(Color color)
		{
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

			/*if(color != clearColor)
			{
				glClearColor((float)color.R/255f, (float)color.G/255f, (float)color.B/255f, (float)color.A/255f);
				clearColor = color;
			}
			glClear(GL_COLOR_BUFFER_BIT);
			glLoadIdentity();*/
		}

		void GraphicsDevice::Clear(const ClearOptions_t options, const Color color, const float depth, const int stencil)
		{
			DWORD		*p;
			DWORD		format;
			DWORD		_depth;
			
			int		x1,y1,x2,y2;
			
			//Set the coordinates for the rectangle to be cleared
			x1 = 0;
			y1 = 0;
			x2 = x1 + _depthStencilBuffer.Width();
			y2 = y1 + _depthStencilBuffer.Height();

			p=pb_begin();
			pb_push(p++,NV20_TCL_PRIMITIVE_3D_CLEAR_VALUE_HORIZ,2);		//sets rectangle coordinates
			*(p++)=((x2-1)<<16)|x1;
			*(p++)=((y2-1)<<16)|y1;

			if ((options & ClearOptions::Depth) != 0)
			{
				
			}
			if ((options & ClearOptions::Stencil) != 0)
			{

			}
			if ((options & ClearOptions::Target) != 0)
			{

			}

			pb_end(p);
		}

		void GraphicsDevice::Clear(const ClearOptions_t options, const Vector4 color, const float depth, const int stencil)
		{
			Clear(options, Color(color), depth, stencil);
		}
		
		void GraphicsDevice::Dispose()
		{
			Dispose(true);
		}
		
		void GraphicsDevice::Dispose(bool disposing)
		{
			if (!isDisposed)
			{
				if(disposing)
				{
					textures.Dispose();

					isDisposed = true;
				}
			}
		}

		void GraphicsDevice::Present()
		{
			while(pb_finished());

			// reset the push buffer
			pb_reset();
		}

		void GraphicsDevice::raise_DeviceLost(Object* sender, EventArgs e)
		{
			if (DeviceLost)
				DeviceLost(sender, e);
		}

		void GraphicsDevice::raise_DeviceReset(Object* sender, EventArgs e)
		{
			if (DeviceReset)
				DeviceReset(sender, e);
		}

		void GraphicsDevice::raise_DeviceResetting(Object* sender, EventArgs e)
		{
			if (DeviceResetting)
				DeviceResetting(sender, e);
		}

		void GraphicsDevice::raise_Disposing(Object* sender, EventArgs e)
		{
			if (Disposing)
				Disposing(sender, e);
		}

		void GraphicsDevice::Reset()
		{
			Reset(getPresentationParameters());
		}

		void GraphicsDevice::Reset(PresentationParameters* presentationParameters)
		{
			raise_DeviceResetting(this, EventArgs::Empty);
			setPresentationParameters(presentationParameters);
			raise_DeviceReset(this, EventArgs::Empty);
		}

		void GraphicsDevice::SetRenderTarget(RenderTarget2D* renderTarget)
		{
			if (renderTarget == null) // the user wants to reset the render target to the normal back buffer
			{
				pb_target_back_buffer();
			}
			else
			{
				//! TODO: set the render target.
			}
		}
	}
}
