/********************************************************
 *	GamerServicesComponent.h							*
 *														*
 *	XFX GamerServicesComponent class definition file	*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAMERSERVICES_GAMERSERVICESCOMPONENT_
#define _XFX_GAMERSERVICES_GAMERSERVICESCOMPONENT_

#include "../Game.h"

namespace XFX
{
	namespace GamerServices
	{
		/// <summary>
		/// Creates a new GamerServicesComponent.
		/// </summary>
		class GamerServicesComponent : public GameComponent
		{	
		public:
			GamerServicesComponent(Game game);
	
			void Initialize();
			void Update(GameTime gameTime);
		};
	}
}

#endif //_XFX_GAMERSERVICES_GAMERSERVICESCOMPONENT_
