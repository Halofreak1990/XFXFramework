/********************************************************
 *	GameComponentCollectionEventArgs.h					*
 *														*
 *	XFX GameComponentCollectionEventArgs definition		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAMECOMPONENTCOLLECTIONEVENTARGS_
#define _XFX_GAMECOMPONENTCOLLECTIONEVENTARGS_

#include "Interfaces.h"
#include <SYstem/EventArgs.h>

namespace XFX
{
	/// <summary>
	/// Arguments used with events from the GameComponentCollection.
	/// </summary>
	class GameComponentCollectionEventArgs : EventArgs
	{
	private:
		IGameComponent _gameComponent;

	public:
		IGameComponent GameComponent_();

		GameComponentCollectionEventArgs(IGameComponent gameComponent);
	};
}

#endif //_XFX_GAMECOMPONENTCOLLECTIONEVENTARGS_
