/********************************************************
 *	GameServiceContainer.h								*
 *														*
 *	XFX GameServiceContainer definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAMESERVICECONTAINER_
#define _XFX_GAMESERVICECONTAINER_

#include <System/Interfaces.h>
#include <System/Object.h>

namespace XFX
{
	/// <Summary>
	/// A collection of game services.
	/// </summary>
	class GameServiceContainer : public IServiceProvider
	{
	public:
		void AddService(Object* provider);
		GameServiceContainer();
		Object* GetService(Object* serviceType);
		void RemoveService(Object* type);
	};
}

#endif //_XFX_GAMESERVICECONTAINER_H
