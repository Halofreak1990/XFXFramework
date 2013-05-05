#ifndef XFRAMEWORK_SOUNDBANK_H
#define XFRAMEWORK_SOUNDBANK_H

#include "AudioEmitter.h"
#include "AudioEngine.h"
#include "AudioListener.h"
#include "Cue.h"

namespace XFramework::Audio
{
	class SoundBank
	{
		protected:
			void Dispose(int disposing);
		public:
			int IsInUse;

			void Dispose();
			Cue GetCue(char* name);
			void PlayCue(char* name);
			void PlayCue(char *name, AudioListener listener, AudioEmitter emitter);
			SoundBank(AudioEngine audioEngine, char* filename);
	};
}

#endif //XFRAMEWORK_SOUNDBANK_H
