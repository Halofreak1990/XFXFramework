/********************************************************
 *	GameServiceContainer.h								*
 *														*
 *	XFX GameServiceContainer definition file			*
 *	Copyright (c) XFX Team. All Rights Reserved			*
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
	class GameServiceContainer : public IServiceProvider
	{
	private:
		Dictionary<String, Object*> _services;

	public:
		GameServiceContainer();
		virtual ~GameServiceContainer() {}

		void AddService(const String& serviceType, Object* provider);
		Object* GetService(const String& ServiceType);
		void RemoveService(const String& type);
	};
}

#endif //_XFX_GAMESERVICECONTAINER_
