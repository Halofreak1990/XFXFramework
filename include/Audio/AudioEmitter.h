/********************************************************
 *	AudioEmitter.h  									*
 *														*
 *	XFX::Audio::AudioEmitter definition file			*
 *	Copyright (c) XFX Team. All Rights Reserved 		*
 ********************************************************/
#ifndef _XFX_AUDIO_AUDIOEMITTER_
#define _XFX_AUDIO_AUDIOEMITTER_

#include <System/Object.h>
#include <Vector3.h>

namespace XFX
{
	namespace Audio
	{		
		class AudioEmitter : public Object
		{
		public:
			float DopplerScale;
			Vector3 Forward;
			Vector3 Position;
			Vector3 Up;
			Vector3 Velocity;

			AudioEmitter() { }

			inline int GetType() const { }
		};
	}
}

#endif //XFX_AUDIO_AUDIOEMITTER_H
