/********************************************************
 *	Delegates.h											*
 *														*
 *	Defines delegates within the System namespace		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_DELEGATES_
#define _SYSTEM_DELEGATES_

#include "EventArgs.h"
#include "Interfaces.h"

namespace System
{
	/// <summary>
	/// References a method to be called when a corresponding asynchronous operation completes.
	/// </summary>
	typedef void *(ASyncCallback)(IAsyncResult ar);

	/// <summary>
	/// Represents the method that will handle an event that has no event data.
	/// </summary>
	typedef void *(EventHandler)(void* sender, EventArgs e);
}

#endif
