#ifndef XFRAMEWORK_AUDIOCATEGORY_H
#define XFRAMEWORK_AUDIOCATEGORY_H

namespace XFramework::Audio
{
	struct AudioCategory
	{
		char* Name;

		void Pause();
		int operator!=(AudioCategory &other);
		int operator==(AudioCategory &other);
		void Resume();
		void SetVolume(float volume);
		void Stop();
	};
}

#endif //XFRAMEWORK_AUDIOCATEGORY_H
