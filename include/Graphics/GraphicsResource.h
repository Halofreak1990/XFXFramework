/*****************************************************************************
 *	GraphicsResource.h  													 *
 *																			 *
 *	XFX GraphicsResource definition file									 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_GRAPHICSRESOURCE_
#define _XFX_GRAPHICS_GRAPHICSRESOURCE_

#include <System/Event.h>
#include <System/String.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		class GraphicsDevice;

		/**
		 * Queries and prepares resources.
		 */
		class GraphicsResource : public IDisposable, public Object
		{
		private:
			bool isDisposed;
		
		protected:
			GraphicsDevice* graphicsDevice;
			
			virtual void Dispose(bool disposing);
			
		public:
			virtual GraphicsDevice* getGraphicsDevice();
			bool IsDisposed();
			String Name;
			Object* Tag;

			EventHandler Disposing;
			
			virtual ~GraphicsResource();
			GraphicsResource();

			void Dispose();
			static const Type& GetType();
		};
	}
}

#endif //_XFX_GRAPHICS_GRAPHICSRESOURCE_
