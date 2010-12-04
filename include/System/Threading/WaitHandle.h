/********************************************************
 *	WaitHandle.h										*
 *														*
 *	XFX WaitHandle definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_THREADING_WAITHANDLE_
#define _SYSTEM_THREADING_WAITHANDLE_

#include "../Types.h"

namespace System
{
	namespace Threading
	{
		/// <summary>
		/// Encapsulates operating system–specific objects that wait for exclusive access to shared resources.
		/// </summary>
		class WaitHandle
		{
		protected:
			static const IntPtr InvalidHandle;

			virtual void Dispose(bool explicitDisposing);
			WaitHandle();

		public:
			IntPtr Handle;

			virtual void Close();
			virtual bool WaitOne();
			virtual bool WaitOne(int millisecondsTimeout, bool exitContext);
		};
	}
}

#endif //_SYSTEM_THREADING_WAITHANDLE_
