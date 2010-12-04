#ifndef XFRAMEWORK_WAVEBANK_H
#define XFRAMEWORK_WAVEBANK_H

#include "AudioEngine.h"
#include "../Net_Framework/System.h"

namespace XFramework::Audio
{
	class WaveBank
	{
		private:
			int isDisposed;
			int isInUse;
			int isPrepared;

		protected:
			void Dispose(int disposing);

		public:
			int IsDisposed();
			int IsInUse();
			int IsPrepared();

			void Dispose();
			WaveBank(AudioEngine audioEngine, char* nonStreamingWaveBankFilename);
			WaveBank(AudioEngine audioEngine, char* streamingWaveBankFilename, int offset, short packetsize);
	}
}

#endif //XFRAMEWORK_WAVEBANK_H
