#include <Audio/SoundEffect.h>
#include <Audio/SoundEffectInstance.h>

namespace XFX
{
	namespace Audio
	{
		SoundEffect::SoundEffect(byte buffer[], int sampleRate, AudioChannels_t numChannels)
		{
		}

		SoundEffect::SoundEffect(const SoundEffect &obj)
		{
		}

		SoundEffect::~SoundEffect()
		{
		}

		SoundEffectInstance SoundEffect::CreateInstance()
		{
		}

		void SoundEffect::Dispose()
		{
			Dispose(true);
		}

		void SoundEffect::Dispose(bool disposing)
		{
		}

		SoundEffect SoundEffect::FromStream(Stream* stream)
		{
		}

		bool SoundEffect::Play()
		{
		}

		bool SoundEffect::Play(float volume, float pitch, float pan)
		{
		}
	}
}
