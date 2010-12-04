/********************************************************
 *	PresentationParameters.h							*
 *														*
 *	XFX PresentationParameters definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _PRESENTATIONPARAMETERS_
#define _PRESENTATIONPARAMETERS_

#include "../System.h"
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Contains presentation parameters.
		/// </summary>
		class PresentationParameters : IDisposable
		{
			private:
         		int disposed; 
			
			protected:
				virtual void Dispose(int disposing);
				
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

				int EnableAutoDepthStencil;
				int FullScreenRefreshRateInHz;
				int IsFullScreen;
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
				int Equals(PresentationParameters &other);
				
				int operator!=(PresentationParameters &other);
				int operator==(PresentationParameters &other);
		};
	}
}

#endif //_PRESENTATIONPARAMETERS_
