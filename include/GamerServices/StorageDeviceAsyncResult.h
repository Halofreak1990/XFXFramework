
#include <System/Interfaces.h>
#include <System/Threading/WaitHandle.h>

using namespace System;
using namespace System::Threading;

namespace XFX
{
	namespace GamerServices
	{
		class Guide;

		class StorageDeviceAsyncResult : public IAsyncResult
		{
			friend class Guide;

		private:
			Object* syncObject;
			int playerIndex;

			StorageDeviceAsyncResult(Object* stateObject, int player);
			StorageDeviceAsyncResult(const StorageDeviceAsyncResult &obj);
			StorageDeviceAsyncResult(IAsyncResult* &obj);

		public:
			Object* AsyncState();
			bool CompletedSynchronously();
			bool IsCompleted();
			WaitHandle* AsyncWaitHandle();
		};
	}
}
