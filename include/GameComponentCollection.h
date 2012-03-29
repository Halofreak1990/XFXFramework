/********************************************************
 *	GameComponentCollection.h							*
 *														*
 *	XFX GameComponentCollection definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAMECOMPONENTCOLLECTION_
#define _XFX_GAMECOMPONENTCOLLECTION_

#include "Interfaces.h"
#include <System/Delegates.h>
#include <System/Collections/Generic/List.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	// A collection of game components.
	class GameComponentCollection : virtual Object
	{
	private:
		List<IGameComponent*> _components;

	protected:
		void ClearItems();
		void InsertItem(int index, IGameComponent* item);
		void RemoveItem(int index);
		void SetItem(int index, IGameComponent* item);
		
	public:
		int Count() const;

		GameComponentCollection();
		virtual ~GameComponentCollection();
		IGameComponent* operator[](const int index);

		EventHandler ComponentAdded;
		EventHandler ComponentRemoved;
	};
}

#endif //_XFX_GAMECOMPONENTCOLLECTION_
