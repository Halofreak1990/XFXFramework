/********************************************************
 *	GameComponentCollection.h							*
 *														*
 *	XFX GameComponentCollection definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAMECOMPONENTCOLLECTION_
#define _XFX_GAMECOMPONENTCOLLECTION_

#include "Interfaces.h"

namespace XFX
{

	/// <summary>
	/// A collection of game components.
	/// </summary>
	class GameComponentCollection
	{
	protected:
		void ClearItems();
		void InsertItem(int index, IGameComponent* item);
		void RemoveItem(int index);
		void SetItem(int index, IGameComponent* item);
		
	public:
		GameComponentCollection();
	};
}

#endif //_XFX_GAMECOMPONENTCOLLECTION_
