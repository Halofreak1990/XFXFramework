/********************************************************
 *	VideoPlayer.h										*
 *														*
 *	XFX VideoPlayer file								*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_MEDIA_VIDEOPLAYER_
#define _XFX_MEDIA_VIDEOPLAYER_

#include "Enums.h"
#include <Graphics/Texture2D.h>
#include <System/TimeSpan.h>

using namespace System;
using namespace XFX::Graphics;

namespace XFX
{
	namespace Media
	{
		class Video;

		/**
		 * Provides methods and properties to playback, pause, resume, and stop video. VideoPlayer also exposes repeat, volume, and play position information.
		 */
		class VideoPlayer
		{
		private:
			bool isDisposed;
			Video* playingVideo;

			void Dispose(bool disposing);

		protected:
			~VideoPlayer();
			
		public:
			bool IsDisposed();
			bool IsLooped;
			bool IsMuted;
			TimeSpan getPlayPosition();
			MediaState_t getState();
			Video* getVideo();
			float Volume;
		
			VideoPlayer();
		
			void Dispose();
			Texture2D* GetTexture();
			void Pause();
			void Play(Video* video);
			void Resume();
			void Stop();
		};
	}
}

#endif //_XFX_MEDIA_VIDEOPLAYER_
