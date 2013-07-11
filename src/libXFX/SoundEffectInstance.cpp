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

#include <Audio/SoundEffectInstance.h>
#include <Audio/AudioEmitter.h>
#include <Audio/AudioListener.h>
#include <Audio/SoundEffect.h>

namespace XFX
{
	namespace Audio
	{
		bool SoundEffectInstance::IsDisposed() const
		{
		}

		bool SoundEffectInstance::IsLooped() const
		{
		}

		void SoundEffectInstance::IsLooped(bool value)
		{
		}

		float SoundEffectInstance::getPan() const
		{
		}

		void SoundEffectInstance::setPan(float value)
		{
		}

		float SoundEffectInstance::getPitch() const
		{
		}

		void SoundEffectInstance::setPitch(float value)
		{
		}

		SoundState_t SoundEffectInstance::getState() const
		{
		}

		float SoundEffectInstance::getVolume() const
		{
		}

		void SoundEffectInstance::setVolume(float value)
		{
		}

		SoundEffectInstance::SoundEffectInstance(SoundEffect* parent)
		{
		}

		SoundEffectInstance::~SoundEffectInstance()
		{
		}

		void SoundEffectInstance::Apply3D(AudioListener listener, AudioEmitter emitter)
		{
		}

		void SoundEffectInstance::Apply3D(AudioListener listeners[], AudioEmitter emitter)
		{
		}

		void SoundEffectInstance::Dispose()
		{
			Dispose(true);
		}

		void SoundEffectInstance::Dispose(bool disposing)
		{
		}

		int SoundEffectInstance::GetType()
		{
		}

		void SoundEffectInstance::Pause()
		{
		}

		void SoundEffectInstance::Play()
		{
		}

		void SoundEffectInstance::Resume()
		{
		}

		void SoundEffectInstance::Stop()
		{
		}

		void SoundEffectInstance::Stop(bool immediate)
		{
		}
	}
}
