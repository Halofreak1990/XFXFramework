/********************************************************
 *	IGraphicsDeviceService.h							*
 *														*
 *	XFX IGraphicsDeviceService definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_IGRAPHICSDEVICESERVICE_
#define _XFX_GRAPHICS_IGRAPHICSDEVICESERVICE_

#include <System/Types.h>
#include "GraphicsDevice.h"

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Defines a mechanism for retrieving GraphicsDevice objects.
		/// </summary>
		interface IGraphicsDeviceService
		{
		public:
			EventHandler DeviceCreated;
			EventHandler DeviceDisposing;
			EventHandler DeviceReset;
			EventHandler DeviceResetting;

			virtual GraphicsDevice getGraphicsDevice()=0;
		};
	}
}

#endif //_XFX_GRAPHICS_IGRAPHICSDEVICESERVICE_
