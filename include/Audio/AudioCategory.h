/*****************************************************************************
 *	AudioCategory.h 														 *
 *																			 *
 *	XFX XFX::Audio::AudioCategory definition file							 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef XFX_AUDIO_AUDIOCATEGORY_H
#define XFX_AUDIO_AUDIOCATEGORY_H

#include <System/String.h>

using namespace System;

namespace XFX
{
	namespace Audio
	{
		struct AudioCategory : Object
		{
			String Name;

			static const Type& GetType();
			void Pause();
			void Resume();
			void SetVolume(float volume);
			void Stop();

			bool operator!=(const AudioCategory& other) const;
			bool operator==(const AudioCategory& other) const;
		};
	}
}

#endif // XFX_AUDIO_AUDIOCATEGORY_H
