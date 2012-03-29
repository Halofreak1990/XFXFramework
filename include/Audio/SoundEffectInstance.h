
#include <System/Interfaces.h>

using namespace System;

namespace XFX
{
	namespace Audio
	{
		// Provides a single playing, paused, or stopped instance of a SoundEffect sound.
		class SoundEffectInstance : public IDisposable, virtual Object
		{
			friend class SoundEffect;

			SoundEffect* _parent;

		private:
			SoundEffectInstance(SoundEffect* parent);

		public:
			~SoundEffectInstance();

			void Pause();
			void Play();
			void Resume();
			void Stop();
		};
	}
}
