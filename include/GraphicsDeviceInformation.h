/*****************************************************************************
 *	GraphicsDeviceInformation.h												 *
 *																			 *
 *	XFX GraphicsDeviceInformation class definition file						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _GRAPHICSDEVICEINFORMATION_
#define _GRAPHICSDEVICEINFORMATION_

#include <Graphics/Enums.h>
#include <Graphics/PresentationParameters.h>

using namespace System;
using namespace XFX::Graphics;

namespace XFX
{
	/**
	 * Holds the settings for creating a graphics device.
	 */
	class GraphicsDeviceInformation : public Object
	{
	public:
		GraphicsAdapter Adapter;
		XFX::Graphics::PresentationParameters PresentationParameters;

		GraphicsDeviceInformation();
	
		GraphicsDeviceInformation Clone() const;
		bool Equals(Object const * const obj) const;
		static const Type& GetType();
	};
}

#endif //_GRAPHICSDEVICEINFORMATION_
