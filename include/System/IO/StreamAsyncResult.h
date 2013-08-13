/*****************************************************************************
 *	StreamAsyncResult.h 													 *
 *																			 *
 *	System::IO::StreamAsyncResult class definition file 					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_IO_STREAMASYNCRESULT_
#define _SYSTEM_IO_STREAMASYNCRESULT_

#include <System/Interfaces.h>
#include <System/Object.h>
#include <System/Types.h>
#include <System/Threading/WaitHandle.h>

namespace System
{
	namespace IO
	{
		/**
		 * 
		 */
		class StreamAsyncResult : public IAsyncResult, public Object
		{
		private:
			Object* _state;
			bool completed;
			bool done;
			//Exception* exc;
			int _nbytes;

		public:
			Object* AsyncState();
			Threading::WaitHandle* AsyncWaitHandle();
			virtual bool CompletedSynchronously();
			bool IsCompleted();
			//Exception* getException();
			int NBytes();
			bool Done;

			/**
			 * 
			 *
			 * @param state
			 *
			 */
			StreamAsyncResult(Object* state);
			/**
			 * 
			 *
			 * @param obj
			 * 
			 */
			StreamAsyncResult(const IAsyncResult &obj);
			/**
			 * 
			 *
			 * @param obj
			 * 
			 */
			StreamAsyncResult(const StreamAsyncResult &obj);

			//void SetComplete(Exception* e);
			//void SetComplete(Exception* e, int nbytes);
		};
	}
}

#endif //_SYSTEM_IO_STREAMASYNCRESULT_
