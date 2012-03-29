/********************************************************
 *	IGraphicsDeviceService.h							*
 *														*
 *	XFX IGraphicsDeviceService definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_IGRAPHICSDEVICESERVICE_
#define _XFX_GRAPHICS_IGRAPHICSDEVICESERVICE_

#include <System/Types.h>

namespace XFX
{
	namespace Graphics
	{
		class GraphicsDevice;

		// Defines a mechanism for retrieving GraphicsDevice objects.
		interface IGraphicsDeviceService : virtual Object
		{
		public:
			EventHandler DeviceCreated;
			EventHandler DeviceDisposing;
			EventHandler DeviceReset;
			EventHandler DeviceResetting;

			virtual GraphicsDevice* getGraphicsDevice() const =0;
		};
	}
}

#endif //_XFX_GRAPHICS_IGRAPHICSDEVICESERVICE_
