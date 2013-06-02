/********************************************************
 *	GamerServicesComponent.h							*
 *														*
 *	XFX GamerServicesComponent class definition file	*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAMERSERVICES_GAMERSERVICESCOMPONENT_
#define _XFX_GAMERSERVICES_GAMERSERVICESCOMPONENT_

#include "../Game.h"

namespace XFX
{
	namespace GamerServices
	{
		// Creates a new GamerServicesComponent.
		class GamerServicesComponent : public GameComponent
		{	
		public:
			GamerServicesComponent(Game * const game);
	
			int GetType() const;
			void Initialize();
			void Update(GameTime gameTime);
		};
	}
}

#endif //_XFX_GAMERSERVICES_GAMERSERVICESCOMPONENT_
