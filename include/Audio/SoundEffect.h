/********************************************************
 *	SoundEffect.h										*
 *														*
 *	XFX::Audio::SoundEffect definition file				*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_AUDIO_SOUNDEFFECT_
#define _XFX_AUDIO_SOUNDEFFECT_

#include <System/Interfaces.h>
#include <System/String.h>
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
			static float distanceScale;
			static float dopplerScale;
			static float masterVolume;
			static float speedOfSound;

			void Dispose(bool disposing);

		public:
			static float getDistanceScale();
			static void setDistanceScale(float value);
			static float getDopplerScale();
			static void setDopplerScale(float value);
			TimeSpan getDuration() const;
			bool IsDisposed() const;
			static float getMasterVolume();
			static void setMasterVolume(float value);
			String Name;
			static float getSpeedOfSound();
			static void setSpeedOfSound(float value);

			SoundEffect(byte buffer[], const int offset, const int count, const int sampleRate, AudioChannels_t channels, const int loopStart, const int loopLength);
			SoundEffect(byte buffer[], const int sampleRate, const AudioChannels_t numChannels);
			SoundEffect(const SoundEffect &obj);
			~SoundEffect();

			SoundEffectInstance* CreateInstance();
			void Dispose();
			static SoundEffect* FromStream(Stream * const stream);
			static TimeSpan GetSampleDuration(int sizeInBytes, int sampleRate, AudioChannels_t channels);
			static int GetSampleSizeInBytes(TimeSpan duration, int sampleRate, AudioChannels_t channels);
			static int GetType();
			bool Play();
			bool Play(const float volume, const float pitch, const float pan);
		};
	}
}

#endif //_XFX_AUDIO_SOUNDEFFECT_
