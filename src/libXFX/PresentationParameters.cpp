// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <Graphics/PresentationParameters.h>

namespace XFX
{
	namespace Graphics
	{
		const int PresentationParameters::DefaultPresentRate = 60;
		
		PresentationParameters::PresentationParameters()
		{
			disposed = false;
			Clear();
		}

		PresentationParameters::~PresentationParameters()
		{
			Dispose(false);
		}
		
		void PresentationParameters::Clear() 
        { 
            AutoDepthStencilFormat = DepthFormat::Unknown; 
            BackBufferCount = 0; 
            BackBufferFormat = SurfaceFormat::Unknown; 
            BackBufferHeight = 0; 
            BackBufferWidth = 0;
#if !ENABLE_XBOX
            DeviceWindowHandle = IntPtr::Zero; 
#endif
            EnableAutoDepthStencil = false; 
            FullScreenRefreshRateInHz = 0; 
            IsFullScreen = false; 
            MultiSampleQuality = 0; 
            MultiSampleType_ = MultiSampleType::None; 
            PresentationInterval = PresentInterval::Default; 
            PresentOptions_ = PresentOptions::None; 
            SwapEffect_ = SwapEffect::Default; 
        }
         
        PresentationParameters PresentationParameters::Clone() 
        { 
            PresentationParameters clone = PresentationParameters(); 
            clone.AutoDepthStencilFormat = AutoDepthStencilFormat; 
            clone.BackBufferCount = BackBufferCount; 
            clone.BackBufferFormat = BackBufferFormat; 
            clone.BackBufferHeight = BackBufferHeight; 
            clone.BackBufferWidth = BackBufferWidth; 
#if !ENABLE_XBOX
            clone.DeviceWindowHandle = DeviceWindowHandle; 
#endif
            clone.disposed = disposed; 
            clone.EnableAutoDepthStencil = EnableAutoDepthStencil; 
            clone.FullScreenRefreshRateInHz = FullScreenRefreshRateInHz; 
            clone.IsFullScreen = IsFullScreen; 
            clone.MultiSampleQuality = MultiSampleQuality; 
            clone.MultiSampleType_ = MultiSampleType_; 
            clone.PresentationInterval = PresentationInterval;
            clone.PresentOptions_ = PresentOptions_;
            clone.SwapEffect_ = SwapEffect_;
            return clone; 
        }
         
        void PresentationParameters::Dispose()
        {
	        Dispose(true);
        }
         
        void PresentationParameters::Dispose(bool disposing)
        {
         	 if (!disposed) 
         	 { 
         	     disposed = true; 
         	     if (disposing) 
				{ 
                  	// Dispose managed resources 
				} 
            	// Dispose unmanaged resources 
            }
        }
        
        bool PresentationParameters::Equals(const PresentationParameters other)
        {
	        return ((other.AutoDepthStencilFormat == AutoDepthStencilFormat) &&
            (other.BackBufferCount == BackBufferCount) &&
            (other.BackBufferFormat == BackBufferFormat) &&
            (other.BackBufferHeight == BackBufferHeight) &&
            (other.BackBufferWidth == BackBufferWidth) &&
#if !ENABLE_XBOX
            (other.DeviceWindowHandle == DeviceWindowHandle) &&
#endif
            (other.Disposed == Disposed) &&
            (other.EnableAutoDepthStencil == EnableAutoDepthStencil) &&
            (other.FullScreenRefreshRateInHz == FullScreenRefreshRateInHz) &&
            (other.IsFullScreen == IsFullScreen) &&
            (other.MultiSampleQuality == MultiSampleQuality) &&
            (other.MultiSampleType_ == MultiSampleType_) &&
            (other.PresentationInterval == PresentationInterval) &&
            (other.PresentOptions_ == PresentOptions_) &&
            (other.SwapEffect_ == SwapEffect_));
        }
        
        bool PresentationParameters::operator!=(const PresentationParameters other)
        {
	        return !Equals(other);
        }
        
		bool PresentationParameters::operator==(const PresentationParameters other)
		{
			return Equals(other);
		}
	}
}
