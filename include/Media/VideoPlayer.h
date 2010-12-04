/********************************************************
 *	VideoPlayer.h										*
 *														*
 *	XFX VideoPlayer file								*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _VIDEOPLAYER_H_
#define _VIDEOPLAYER_H_

#include "../Graphics/Texture2D.h"

namespace XFX
{
	class TimeSpan;

	namespace Media
	{
		class Video;

		/// <summary>
		/// Provides methods and properties to playback, pause, resume, and stop video. VideoPlayer also exposes repeat, volume, and play position information.
		/// </summary>
		class VideoPlayer
		{
		private:
			int isDisposed;
			void Dispose(bool disposing);

		protected:
			~VideoPlayer();
			
		public:
			int IsDisposed();
			int IsLooped;
			int IsMuted;
			TimeSpan PlayPosition();
			MediaState_t State();
			Video Video_();
			float Volume;
		
			VideoPlayer();
		
			void Dispose();
			Texture2D GetTexture();
			void Pause();
			void Play(Video &video);
			void Resume();
			void Stop();
		};
	}
}

#endif //_VIDEOPLAYER_H_
