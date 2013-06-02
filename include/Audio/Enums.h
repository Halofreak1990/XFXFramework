/********************************************************
 *	Enums.h												*
 *														*
 *	XFX::Audio enumerations definition file				*
 *	Copyright (c) XFX Team. All Rights Reserved			*
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

		struct SoundState
		{
			enum type
			{
				// The SoundEffectInstance is playing.
				Playing,
				// The SoundEffectInstance is paused.
				Paused,
				// The SoundEffectInstance is stopped.
				Stopped
			};
		};

		typedef AudioChannels::type		AudioChannels_t;	// Defines the number of audio channels in the audio data.
		typedef AudioStopOptions::type	AudioStopOptions_t;	// Controls how Cue objects should stop when Cue::Stop is called.
		typedef SoundState::type		SoundState_t;		// Current state (playing, paused, or stopped) of a SoundEffectInstance.
	}
}

#endif //_XFX_AUDIO_ENUMS_
