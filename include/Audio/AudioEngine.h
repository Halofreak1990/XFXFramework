/*****************************************************************************
 *	AudioEngine.h															 *
 *																			 *
 *	XFX AudioEngine definition file 										 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef XFX_AUDIO_AUDIOENGINE_H
#define XFX_AUDIO_AUDIOENGINE_H

#include <System/String.h>

using namespace System;

namespace XFX
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
			AudioEngine(String& settingsFile); //Initialize the audio engine for XACT
			AudioEngine(String& settingsFile, TimeSpan lookAheadTime, char* rendererId);
				
			void Dispose();
			AudioCategory GetCategory(String& name);
			float GetGlobalVariable(String& name);
			void SetGlobalVariable(String& name, float value);
			void Update();
		};
	}
}

#endif // XFX_AUDIO_AUDIOENGINE_H
