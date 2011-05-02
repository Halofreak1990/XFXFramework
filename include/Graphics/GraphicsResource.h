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
#include "GraphicsDevice.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Queries and prepares resources.
		/// </summary>
		class GraphicsResource : public IDisposable, virtual Object
		{
		private:
			bool isDisposed; 
            char* name;  
            ResourceType_t resourceType; 
		
		protected:
			GraphicsDevice* graphicsDevice;
			
			virtual void Dispose(bool disposing)=0;
			
		public:
			virtual GraphicsDevice* GraphicsDevice_();
			bool IsDisposed();
			char* Name();
			void Name(char* value);
			int Priority;
			virtual ResourceType_t ResourceType_();

			EventHandler Disposing;
			
			virtual ~GraphicsResource();
			GraphicsResource();

			void Dispose();
		};
	}
}

#endif //_XFX_GRAPHICS_GRAPHICSRESOURCE_
