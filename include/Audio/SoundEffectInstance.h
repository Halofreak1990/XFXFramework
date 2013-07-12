/*****************************************************************************
 *	SoundEffectInstance.h													 *
 *																			 *
 *	XFX::Audio::SoundEffectInstance class definition file					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#include <System/Interfaces.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Audio
	{
		class AudioListener;
		class AudioEmitter;
		class SoundEffect;

		/**
		 * Provides a single playing, paused, or stopped instance of a SoundEffect sound.
		 */
		class SoundEffectInstance : public IDisposable, public Object
		{
		private:
			friend class SoundEffect;

			float _pan;
			SoundEffect* _parent;
			float _volume;

			SoundEffectInstance(SoundEffect* parent);

			virtual void Dispose(bool disposing);

		public:
			bool IsDisposed() const;
			virtual bool IsLooped() const;
			virtual void IsLooped(bool value);
			float getPan() const;
			void setPan(float value);
			float getPitch() const;
			void setPitch(float value);
			SoundState_t getState() const;
			float getVolume() const;
			void setVolume(float value);

			~SoundEffectInstance();

			void Apply3D(AudioListener listener, AudioEmitter emitter);
			void Apply3D(AudioListener listeners[], AudioEmitter emitter);
			void Dispose();
			static const Type& GetType();
			void Pause();
			virtual void Play();
			void Resume();
			void Stop();
			void Stop(bool immediate);
		};
	}
}
