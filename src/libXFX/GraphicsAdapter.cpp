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

		const char* GraphicsAdapter::Description()
		{
			//TODO: Come up with a device description
			return "";
		}

		int GraphicsAdapter::DeviceId()
		{
			return 0x2a0;
		}

		const char* GraphicsAdapter::DeviceName()
		{
			return "NV2A";
		}

		const char* GraphicsAdapter::DriverDLL()
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

		bool GraphicsAdapter::QueryBackBufferFormat(SurfaceFormat_t format, DepthFormat_t depthFormat, int multiSampleCount, out SurfaceFormat_t selectedFormat, out DepthFormat_t selectedDepthFormat, out int selectedMultiSampleCount) const
		{
		}

		bool GraphicsAdapter::QueryRenderTargetFormat(SurfaceFormat_t format, DepthFormat_t depthFormat, int multiSampleCount, out SurfaceFormat_t selectedFormat, out DepthFormat_t selectedDepthFormat, out int selectedMultiSampleCount) const
		{
		}
		
		DisplayMode GraphicsAdapter::CurrentDisplayMode()
		{
			DisplayMode disp;
			
			VIDEO_MODE mode = XVideoGetMode();
			disp.Height = mode.height;
			disp.RefreshRate = mode.refresh;
			disp.Width = mode.width;

			// TODO: verify-- from the formats in SurfaceFormat, one could deduce that only 16- and 32-bit formats are supported
			switch(mode.bpp)
			{
			case 32: disp.Format = SurfaceFormat::Color;
			case 16: disp.Format = SurfaceFormat::Bgr565;
			}
			return disp;
		}

		void GraphicsAdapter::Dispose()
		{
			Dispose(true);
		}

		void GraphicsAdapter::Dispose(bool disposing)
		{
			if (disposing)
			{
			}
		}

		bool GraphicsAdapter::Equals(Object const * const obj) const
		{
			return is(this, obj) ? (*this == *(GraphicsAdapter*)obj) : false;
		}

		bool GraphicsAdapter::Equals(const GraphicsAdapter obj) const
		{
			// There's for now only one GraphicsAdapter instance, so just return true;
			return true;
		}

		DisplayModeCollection GraphicsAdapter::SupportedDisplayModes()
		{
			DisplayModeCollection collection;
			// TODO: get a lsit of displaymodes supported
			return collection;
		}

		bool GraphicsAdapter::operator!=(const GraphicsAdapter& other) const
		{
			return false;
		}

		bool GraphicsAdapter::operator==(const GraphicsAdapter& other) const
		{
			return true;
		}
	}
}
