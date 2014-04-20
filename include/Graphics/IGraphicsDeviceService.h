/********************************************************
 *	IGraphicsDeviceService.h							*
 *														*
 *	XFX IGraphicsDeviceService definition file			*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_IGRAPHICSDEVICESERVICE_
#define _XFX_GRAPHICS_IGRAPHICSDEVICESERVICE_

#include <System/Event.h>
#include <System/Types.h>

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		class GraphicsDevice;

		// Defines a mechanism for retrieving GraphicsDevice objects.
		interface IGraphicsDeviceService : public Object
		{
		public:
			EventHandler DeviceCreated;
			EventHandler DeviceDisposing;
			EventHandler DeviceReset;
			EventHandler DeviceResetting;

			virtual ~IGraphicsDeviceService() {}

			virtual GraphicsDevice* getGraphicsDevice() const =0;

			static const Type& GetType();
		};
	}
}

#endif //_XFX_GRAPHICS_IGRAPHICSDEVICESERVICE_
