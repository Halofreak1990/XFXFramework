
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
			// TODO: implement
			return true;
		}

		StorageDeviceAsyncResult::StorageDeviceAsyncResult(Object * const stateObject, int player)
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
			// TODO: implement
		}
	}
}
