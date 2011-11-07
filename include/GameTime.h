/********************************************************
 *	GameTime.h											*
 *														*
 *	XFX GameTime definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAMETIME_
#define _XFX_GAMETIME_

#include <System/TimeSpan.h>

using namespace System;

namespace XFX
{
	// Snapshot of the game timing state expressed in values that can be used by variable-step (real time) or fixed- step (game time) games.
	class GameTime
	{
	private:
		TimeSpan _elapsedGameTime; 
     	TimeSpan _elapsedRealTime; 
     	bool _isRunningSlowly; 
     	TimeSpan _totalGameTime; 
     	TimeSpan _totalRealTime; 	
	
	public:
		TimeSpan ElapsedGameTime();
		TimeSpan ElapsedRealTime();
		bool IsRunningSlowly();
		TimeSpan TotalGameTime();
		TimeSpan TotalRealTime();
	
		GameTime(TimeSpan totalRealTime, TimeSpan elapsedRealTime, TimeSpan totalGameTime, TimeSpan elapsedGameTime);
		GameTime(TimeSpan totalRealTime, TimeSpan elapsedRealTime, TimeSpan totalGameTime, TimeSpan elapsedGameTime, bool isRunningSlowly);
		GameTime();
	};
}

#endif //_XFX_GAMETIME_
