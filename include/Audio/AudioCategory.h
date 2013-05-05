#ifndef XFX_AUDIO_AUDIOCATEGORY_H
#define XFX_AUDIO_AUDIOCATEGORY_H

#include <System/String.h>

namespace XFX
{
	namespace Audio
	{
		struct AudioCategory : Object
		{
			String Name;

			void Pause();
			bool operator!=(const AudioCategory &other) const;
			bool operator==(const AudioCategory &other) const;
			void Resume();
			void SetVolume(float volume);
			void Stop();
		};
	}
}

#endif //XFX_AUDIO_AUDIOCATEGORY_H
