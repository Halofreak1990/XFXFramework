/********************************************************
 *	Enums.h												*
 *														*
 *	XFX::Audio enumerations definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_AUDIO_ENUMS_
#define _XFX_AUDIO_ENUMS_

namespace XFX
{
	namespace Audio
	{
		struct AudioChannels
		{
			enum type
			{
				// Indicates audio data is contained in one channel.
				Mono = 1,
				// Indicates audio data is contained in two channels.
				Stereo = 2
			};
		};

		struct AudioStopOptions
		{
			enum type
			{
				AsAuthored,
				Immediate
			};
		};

		typedef AudioChannels::type		AudioChannels_t;	// Defines the number of audio channels in the audio data.
		typedef AudioStopOptions::type	AudioStopOptions_t;	// Controls how Cue objects should stop when Cue::Stop is called.
	}
}

#endif //_XFX_AUDIO_ENUMS_
