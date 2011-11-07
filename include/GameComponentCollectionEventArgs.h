/********************************************************
 *	GameComponentCollectionEventArgs.h					*
 *														*
 *	XFX GameComponentCollectionEventArgs definition		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAMECOMPONENTCOLLECTIONEVENTARGS_
#define _XFX_GAMECOMPONENTCOLLECTIONEVENTARGS_

#include "Interfaces.h"
#include <System/EventArgs.h>

namespace XFX
{
	// Arguments used with events from the GameComponentCollection.
	class GameComponentCollectionEventArgs : public EventArgs, virtual Object
	{
	private:
		IGameComponent _gameComponent;

	public:
		IGameComponent getGameComponent();

		GameComponentCollectionEventArgs(IGameComponent gameComponent);
	};
}

#endif //_XFX_GAMECOMPONENTCOLLECTIONEVENTARGS_
