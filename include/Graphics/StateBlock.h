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

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		class StateBlock : public IDisposable, virtual Object
		{
		private:
			GraphicsDevice* device;

		protected:
			void Dispose(bool disposing);

		public:
			EventHandler Disposing;

			StateBlock(GraphicsDevice* graphiceDevice);
			StateBlock(const StateBlock &obj);

			void Apply();
			void Capture();
			void Dispose();
			bool Equals(const StateBlock& obj) const;
			int GetHashCode() const;
			const char* ToString() const;

			bool operator!=(const StateBlock& right) const;
			bool operator==(const StateBlock& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_STATEBLOCK_
