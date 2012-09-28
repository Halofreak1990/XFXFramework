/********************************************************
 *	SoundEffect.h										*
 *														*
 *	XFX::Audio::SoundEffect definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_AUDIO_SOUNDEFFECT_
#define _XFX_AUDIO_SOUNDEFFECT_

#include <System/Interfaces.h>
#include <System/TimeSpan.h>
#include <System/IO/Stream.h>
#include "Enums.h"

using namespace System;
using namespace System::IO;

namespace XFX
{
	namespace Audio
	{
		class SoundEffectInstance;

		// 
		class SoundEffect : public IDisposable, public Object
		{
		private:
			void Dispose(bool disposing);

		public:
			SoundEffect(byte buffer[], const int sampleRate, const AudioChannels_t numChannels);
			SoundEffect(const SoundEffect &obj);
			~SoundEffect();

			SoundEffectInstance CreateInstance();
			void Dispose();
			static SoundEffect FromStream(Stream * const stream);
			int GetType() const;
			bool Play();
			bool Play(const float volume, const float pitch, const float pan);
		};
	}
}

#endif //_XFX_AUDIO_SOUNDEFFECT_
