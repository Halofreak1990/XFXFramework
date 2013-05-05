/********************************************************
 *	GraphicsAdapter.h									*
 *														*
 *	XFX GraphicsAdapter definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_GRAPHICSADAPTER_
#define _XFX_GRAPHICS_GRAPHICSADAPTER_

#include <System/Types.h>
#include <System/Interfaces.h>

#include "DisplayMode.h"
#include "DisplayModeCollection.h"
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		// Provides methods to retrieve and manipulate graphics adapters.
		class GraphicsAdapter : public IDisposable, public Object
		{
		protected:
			void Dispose(bool disposing);
		
		public:
			DisplayMode CurrentDisplayMode();

			const char* Description();
			int DeviceId();		
			const char* DeviceName();
			const char* DriverDLL();		
			float DriverVersion();		
			bool IsDefaultAdapter();		
			int VendorId();
			bool IsWideScreen();
			DisplayModeCollection SupportedDisplayModes();
		
			virtual ~GraphicsAdapter();

			void Dispose();
			bool Equals(const Object* obj) const;
			bool Equals(const GraphicsAdapter obj) const;
			int GetHashCode() const;
			int GetType() const;
			bool QueryBackBufferFormat(SurfaceFormat_t format, DepthFormat_t depthFormat, int multiSampleCount, out SurfaceFormat_t selectedFormat, out DepthFormat_t selectedDepthFormat, out int selectedMultiSampleCount) const;
			bool QueryRenderTargetFormat(SurfaceFormat_t format, DepthFormat_t depthFormat, int multiSampleCount, out SurfaceFormat_t selectedFormat, out DepthFormat_t selectedDepthFormat, out int selectedMultiSampleCount) const;
			
			bool operator!=(const GraphicsAdapter& other) const;
			bool operator==(const GraphicsAdapter& other) const;
		};
	}
}

#endif //_XFX_GRAPHICS_GRAPHICSADAPTER_
