// Copyright (C) XFX Team
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

#include <Audio/SoundEffect.h>
#include <Audio/SoundEffectInstance.h>

#include <System/Single.h>

#include <sassert.h>

namespace XFX
{
	namespace Audio
	{
		float SoundEffect::masterVolume = 1.0f;

		float SoundEffect::getDistanceScale()
		{
			return distanceScale;
		}

		void SoundEffect::setDistanceScale(float value)
		{
			sassert(value >= 0, "");

			value = (value <= Single::MinValue) ? Single::MinValue : value;

			// TODO: set in hardware
		}

		float SoundEffect::getDopplerScale()
		{
			return dopplerScale;
		}

		void SoundEffect::setDopplerScale(float value)
		{
			sassert(value >= 0, "");
		
			dopplerScale = value;

			// TODO: set in hardware
		}

		TimeSpan SoundEffect::getDuration() const
		{
			return duration;
		}

		bool SoundEffect::IsDisposed() const
		{
			return isDisposed;
		}

		float SoundEffect::getMasterVolume()
		{
			return masterVolume;
		}

		void SoundEffect::setMasterVolume(float value)
		{
			masterVolume = value;
		}

		SoundEffect::SoundEffect(byte buffer[], int sampleRate, AudioChannels_t numChannels)
			: volume(masterVolume)
		{
		}

		SoundEffect::SoundEffect(const SoundEffect &obj)
			: duration(obj.duration), volume(obj.volume)
		{
		}

		SoundEffect::~SoundEffect()
		{
			Dispose(false);
		}

		SoundEffectInstance* SoundEffect::CreateInstance()
		{
			return new SoundEffectInstance(this);
		}

		void SoundEffect::Dispose()
		{
			Dispose(true);
		}

		void SoundEffect::Dispose(bool disposing)
		{
		}

		SoundEffect* SoundEffect::FromStream(Stream * const stream)
		{
			
		}

		int SoundEffect::GetType() const
		{
		}

		bool SoundEffect::Play()
		{
			SoundEffectInstance(this).Play();
		}

		bool SoundEffect::Play(float volume, float pitch, float pan)
		{
			SoundEffectInstance sei(this);
			sei.setPan(pan);
			sei.setPitch(pitch);
			sei.setVolume(volume);
			sei.Play();
		}
	}
}
