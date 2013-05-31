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

#include <Graphics/Color.h>
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
#include <openxdk/debug.h>
#include <hal/xbox.h>
}

#include <sassert.h>

using namespace System;
using namespace XFX;

namespace XFX
{
	namespace Graphics
	{
		PresentationParameters* GraphicsDevice::getPresentationParameters() const
		{
			return p_cachedParameters;
		}

		void GraphicsDevice::setPresentationParameters(PresentationParameters* presentationParameters)
		{
			viewport.X = 0;
			viewport.Y = 0;
			viewport.Width = presentationParameters->BackBufferWidth;
			viewport.Height = presentationParameters->BackBufferHeight;

			DWORD* p = pb_begin();

			if (presentationParameters->BackBufferFormat == SurfaceFormat::Color)
			{
				// TODO: find command *RED_SIZE
				//pb_push1(p, 0, 0);
				// TODO: find command *GREEN_SIZE
				//pb_push1(p, 0, 0);
				// TODO: find command *BLUE_SIZE
				//pb_push1(p, 0, 0);
				//  TODO: find command *ALPHA_SIZE
				//pb_push1(p, 0, 0);
			}
			
			pb_end(p);

			pb_set_viewport(viewport.X, viewport.Y, viewport.Width, viewport.Height, viewport.MinDepth, viewport.MaxDepth);
		}

		TextureCollection GraphicsDevice::getTextures() const
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

		GraphicsDevice::GraphicsDevice(GraphicsAdapter * const  adapter, PresentationParameters * const presentationParameters)
		{
			//sassert(adapter != null, String::Format("adapter; %s", FrameworkResources::ArgumentNull_Generic));

			sassert(presentationParameters != null, String::Format("presentationParameters; %s", FrameworkResources::ArgumentNull_Generic));

			//this->_adapter = adapter;

			int err = pb_init();

			switch (err)
			{
			case 0: break; //no error
			case -4:		
				debugPrint("IRQ3 already handled. Can't install GPU interrupt.\n");
				debugPrint("You must apply the patch and compile OpenXDK again.\n");
				debugPrint("Also be sure to call pb_init() before any other call.\n");
				XSleep(2000);
				return;
			case -5:		
				debugPrint("Unexpected PLL configuration. Report this issue please.\n");
				XSleep(2000);
				return;
			default:
				debugPrint("pb_init Error %d\n", err);
				XSleep(2000);
				return;
			}

			this->setPresentationParameters(presentationParameters);

			pb_reset();
		}
		
		GraphicsDevice::~GraphicsDevice()
		{
			Dispose(false);
			delete _adapter;
			delete p_cachedParameters;
		}
		
		void GraphicsDevice::Clear(const Color color)
		{
			// start of frame-- reset push buffer
			pb_reset();

			DWORD		*p;
			DWORD		format;
			DWORD		depth;
			
			int		x1,y1,x2,y2;
			
			//Set the coordinates for the rectangle to be cleared
			x1 = 0;
			y1 = 0;
			x2 = x1 + this->p_cachedParameters->BackBufferWidth;
			y2 = y1 + this->p_cachedParameters->BackBufferHeight;
			
			switch(this->p_cachedParameters->DepthStencilFormat)
			{
				// TODO: verify
			case DepthFormat::Depth16: { format = 0x03; depth = 0xffff00; } break;
			case DepthFormat::Depth24: { format = 0x03; depth = 0xffffff00; } break;
			case DepthFormat::Depth24Stencil8: { format = 0x03; depth = 0xffffff00; } break;
			case DepthFormat::None: break;
			}
			
			p = pb_begin();
			pb_push(p++, NV20_TCL_PRIMITIVE_3D_CLEAR_VALUE_HORIZ, 2);		//sets rectangle coordinates
			*(p++) = ((x2-1) << 16) | x1;
			*(p++) = ((y2-1) << 16) | y1;
			pb_push(p++, NV20_TCL_PRIMITIVE_3D_CLEAR_VALUE_DEPTH, 3);		//sets data used to fill in rectangle
			*(p++) = depth;					//depth to clear
			*(p++) = color.PackedValue();	//color
			*(p++) = format;				//triggers the HW rectangle fill (only on D&S)
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
			// start of frame-- reset push buffer
			pb_reset();

			DWORD		*p;
			DWORD		format;
			
			int		x1,y1,x2,y2;
			
			//Set the coordinates for the rectangle to be cleared
			x1 = 0;
			y1 = 0;
			x2 = x1 + this->p_cachedParameters->BackBufferWidth;
			y2 = y1 + this->p_cachedParameters->BackBufferHeight;

			p = pb_begin();
			pb_push(p++, NV20_TCL_PRIMITIVE_3D_CLEAR_VALUE_HORIZ, 2);		//sets rectangle coordinates
			*(p++)= ((x2 - 1) << 16) | x1;
			*(p++)= ((y2 - 1) << 16) | y1;

			if ((options & ClearOptions::Depth) != 0)
			{
				// clear the depth buffer
			}
			if ((options & ClearOptions::Stencil) != 0)
			{
				// clear the stencil buffer
			}
			if ((options & ClearOptions::Target) != 0)
			{
				// clear the current render target
			}

			*(p++) = color.PackedValue();
			*(p++) = format;

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
				pb_kill();

				if(disposing)
				{
					textures.Dispose();

					isDisposed = true;
				}
			}
		}

		int GraphicsDevice::GetType() const
		{
		}

		void GraphicsDevice::Present()
		{
			while(pb_finished());
		}

		void GraphicsDevice::raise_DeviceLost(Object* sender, EventArgs* e)
		{
			DeviceLost(sender, e);
		}

		void GraphicsDevice::raise_DeviceReset(Object* sender, EventArgs* e)
		{
			DeviceReset(sender, e);
		}

		void GraphicsDevice::raise_DeviceResetting(Object* sender, EventArgs* e)
		{
			DeviceResetting(sender, e);
		}

		void GraphicsDevice::raise_Disposing(Object* sender, EventArgs* e)
		{
			Disposing(sender, e);
		}

		void GraphicsDevice::Reset()
		{
			Reset(getPresentationParameters());
		}

		void GraphicsDevice::Reset(PresentationParameters* presentationParameters)
		{
			raise_DeviceResetting(this, const_cast<EventArgs*>(EventArgs::Empty));
			setPresentationParameters(presentationParameters);
			raise_DeviceReset(this, const_cast<EventArgs*>(EventArgs::Empty));
		}

		void GraphicsDevice::SetRenderTarget(RenderTarget2D * const renderTarget)
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
