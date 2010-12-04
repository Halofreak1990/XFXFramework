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

#include "PBKit/pbKit.h"
#include <Graphics/GraphicsAdapter.h>

#if ENABLE_XBOX
#include <hal/video.h>
#endif

namespace XFX
{
	namespace Graphics
	{
		char* GraphicsAdapter::Description()
		{
#if ENABLE_XBOX
			//TODO: Come up with a device description
#else
			//TODO: Get Device Description
#endif
		}
		
		int GraphicsAdapter::DeviceId()
		{
#if ENABLE_XBOX
			return 0x2a0;
#else
			//TODO: Get Device ID
#endif
		}
		
		char* GraphicsAdapter::DeviceName()
		{
#if ENABLE_XBOX
			return "NV2A";
#else
			//TODO: Get Device Name
#endif
		}
		
		char* GraphicsAdapter::DriverDLL()
		{
#if ENABLE_XBOX
			return "pbKit";
#else
			//TODO: Get Driver DLL
#endif
		}
		
		float GraphicsAdapter::DriverVersion()
		{
#if ENABLE_XBOX
			return 1.0;
#else
			//TODO: Get Driver Version
#endif
		}
		
		bool GraphicsAdapter::IsDefaultAdapter()
		{
#if ENABLE_XBOX
			return true;
#else
			//TODO: Find out whther this device is the Default Adapter
#endif
		}
		
		int GraphicsAdapter::VendorId()
		{
#if ENABLE_XBOX
			return 0x10DE;
#else
			//TODO: Get VendorId
#endif
		}
		
		bool GraphicsAdapter::IsWideScreen()
		{
#if ENABLE_XBOX	
			return false;
#else
			//TODO: Get IsWideScreen
#endif
		}
		
		DisplayMode GraphicsAdapter::CurrentDisplayMode()
		{
			DisplayMode disp;
			
#if ENABLE_XBOX
			VIDEO_MODE mode = XVideoGetMode();
			disp.Height = mode.height;
			disp.RefreshRate = mode.refresh;
			disp.Width = mode.width;

			//FIXME: get the proper SurfaceFormat for 16-bit
			switch(mode.bpp)
			{
			case 32: disp.Format = SurfaceFormat::Color;
			case 24: disp.Format = SurfaceFormat::Rgb32;
			case 8: disp.Format = SurfaceFormat::Palette8;
			default: disp.Format = SurfaceFormat::Unknown;
			}
#else
			//TODO: Get the screen surface format, dimensions, and refreshRate, and store them in the 'disp' variable
#endif
			return disp;
		}
		
		bool GraphicsAdapter::IsDeviceTypeAvailable(DeviceType_t deviceType)
		{
#if ENABLE_XBOX
			switch(deviceType)
			{
				case DeviceType::Hardware: return true;
				case DeviceType::NullReference: return false;
				case DeviceType::Reference: return false;
				default: return false;
			}
#else
			//TODO: Add code to check this on Linux
#endif
		}
	}
}
