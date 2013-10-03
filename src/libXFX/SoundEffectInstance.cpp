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
		const Type SoundEffectInstanceTypeInfo("SoundEffectInstance", "XFX::Audio::SoundEffectInstance", TypeCode::Object);

		bool SoundEffectInstance::IsDisposed() const
		{
			// TODO: implement
		}

		bool SoundEffectInstance::IsLooped() const
		{
			// TODO: implement
		}

		void SoundEffectInstance::IsLooped(bool value)
		{
			// TODO: implement
		}

		float SoundEffectInstance::getPan() const
		{
			// TODO: implement
		}

		void SoundEffectInstance::setPan(float value)
		{
			// TODO: implement
		}

		float SoundEffectInstance::getPitch() const
		{
			// TODO: implement
		}

		void SoundEffectInstance::setPitch(float value)
		{
			// TODO: implement
		}

		SoundState_t SoundEffectInstance::getState() const
		{
			// TODO: implement
		}

		float SoundEffectInstance::getVolume() const
		{
			return _volume;
		}

		void SoundEffectInstance::setVolume(float value)
		{
			// TODO: implement
		}

		SoundEffectInstance::SoundEffectInstance(SoundEffect * const parent, bool fireAndForget)
			: _parent(parent), _volume(parent->volume)
		{
			_parent->referenceCount++;
		}

		SoundEffectInstance::~SoundEffectInstance()
		{
			_parent->referenceCount--;
		}

		void SoundEffectInstance::Apply3D(AudioListener listener, AudioEmitter emitter)
		{
			// TODO: implement
		}

		void SoundEffectInstance::Apply3D(AudioListener listeners[], AudioEmitter emitter)
		{
			// TODO: implement
		}

		void SoundEffectInstance::Dispose()
		{
			Dispose(true);
		}

		void SoundEffectInstance::Dispose(bool disposing)
		{
			if (disposing)
			{
				
			}
		}

		const Type& SoundEffectInstance::GetType()
		{
			return SoundEffectInstanceTypeInfo;
		}

		void SoundEffectInstance::Pause()
		{
			// TODO: implement
		}

		void SoundEffectInstance::Play()
		{
			// TODO: implement
		}

		void SoundEffectInstance::Resume()
		{
			// TODO: implement
		}

		void SoundEffectInstance::Stop()
		{
			Stop(true);
		}

		void SoundEffectInstance::Stop(bool immediate)
		{
			// TODO: implement
		}
	}
}
