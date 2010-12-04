/********************************************************
 *	AudioListener.h										*
 *														*
 *	XFramework AudioListener definition file			*
 *	Copyright © XFX Team. All Rights Reserved		*
 ********************************************************/

#ifndef XFRAMEWORK_AUDIOLISTENER_H
#define XFRAMEWORK_AUDIOLISTENER_H

#include "System/System.h"

namespace XFramework
{
	class Vector3;
	
	namespace Audio
	{
		class AudioListener
		{
			public:
				Vector3 Forward;
				Vector3 Position;
				Vector3 Up;
				Vector3 Velocity;

				AudioListener();
		}
	}
}

#endif //XFRAMEWORK_AUDIOLISTENER_H
