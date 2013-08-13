/*****************************************************************************
 *	GraphicsDeviceInformation.h 											 *
 *																			 *
 *	XFX GraphicsDeviceInformation class definition file 					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICSDEVICEINFORMATION_
#define _XFX_GRAPHICSDEVICEINFORMATION_

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

#endif //_XFX_GRAPHICSDEVICEINFORMATION_
