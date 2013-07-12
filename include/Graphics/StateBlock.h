/*****************************************************************************
 *	StateBlock.h															 *
 *																			 *
 *	XFX::Graphics::StateBlock definition file								 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
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

			StateBlock(GraphicsDevice * const graphiceDevice);
			StateBlock(const StateBlock &obj);
			virtual ~StateBlock() { delete device; }

			void Apply();
			void Capture();
			void Dispose();
			bool Equals(Object const * const obj) const;
			int GetHashCode() const;
			static const Type& GetType();
			const String ToString() const;

			bool operator!=(const StateBlock& right) const;
			bool operator==(const StateBlock& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_STATEBLOCK_
