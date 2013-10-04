#ifndef _SYSTEM_DIAGNOSTICS_STOPWATCH_
#define _SYSTEM_DIAGNOSTICS_STOPWATCH_

#include <System/TimeSpan.h>

namespace System
{
	namespace Diagnostics
	{
		/**
		 * 
		 */
		class Stopwatch
		{
		private:
			bool isRunning;
			long long elapsedTicks;

		public:
			static const long long Frequency;

			TimeSpan getElapsed() const;
			/**
			 * Gets the total elapsed time measured by the current instance, in milliseconds.
			 */
			long long getElapsedMilliseconds() const;
			long long getElapsedTicks() const;
			bool IsRunning() const;

			Stopwatch();

			static long long GetTimestamp();
			void Reset();
			void Restart();
			void Start();
			static const Stopwatch& StartNew();
			void Stop();
		};
	}
}

#endif //_SYSTEM_DIAGNOSTICS_STOPWATCH_
