/********************************************************
 *	StateBlock.h										*
 *														*
 *	XFX StateBlock definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_STATEBLOCK_
#define _XFX_GRAPHICS_STATEBLOCK_

#include <System/Delegates.h>
#include "GraphicsDevice.h"

namespace XFX
{
	namespace Graphics
	{
		class StateBlock : public IDisposable
		{
		protected:
			void Dispose(bool disposing);

		public:
			EventHandler Disposing;

			StateBlock();
			StateBlock(GraphicsDevice graphiceDevice);
			StateBlock(const StateBlock &obj);

			void Apply();
			void Capture();
			void Dispose();
			bool Equals(StateBlock other);
			int GetHashCode();

			bool operator!=(const StateBlock other);
			bool operator==(const StateBlock other);
		};
	}
}

#endif //_XFX_GRAPHICS_STATEBLOCK_
