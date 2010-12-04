/********************************************************
 *	AudioEngine.h										*
 *														*
 *	XFramework AudioEngine definition file				*
 *	Copyright © XFX Team. All Rights Reserved		*
 ********************************************************/
#ifndef XFRAMEWORK_AUDIOENGINE_H
#define XFRAMEWORK_AUDIOENGINE_H

#include "System/System.h"

namespace XFramework
{
	namespace Audio
	{
		class AudioCategory;
		
		class AudioEngine
		{
			protected:
				virtual void Dispose(int disposing);
		
			public:
				const int ContentVersion; //XACT version supported

				AudioEngine(); //Initialize the audio engine for direct wav play.
				AudioEngine(char* settingsFile); //Initialize the audio engine for XACT
				AudioEngine(char* settingsFile, Timespan &lookAheadTime, char* rendererId);
				
				void Dispose();
				AudioCategory GetCategory(char* name);
				float GetGlobalVariable(char* name);
				void SetGlobalVariable(char* name, float value);
				void Update();
		};
	}
}

#endif //XFRAMEWORK_AUDIOENGINE_H
