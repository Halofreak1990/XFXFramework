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

#include <Graphics/GraphicsAdapter.h>

extern "C" {
#include "pbKit.h"
#include <hal/video.h>
}

namespace XFX
{
	namespace Graphics
	{
		GraphicsAdapter::~GraphicsAdapter()
		{
			Dispose(false);
		}

		char* GraphicsAdapter::Description()
		{
			//TODO: Come up with a device description
			return "";
		}
		
		int GraphicsAdapter::DeviceId()
		{
			return 0x2a0;
		}
		
		char* GraphicsAdapter::DeviceName()
		{
			return "NV2A";
		}
		
		char* GraphicsAdapter::DriverDLL()
		{
			return "pbKit";
		}
		
		float GraphicsAdapter::DriverVersion()
		{
			return 1.0;
		}
		
		bool GraphicsAdapter::IsDefaultAdapter()
		{
			return true;
		}
		
		int GraphicsAdapter::VendorId()
		{
			return 0x10DE;
		}
		
		bool GraphicsAdapter::IsWideScreen()
		{
			//TODO: Get WideScreen setting from EEPROM
			return false;
		}

		bool GraphicsAdapter::CheckDepthStencilMatch(DeviceType_t deviceType, SurfaceFormat_t adapterFormat, SurfaceFormat_t renderTargetFormat, DepthFormat_t depthStencilFormat)
		{
		}

		bool GraphicsAdapter::CheckDeviceFormat(DeviceType_t deviceType, SurfaceFormat_t adapterFormat, TextureUsage_t usage, QueryUsages_t queryUsages, ResourceType_t resourceType, SurfaceFormat_t checkFormat)
		{
		}

		bool GraphicsAdapter::CheckDeviceFormat(DeviceType_t deviceType, SurfaceFormat_t adapterFormat, TextureUsage_t usage, QueryUsages_t queryUsages, ResourceType_t resourceType, DepthFormat_t checkFormat)
		{
		}

		bool GraphicsAdapter::CheckDeviceFormatConversion(DeviceType_t deviceType, SurfaceFormat_t sourceFormat, SurfaceFormat_t targetFormat)
		{
		}

		bool GraphicsAdapter::CheckDeviceMultiSampleType(DeviceType_t deviceType, SurfaceFormat_t surfaceFormat, bool isFullScreen, MultiSampleType_t sampleType)
		{
		}

		bool GraphicsAdapter::CheckDeviceMultiSampleType(DeviceType_t deviceType, SurfaceFormat_t surfaceFormat, bool isFullScreen, MultiSampleType_t sampleType, out int qualityLevels)
		{
		}

		bool GraphicsAdapter::CheckDeviceType(DeviceType_t deviceType, SurfaceFormat_t displayFormat, SurfaceFormat_t backBufferFormat, bool isFullScreen)
		{
		}
		
		DisplayMode GraphicsAdapter::CurrentDisplayMode()
		{
			DisplayMode disp;
			
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
			return disp;
		}

		void GraphicsAdapter::Dispose()
		{
			Dispose(true);
		}

		void GraphicsAdapter::Dispose(bool __p1)
		{
			if (__p1)
			{
			}
		}

		bool GraphicsAdapter::Equals(const GraphicsAdapter obj)
		{
			// There's for now only one GraphicsAdapter instance, so just return true;
			return true;
		}
		
		bool GraphicsAdapter::IsDeviceTypeAvailable(DeviceType_t deviceType)
		{
			switch(deviceType)
			{
			case DeviceType::Hardware: return true;
			case DeviceType::NullReference: return false;
			case DeviceType::Reference: return false;
			default: return false;
			}
		}

		DisplayModeCollection GraphicsAdapter::SupportedDisplayModes()
		{
			DisplayModeCollection collection;

			return collection;
		}

		bool GraphicsAdapter::operator!=(const GraphicsAdapter other)
		{
			return !Equals(other);
		}

		bool GraphicsAdapter::operator==(const GraphicsAdapter other)
		{
			return Equals(other);
		}
	}
}
