/********************************************************
 *	SoundEffectInstance.h								*
 *														*
 *	XFX::Audio::SoundEffectInstance definition file		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#include <System/Interfaces.h>

using namespace System;

namespace XFX
{
	namespace Audio
	{
		// Provides a single playing, paused, or stopped instance of a SoundEffect sound.
		class SoundEffectInstance : public IDisposable, public Object
		{
		private:
			friend class SoundEffect;

			SoundEffect* _parent;

			SoundEffectInstance(SoundEffect* parent);

		public:
			~SoundEffectInstance();

			void Dispose();
			int GetType() const;
			void Pause();
			void Play();
			void Resume();
			void Stop();
		};
	}
}
