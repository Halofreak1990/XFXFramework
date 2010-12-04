/********************************************************
 *	Enums.h												*
 *														*
 *	XFX::Media enumeration definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _MEDIA_ENUMS_H_
#define _MEDIA_ENUMS_H_

namespace XFX
{
	namespace Media
	{
		/// <summary>
		/// Type of the media source.
		/// </summary>
		struct MediaSourceType
		{
			enum type
			{
				LocalDevice,
				WindowsMediaConnect
			};
		};

		/// <summary>
		/// Media playback state (playing, paused, or stopped).
		/// </summary>
		struct MediaState
		{
			enum type
			{
				Paused,
				Playing,
				Stopped
			};
		};
		
		/// <summary>
		/// Type of sounds in a video
		/// </summary>
		struct VideoSoundtrackType
		{
			enum type
			{
				Dialog,
				Music,
				MusicAndDialog
			};
		};

		typedef MediaSourceType::type		MediaSourceType_t;
		typedef MediaState::type			MediaState_t;
		typedef VideoSoundtrackType::type	VideoSoundtrackType_t;
	}
}

#endif //_MEDIA_ENUMS_H_
