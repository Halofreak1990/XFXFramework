/********************************************************
 *	GraphicsResource.h									*
 *														*
 *	XFX GraphicsResource definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_GRAPHICSRESOURCE_
#define _XFX_GRAPHICS_GRAPHICSRESOURCE_

#include <System/Types.h>
#include <System/Delegates.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		class GraphicsDevice;

		// Queries and prepares resources.
		class GraphicsResource : public IDisposable, virtual Object
		{
		private:
			bool isDisposed; 
            char* name;  
            ResourceType_t resourceType; 
		
		protected:
			GraphicsDevice* graphicsDevice;
			
			virtual void Dispose(bool disposing);
			
		public:
			virtual GraphicsDevice* getGraphicsDevice();
			bool IsDisposed();
			char* Name;
			Object Tag;

			EventHandler Disposing;
			
			virtual ~GraphicsResource();
			GraphicsResource();

			void Dispose();
		};
	}
}

#endif //_XFX_GRAPHICS_GRAPHICSRESOURCE_
