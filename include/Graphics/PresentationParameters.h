/********************************************************
 *	PresentationParameters.h							*
 *														*
 *	XFX PresentationParameters definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_PRESENTATIONPARAMETERS_
#define _XFX_GRAPHICS_PRESENTATIONPARAMETERS_

#include <System/Types.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Contains presentation parameters.
		/// </summary>
		class PresentationParameters : public IDisposable
		{
			private:
         		bool disposed; 
			
			protected:
				virtual void Dispose(bool disposing);
				
			public:
				DepthFormat_t AutoDepthStencilFormat;
				int BackBufferCount;
				SurfaceFormat_t BackBufferFormat;
				int BackBufferHeight;
				int BackBufferWidth;
				static const int DefaultPresentRate;
				
#if !ENABLE_XBOX //Only valid on Linux
				IntPtr DeviceWindowHandle;
#endif

				bool EnableAutoDepthStencil;
				int FullScreenRefreshRateInHz;
				bool IsFullScreen;
				int MultiSampleQuality; 
         		MultiSampleType_t MultiSampleType_; 
				PresentInterval_t PresentationInterval;
				PresentOptions_t PresentOptions_;
				SwapEffect_t SwapEffect_;

				virtual ~PresentationParameters();
				PresentationParameters();
				
				void Clear();
				PresentationParameters Clone();
				void Dispose();
				bool Equals(const PresentationParameters other);
				
				bool operator!=(const PresentationParameters other);
				bool operator==(const PresentationParameters other);
		};
	}
}

#endif //_XFX_GRAPHICS_PRESENTATIONPARAMETERS_
