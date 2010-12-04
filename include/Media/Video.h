/********************************************************
 *	Video.h												*
 *														*
 *	XFX Video definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <System.h>
#include "Enums.h"

namespace XFX
{
	namespace Media
	{
		/// <summary>
		/// Represents a video.
		/// </summary>
		class Video
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

#endif //_VIDEO_H_
