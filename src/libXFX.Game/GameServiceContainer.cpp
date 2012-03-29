#include <GameServiceContainer.h>

namespace XFX
{
	GameServiceContainer::GameServiceContainer()
	{
		_services = new Dictionary<const char*, Object*>();
	}

	GameServiceContainer::~GameServiceContainer()
	{
		delete _services;
	}

	void GameServiceContainer::AddService(const char* serviceType, Object* provider)
	{
		_services->Add(serviceType, provider);
	}

	Object* GameServiceContainer::GetService(const char* serviceType)
	{
		Object* service = null;
		if (_services->TryGetValue(serviceType, service))
			return service;

		return null;
	}

	void GameServiceContainer::RemoveService(const char* type)
	{
		_services->Remove(type);
	}
}
