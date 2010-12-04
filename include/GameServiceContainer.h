/********************************************************
 *	GameServiceContainer.h								*
 *														*
 *	XFX GameServiceContainer definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAMESERVICECONTAINER_
#define _XFX_GAMESERVICECONTAINER_

namespace XFX
{
	/// <Summary>
	/// A collection of game services.
	/// </summary>
	class GameServiceContainer
	{
	public:
		template <class T>
		void AddService(T type, void* provider);
		GameServiceContainer();
		template <class T>
		void* GetService(T type);
		template <class T>
		void RemoveService(T type);
	};
}

#endif //_XFX_GAMESERVICECONTAINER_H
