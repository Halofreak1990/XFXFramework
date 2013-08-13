/********************************************************
 *	AudioEmitter.h  									*
 *														*
 *	XFX::Audio::AudioEmitter definition file			*
 *	Copyright (c) XFX Team. All Rights Reserved 		*
 ********************************************************/
#ifndef _XFX_AUDIO_AUDIOEMITTER_
#define _XFX_AUDIO_AUDIOEMITTER_

#include <System/Object.h>
#include <System/Type.h>
#include <Vector3.h>

using namespace System;

namespace XFX
{
	namespace Audio
	{		
		class AudioEmitter : public Object
		{
		private:
			static const Type AudioEmitterTypeInfo;

		public:
			float DopplerScale;
			Vector3 Forward;
			Vector3 Position;
			Vector3 Up;
			Vector3 Velocity;

			AudioEmitter() { }

			const Type& GetType()
			{
				return AudioEmitterTypeInfo;
			}
		};

		const Type AudioEmitter::AudioEmitterTypeInfo = Type("AudioEmitter", "XFX::Audio::AudioEmitter", TypeCode::Object);
	}
}

#endif //XFX_AUDIO_AUDIOEMITTER_H
