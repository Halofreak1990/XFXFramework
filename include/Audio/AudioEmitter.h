/********************************************************
 *	AudioEmitter.h										*
 *														*
 *	XFX AudioEmitter definition file					*
 *	Copyright © XFX Team. All Rights Reserved		*
 ********************************************************/
#ifndef AUDIOEMITTER_H
#define AUDIOEMITTER_H

#include "System/System.h"

namespace XFX
{
	namespace Audio
	{
		class Vector3;
		
		class Audioemitter
		{
			public:
				float DopplerScale;
				Vector3 Forward;
				Vector3 Position;
				Vector3 Up;
				Vector3 Velocity;
	
				AudioEmitter();
				
		}
	}
}

#endif //AUDIOEMITTER_H
