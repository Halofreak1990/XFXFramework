/*****************************************************************************
 *	PresentationParameters.h												 *
 *																			 *
 *	XFX::Graphics::PresentationParameters class definition file				 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_PRESENTATIONPARAMETERS_
#define _XFX_GRAPHICS_PRESENTATIONPARAMETERS_

#include <System/Interfaces.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	struct Rectangle;

	namespace Graphics
	{
		/**
		 * Contains presentation parameters.
		 */
		class PresentationParameters : public Object
		{
		public:
			SurfaceFormat_t BackBufferFormat;
			int BackBufferHeight;
			int BackBufferWidth;
			Rectangle getBounds() const;
			DepthFormat_t DepthStencilFormat;
			bool IsFullScreen;
     		int MultiSampleCount;
			PresentInterval_t PresentationInterval;
			RenderTargetUsage_t RenderTargetUsage;

			PresentationParameters();

			PresentationParameters* Clone() const;
			bool Equals(Object const * const obj) const;
			bool Equals(const PresentationParameters other) const;
			static const Type& GetType();
			
			bool operator!=(const PresentationParameters& other) const;
			bool operator==(const PresentationParameters& other) const;
		};
	}
}

#endif //_XFX_GRAPHICS_PRESENTATIONPARAMETERS_
