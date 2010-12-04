/********************************************************
 *	GraphicsAdapter.h									*
 *														*
 *	XFX GraphicsAdapter definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _GRAPHICSADAPTER_
#define _GRAPHICSADAPTER_

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
		/// <summary>
		/// Provides methods to retrieve and manipulate graphics adapters.
		/// </summary>
		class GraphicsAdapter : public IDisposable
		{
			protected:
				void Dispose(int __p1);
			
			public:
				DisplayMode CurrentDisplayMode();

				char* Description();
				int DeviceId();		
				char* DeviceName();
				char* DriverDLL();		
				float DriverVersion();		
				bool IsDefaultAdapter();		
				int VendorId();
				bool IsWideScreen();
				DisplayModeCollection SupportedDisplayModes();
			
				virtual ~GraphicsAdapter();

				bool CheckDepthStencilMatch(DeviceType_t deviceType, SurfaceFormat_t adapterFormat, SurfaceFormat_t renderTargetFormat, DepthFormat_t depthStencilFormat);
				bool CheckDeviceFormat(DeviceType_t deviceType, SurfaceFormat_t adapterFormat, TextureUsage_t usage, QueryUsages_t queryUsages, ResourceType_t resourceType, SurfaceFormat_t checkFormat);
				bool CheckDeviceFormat(DeviceType_t deviceType, SurfaceFormat_t adapterFormat, TextureUsage_t usage, QueryUsages_t queryUsages, ResourceType_t resourceType, DepthFormat_t checkFormat);
				bool CheckDeviceFormatConversion(DeviceType_t deviceType, SurfaceFormat_t sourceFormat, SurfaceFormat_t targetFormat);
				bool CheckDeviceMultiSampleType(DeviceType_t deviceType, SurfaceFormat_t surfaceFormat, int isFullScreen, MultiSampleType_t sampleType);
				bool CheckDeviceMultiSampleType(DeviceType_t deviceType, SurfaceFormat_t surfaceFormat, int isFullScreen, MultiSampleType_t sampleType, out int qualityLevels);
				bool CheckDeviceType(DeviceType_t deviceType, SurfaceFormat_t displayFormat, SurfaceFormat_t backBufferFormat, int isFullScreen);
				void Dispose();
				bool Equals(GraphicsAdapter &other);
				int GetHashCode();
				bool IsDeviceTypeAvailable(DeviceType_t deviceType);
				
				bool operator!=(GraphicsAdapter &other);
				bool operator==(GraphicsAdapter &other);
		};
	}
}

#endif //_GRAPHICSADAPTER_
