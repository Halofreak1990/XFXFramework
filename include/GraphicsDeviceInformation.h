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

using namespace System;
using namespace XFX::Graphics;

namespace XFX
{
	// Holds the settings for creating a graphics device.
	class GraphicsDeviceInformation : public Object
	{
	public:
		GraphicsAdapter Adapter;
		XFX::Graphics::PresentationParameters PresentationParameters;

		GraphicsDeviceInformation();
	
		GraphicsDeviceInformation Clone() const;
		bool Equals(const Object* obj) const;
		int GetType() const;
	};
}

#endif //_GRAPHICSDEVICEINFORMATION_
