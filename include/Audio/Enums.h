/********************************************************
 *	Enums.h												*
 *														*
 *	XFX::Audio enumerations definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef XFX_AUDIO_ENUMS_
#define XFX_AUDIO_ENUMS_

namespace XFX
{
	namespace Audio
	{
		/// <summary>
		/// Controls how Cue objects should stop when Cue.Stop is called.
		/// </summary>
		struct AudioStopOptions
		{
			enum type
			{
				AsAuthored,
				Immediate
			};
		};

		typedef AudioStopOptions::type AudioStopOptions_t;
	}
}

#endif //XFRAMEWORK_AUDIOSTOPOPTIONS_H
