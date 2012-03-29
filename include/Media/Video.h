/********************************************************
 *	Video.h												*
 *														*
 *	XFX Video definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_MEDIA_VIDEO_H_
#define _XFX_MEDIA_VIDEO_H_

#include <System/Types.h>
#include <System/Object.h>
#include "Enums.h"

namespace XFX
{
	namespace Media
	{
		// Represents a video.
		class Video : virtual Object
		{
		public:
			TimeSpan Duration();
			float FramesPerSecond();
			int Height();
			VideoSoundtrackType_t videoSoundtrackType();
			int Width();
		};
	}
}

#endif //_XFX_MEDIA_VIDEO_H_
