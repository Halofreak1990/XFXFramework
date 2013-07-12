/*****************************************************************************
 *	GameComponentCollectionEventArgs.h  									 *
 *																			 *
 *	XFX GameComponentCollectionEventArgs definition 						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GAMECOMPONENTCOLLECTIONEVENTARGS_
#define _XFX_GAMECOMPONENTCOLLECTIONEVENTARGS_

#include "Interfaces.h"
#include <System/EventArgs.h>

namespace XFX
{
	/**
	 * Arguments used with events from the GameComponentCollection.
	 */
	class GameComponentCollectionEventArgs : public EventArgs
	{
	private:
		IGameComponent* _gameComponent;

	public:
		IGameComponent* getGameComponent() const;

		GameComponentCollectionEventArgs(IGameComponent * const gameComponent);
		virtual ~GameComponentCollectionEventArgs() { }

		static const Type& GetType();
	};
}

#endif //_XFX_GAMECOMPONENTCOLLECTIONEVENTARGS_
