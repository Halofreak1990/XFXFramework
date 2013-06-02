/********************************************************
 *	Enums.h												*
 *														*
 *	XFX::Media enumeration definition file				*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_MEDIA_ENUMS_H_
#define _XFX_MEDIA_ENUMS_H_

namespace XFX
{
	namespace Media
	{
		// Type of the media source.
		struct MediaSourceType
		{
			enum type
			{
				LocalDevice,
				WindowsMediaConnect
			};
		};

		// Media playback state (playing, paused, or stopped).
		struct MediaState
		{
			enum type
			{
				Paused,
				Playing,
				Stopped
			};
		};
		
		// Type of sounds in a video
		struct VideoSoundtrackType
		{
			enum type
			{
				Dialog,
				Music,
				MusicAndDialog
			};
		};

		typedef MediaSourceType::type		MediaSourceType_t;		// Type of the media source.
		typedef MediaState::type			MediaState_t;			// Media playback state (playing, paused, or stopped).
		typedef VideoSoundtrackType::type	VideoSoundtrackType_t;	// Type of sounds in a video
	}
}

#endif //_XFX_MEDIA_ENUMS_H_
