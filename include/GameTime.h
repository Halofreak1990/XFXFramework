/*****************************************************************************
 *	GameTime.h																 *
 *																			 *
 *	XFX GameTime class definition file										 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GAMETIME_
#define _XFX_GAMETIME_

#include <System/TimeSpan.h>

using namespace System;

namespace XFX
{
	/**
	 * Snapshot of the game timing state expressed in values that can be used by variable-step (real time) or fixed- step (game time) games.
	 */
	class GameTime : public Object
	{
	private:
		TimeSpan _elapsedGameTime; 
		bool _isRunningSlowly; 
		TimeSpan _totalGameTime; 
	
	public:
		TimeSpan getElapsedGameTime() const;
		bool IsRunningSlowly() const;
		TimeSpan getTotalGameTime() const;
	
		GameTime(const TimeSpan totalGameTime, const TimeSpan elapsedGameTime);
		GameTime(const TimeSpan totalGameTime, const TimeSpan elapsedGameTime, const bool isRunningSlowly);
		GameTime();

		static const Type& GetType();
	};
}

#endif //_XFX_GAMETIME_
