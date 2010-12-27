/********************************************************
 *	GraphicsDeviceInformation.h							*
 *														*
 *	XFX GraphicsDeviceInformation definition file		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _GRAPHICSDEVICEINFORMATION_
#define _GRAPHICSDEVICEINFORMATION_

#include <Graphics/Enums.h>
#include <Graphics/PresentationParameters.h>

using namespace XFX::Graphics;

namespace XFX
{
	/// <summary>
	/// Holds the settings for creating a graphics device.
	/// </summary>
	class GraphicsDeviceInformation
	{
	public:
		GraphicsAdapter Adapter;
		DeviceType_t DeviceType_;
		PresentationParameters PresentationParameters_;
	
		GraphicsDeviceInformation Clone();
	};
}

#endif //_GRAPHICSDEVICEINFORMATION_
