/********************************************************
 *	Delegates.h											*
 *														*
 *	Defines delegates within the System namespace		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_DELEGATES_
#define _SYSTEM_DELEGATES_

#include "EventArgs.h"
#include "Object.h"
#include "Interfaces.h"

namespace System
{
	// References a method to be called when a corresponding asynchronous operation completes.
	typedef void (*AsyncCallback)(IAsyncResult* ar);

	// Represents the method that will handle an event that has no event data.
	//typedef void (*EventHandler)(Object* sender, EventArgs e);
}

#endif
