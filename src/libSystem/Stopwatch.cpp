#include <System/Diagnostics/Stopwatch.h>

#if ENABLE_XBOX
#include <xboxkrnl/xboxkrnl.h>
#else
#endif

namespace System
{
	namespace Diagnostics
	{
		const long long Stopwatch::Frequency = KeQueryPerformanceFrequency();

		TimeSpan Stopwatch::getElapsed() const
		{
			return TimeSpan::FromTicks(elapsedTicks);
		}

		long long Stopwatch::getElapsedMilliseconds() const
		{
			return getElapsed().Milliseconds();
		}

		long long Stopwatch::getElapsedTicks() const
		{
			return elapsedTicks;
		}

		bool Stopwatch::IsRunning() const
		{
			return isRunning;
		}

		Stopwatch::Stopwatch()
		{
		}

		long long Stopwatch::GetTimestamp()
		{
			return KeQueryPerformanceCounter();
		}

		void Stopwatch::Restart()
		{
			Reset();
			Start();
		}

		void Stopwatch::Start()
		{

			isRunning = true;
		}

		const Stopwatch& Stopwatch::StartNew()
		{
			Stopwatch sw = Stopwatch();
			sw.Start();
			return sw;
		}

		void Stopwatch::Stop()
		{

			isRunning = false;
		}
	}
}
