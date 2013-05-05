
#include <GamerServices/StorageDeviceAsyncResult.h>

namespace XFX
{
	namespace GamerServices
	{
		Object* StorageDeviceAsyncResult::AsyncState()
		{
			return syncObject;
		}

		bool StorageDeviceAsyncResult::CompletedSynchronously()
		{
			return true;
		}

		StorageDeviceAsyncResult::StorageDeviceAsyncResult(Object* stateObject, int player)
		{
			syncObject = stateObject;
			playerIndex = player;
		}

		StorageDeviceAsyncResult::StorageDeviceAsyncResult(const StorageDeviceAsyncResult &obj)
		{
			syncObject = obj.syncObject;
			playerIndex = obj.playerIndex;
		}

		StorageDeviceAsyncResult::StorageDeviceAsyncResult(IAsyncResult* &obj)
		{
			
		}
	}
}
