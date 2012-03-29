/********************************************************
 *	GameServiceContainer.h								*
 *														*
 *	XFX GameServiceContainer definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAMESERVICECONTAINER_
#define _XFX_GAMESERVICECONTAINER_

#include <System/Collections/Generic/Dictionary.h>
#include <System/Interfaces.h>
#include <System/Object.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	// A collection of game services.
	class GameServiceContainer : public IServiceProvider, virtual Object
	{
	private:
		Dictionary<const char*, Object*>* _services;

	public:
		GameServiceContainer();
		virtual ~GameServiceContainer();

		void AddService(const char* serviceType, Object* provider);
		Object* GetService(const char* ServiceType);
		void RemoveService(const char* type);
	};
}

#endif //_XFX_GAMESERVICECONTAINER_
