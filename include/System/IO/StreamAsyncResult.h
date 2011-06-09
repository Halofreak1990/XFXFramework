/********************************************************
 *	StreamAsyncResult.h									*
 *														*
 *	XFX StreamAsyncResult definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_STREAMASYNCRESULT_
#define _SYSTEM_IO_STREAMASYNCRESULT_

#include "../Exception.h"
#include "../Interfaces.h"
#include "../Object.h"
#include "../Types.h"
#include "../Threading/WaitHandle.h"

namespace System
{
	namespace IO
	{
		/// <summary>
		/// 
		/// </summary>
		class StreamAsyncResult : public IAsyncResult, virtual Object
		{
			Object* _state;
			bool completed;
			bool done;
			Exception* exc;
			int _nbytes;

		public:
			Object* ASyncState();
			Threading::WaitHandle* AsyncWaitHandle();
			virtual bool CompletedSynchronously();
			bool IsCompleted();
			Exception* Exception_();
			int NBytes();
			bool Done;

			StreamAsyncResult(Object* state);
			StreamAsyncResult(const IAsyncResult* &obj);
			StreamAsyncResult(const StreamAsyncResult &obj);

			void SetComplete(Exception* e);
			void SetComplete(Exception* e, int nbytes);
		};
	}
}

#endif //_SYSTEM_IO_STREAMASYNCRESULT_
