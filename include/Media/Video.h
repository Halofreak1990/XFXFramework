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
			/**
			 * Gets the duration of the Video.
			 */
			TimeSpan getDuration() const;
			/**
			 * Gets the frame rate of this video.
			 */
			float getFramesPerSecond() const;
			/**
			 * Gets the height of this video, in pixels.
			 */
			int getHeight() const;
			/**
			 * Gets the VideoSoundtrackType for this video.
			 */
			VideoSoundtrackType_t getVideoSoundtrackType() const;
			/**
			 * Gets the width of this video, in pixels.
			 */
			int getWidth() const;

			static const Type& GetType();
		};
	}
}

#endif //_XFX_MEDIA_VIDEO_H_
