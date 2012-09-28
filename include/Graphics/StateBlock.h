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
		class StateBlock : public IDisposable, public Object
		{
		private:
			GraphicsDevice* device;

		protected:
			void Dispose(bool disposing);

		public:
			EventHandler Disposing;

			StateBlock(GraphicsDevice* graphiceDevice);
			StateBlock(const StateBlock &obj);
			virtual ~StateBlock() { delete device; }

			void Apply();
			void Capture();
			void Dispose();
			bool Equals(const Object* obj) const;
			int GetHashCode() const;
			int GetType() const;
			const char* ToString() const;

			bool operator!=(const StateBlock& right) const;
			bool operator==(const StateBlock& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_STATEBLOCK_
