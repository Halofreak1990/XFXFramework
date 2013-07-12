/*****************************************************************************
 *	GraphicsDevice.h														 *
 *																			 *
 *	XFX::Graphics::GraphicsDevice class definition file 					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_GRAPHICSDEVICE_
#define _XFX_GRAPHICS_GRAPHICSDEVICE_

#include "Color.h"
#include "DisplayMode.h"
#include "Enums.h"
#include "GraphicsAdapter.h"
#include "IndexBuffer.h"
#include "PresentationParameters.h"
#include "RenderTarget2D.h"
#include "TextureCollection.h"
#include "VertexBuffer.h"
#include "Viewport.h"

namespace XFX
{
	struct Matrix;
	struct Quaternion;
	struct Rectangle;
	struct Vector2;
	struct Vector4;
	
	namespace Graphics
	{
		/**
		 * Performs primitive-based rendering, creates resources, handles system-level variables, adjusts gamma ramp levels, and creates shaders.
		 */
		class GraphicsDevice : public IDisposable, public Object
		{
		private:
			IndexBuffer* _indices;
			GraphicsAdapter* _adapter;
			bool isDisposed;
			PresentationParameters* p_cachedParameters;
			TextureCollection textures;
			Color clearColor;
			Viewport viewport;

			void setPresentationParameters(PresentationParameters* presentationParameters);
			
		protected:
			virtual void Dispose(bool disposing);
			virtual void raise_DeviceLost(Object* sender, EventArgs* e);
			virtual void raise_DeviceReset(Object* sender, EventArgs* e);
			virtual void raise_DeviceResetting(Object* sender, EventArgs* e);
			virtual void raise_Disposing(Object* sender, EventArgs* e);
		
		public:
			EventHandler DeviceLost;
			EventHandler DeviceReset;
			EventHandler DeviceResetting;
			EventHandler Disposing;

			PresentationParameters* getPresentationParameters() const;
			TextureCollection getTextures() const;
			Viewport getViewport() const;
			void setViewport(const Viewport value);
		
			GraphicsDevice(GraphicsAdapter * const adapter, PresentationParameters * const presentationParameters);
			virtual ~GraphicsDevice();
			
			void Clear(const Color color);
			void Clear(const ClearOptions_t options, const Color color, const float depth, const int stencil);
			void Clear(const ClearOptions_t options, const Vector4 color, const float depth, const int stencil);
			void Dispose();
			void DrawIndexedPrimitives(const PrimitiveType_t primitiveType, const int baseVertex, const int minVertexIndex, int numVertices, int startIndex, int primitiveCount);
			void DrawInstancedPrimitives(const PrimitiveType_t primitiveType, const int baseVertex, const int minVertexIndex, int numVertices, int startIndex, int primitiveCount);
			void DrawPrimitives(const PrimitiveType_t primitiveType, const int startVertex, const int primitiveCount);
			template <class T>
			void DrawUserIndexedPrimitives(const PrimitiveType_t primitiveType, T vertexData[], int vertexOffset, int numVertices, int indexData[], int indexOffset, int primitiveCount);
			template <class T>
			void DrawUserIndexedPrimitives(const PrimitiveType_t primitiveType, T vertexData[], int vertexOffset, int numVertices, int indexData[], int indexOffset, int primitiveCount, VertexDeclaration vertexDeclaration);
			template <class T>
			void DrawUserIndexedPrimitives(const PrimitiveType_t primitiveType, T vertexData[], int vertexOffset, int numVertices, short indexData[], int indexOffset, int primitiveCount);
			template <class T>
			void DrawUserIndexedPrimitives(const PrimitiveType_t primitiveType, T vertexData[], int vertexOffset, int numVertices, short indexData[], int indexOffset, int primitiveCount, VertexDeclaration vertexDeclaration);
			template <class T>
			void DrawUserPrimitives(const PrimitiveType_t primitiveType, T vertexData[], int vertexOffset, int primitiveCount);
			template <class T>
			void DrawUserPrimitives(const PrimitiveType_t primitiveType, T vertexData[], int vertexOffset, int primitiveCount, VertexDeclaration vertexDeclaration);
			template <typename T>
			void GetBackBufferData(T data[], const int startIndex, const int elementCount);
			static const Type& GetType();
			void Present();
			void Reset();
			void Reset(PresentationParameters * const presentationParameters);
			void SetRenderTarget(RenderTarget2D * const renderTarget);
		};
	}
}

#endif //_XFX_GRAPHICS_GRAPHICSDEVICE_
