/********************************************************
 *	AudioListener.h										*
 *														*
 *	XFX::Audio::AudioListener definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_AUDIO_AUDIOLISTENER_
#define _XFX_AUDIO_AUDIOLISTENER_

#include <System/Object.h>
#include <Vector3.h>

using namespace System;

namespace XFX
{
	namespace Audio
	{
		class AudioListener : public Object
		{
		public:
			Vector3 Forward;
			Vector3 Position;
			Vector3 Up;
			Vector3 Velocity;

			AudioListener();

			int GetType() const;
		};
	}
}

#endif //_XFX_AUDIO_AUDIOLISTENER_
