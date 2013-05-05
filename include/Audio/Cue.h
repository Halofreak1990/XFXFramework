/********************************************************
 *	Cue.h												*
 *														*
 *	XFramework Cue definition file						*
 *	Copyright © XFX Team. All Rights Reserved		*
 ********************************************************/
#ifndef XFRAMEWORK_CUE_H
#define XFRAMEWORK_CUE_H

namespace XFramework
{
	namespace Audio
	{
		class AudioEmitter;
		class AudioListener;
		
		class Cue
		{
			private:
				int isPaused;
				int isPlaying;
				int isStopped;
	
			public:
				int IsPaused();
				int IsPlaying();
				int IsStopped();
				char* Name;
				
				void Apply3D(AudioListener &listener, AudioEmitter &emitter);
				float GetVariable(char* name);
				void Pause();
				void Play();
				void SetVariable(char* name, float value);
				void Stop();
		};
	}
}

#endif //XFRAMEWORK_CUE_H
