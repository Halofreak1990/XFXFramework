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
		class SoundEffect : public IDisposable, virtual Object
		{
		private:
			void Dispose(bool disposing);

		public:
			SoundEffect(byte buffer[], int sampleRate, AudioChannels_t numChannels);
			SoundEffect(const SoundEffect &obj);
			~SoundEffect();

			SoundEffectInstance CreateInstance();
			void Dispose();
			static SoundEffect FromStream(Stream* stream);
			bool Play();
			bool Play(float volume, float pitch, float pan);
		};
	}
}

#endif //_XFX_AUDIO_SOUNDEFFECT_
