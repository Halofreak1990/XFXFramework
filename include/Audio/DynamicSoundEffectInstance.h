/*****************************************************************************
 *	DynamicSoundEffectInstance.h											 *
 *																			 *
 *	XFX::Audio::DynamicSoundEffectInstance definition file  				 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_AUDIO_DYNAMICSOUNDEFFECTINSTANCE_
#define _XFX_AUDIO_DYNAMICSOUNDEFFECTINSTANCE_

#include <Audio/SoundEffectInstance.h>
#include <System/Event.h>
#include <System/Collections/Generic/Queue.h>
#include <System/TimeSpan.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	namespace Audio
	{
		/**
		 * Provides properties, methods, and events for play back of the audio buffer.
		 */
		class DynamicSoundEffectInstance : public SoundEffectInstance
		{
		private:
			Queue<byte[]> bufferQueue;
			AudioChannels_t channels;
			int sampleRate;

		protected:
			void Dispose(bool disposing);

		public:
			/**
			 * The event that occurs when the number of audio capture buffers awaiting playback is less than or equal to two.
			 */
			EventHandler BufferNeeded;

			/**
			 * Initializes a new instance of this class, which creates a dynamic sound effect based on the specified sample rate and audio channel.
			 * 
			 * @param sampleRate
			 * Sample rate, in Hertz (Hz), of audio content.
			 * 
			 * @param channels
			 * Number of channels in the audio data.
			 * 
			 * @throws System::ArgumentOutOfRangeException
			 * 
			 */
			DynamicSoundEffectInstance(int sampleRate, AudioChannels_t channels);

			/**
			 * Returns the sample duration based on the specified size of the audio buffer.
			 * 
			 * @param sizeInBytes
			 * Size, in bytes, of the audio data.
			 * 
			 * @throws System::ObjectDisposedException
			 * 
			 * @throws System::ArgumentException
			 * 
			 */
			TimeSpan GetSampleDuration(int sizeInBytes);
			/**
			 * Returns the size of the audio buffer required to contain audio samples based on the specified duration.
			 * 
			 * @param duration
			 * TimeSpan object that contains the duration of the audio sample.
			 * 
			 * @throws System::ObjectDisposedException
			 * 
			 * @throws System::ArgumentOutOfException
			 *  
			 */
			int GetSampleSizeInBytes(TimeSpan duration);
			/**
			 * Begins or resumes audio playback.
			 * 
			 * @throws System::ObjectDisposedException
			 */
			void Play();
			/**
			 * Submits an audio buffer for playback. Playback begins at the specified offset, and the byte count determines the size of the sample played.
			 * 
			 * @param buffer
			 * Buffer that contains the audio data. The audio format must be PCM wave data.
			 * 
			 * @param offset
			 * Offset, in bytes, to the starting position of the data.
			 * 
			 * @param count
			 * Amount, in bytes, of data sent.
			 * 
			 * @throws System::ObjectDisposedException
			 * 
			 * @throws System::ArgumentException
			 * 
			 */
			void SubmitBuffer(byte buffer[], int offset, int count);
		};
	}
}

#endif // _XFX_AUDIO_DYNAMICSOUNDEFFECTINSTANCE_
