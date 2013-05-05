/********************************************************
 *	GraphicsDeviceCreationParameters.h					*
 *														*
 *	XFX GraphicsDeviceCreationParameters definition file*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_GRAPHICSDEVICECREATIONPARAMETERS_
#define _XFX_GRAPHICS_GRAPHICSDEVICECREATIONPARAMETERS_

#include "Enums.h"
#include "GraphicsAdapter.h"

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Describes the creation parameters for a device.
		/// </summary>
		struct GraphicsDeviceCreationParameters
		{
		private:
			GraphicsAdapter _adapter;
			DeviceType_t _deviceType;

		public:
			GraphicsAdapter Adapter();
			DeviceType_t DeviceType_();

			GraphicsDeviceCreationParameters(GraphicsAdapter graphicsAdapter, DeviceType_t deviceType);
		};
	}
}

#endif //_XFX_GRAPHICS_GRAPHICSDEVICECREATIONPARAMETERS_
