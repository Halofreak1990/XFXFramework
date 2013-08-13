/*****************************************************************************
 *	Video.h 																 *
 *																			 *
 *	XFX::Media::Video class definition file 								 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_MEDIA_VIDEO_H_
#define _XFX_MEDIA_VIDEO_H_

#include <System/TimeSpan.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Media
	{
		/**
		 * Represents a video.
		 */
		class Video : public Object
		{
		public:
			TimeSpan getDuration();
			float getFramesPerSecond();
			int getHeight();
			VideoSoundtrackType_t getVideoSoundtrackType();
			int getWidth();

			static const Type& GetType();
		};
	}
}

#endif //_XFX_MEDIA_VIDEO_H_
