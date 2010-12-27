/********************************************************
 *	GraphicsDevice.h									*
 *														*
 *	XFX GraphicsDevice definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_GRAPHICSDEVICE_
#define _XFX_GRAPHICS_GRAPHICSDEVICE_

#include <System/Types.h>
#include "Color.h"
#include "DepthStencilBuffer.h"
#include "Enums.h"
#include "GraphicsAdapter.h"
#include "GraphicsDeviceCapabilities.h"
#include "GraphicsDeviceCreationParameters.h"
#include "PresentationParameters.h"
#include "TextureCollection.h"
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
		class GammaRamp;
		
		/// <summary>
		/// Performs primitive-based rendering, creates resources, handles system-level
		/// variables, adjusts gamma ramp levels, and creates shaders.
		/// </summary>
		class GraphicsDevice : public IDisposable
		{
		private:
			GraphicsAdapter _adapter;
			DepthStencilBuffer _depthStencilBuffer;
			DeviceType_t _deviceType;
			GraphicsDeviceCapabilities graphicsDeviceCapabilities;
			bool isDisposed;
			TextureCollection textures;
			Color clearColor;
			Viewport viewport;
			
		protected:
			virtual void Dispose(bool disposing);
		
		public:
			GraphicsDeviceCreationParameters CreationParameters();
			DepthStencilBuffer GetDepthStencilBuffer();
			void SetDepthStencilBuffer(DepthStencilBuffer buffer);
			TextureCollection Textures();
			Viewport Viewport_();
			void Viewport_(Viewport newValue);
		
			GraphicsDevice(GraphicsAdapter adapter, DeviceType_t deviceType, PresentationParameters presentationParameters);
			GraphicsDevice();
			virtual ~GraphicsDevice();
			
			void Clear(Color color);
			void Clear(ClearOptions_t options, Color color, float depth, int stencil);
			void Clear(ClearOptions_t options, Vector4 color, float depth, int stencil);
			void Clear(ClearOptions_t options, Color color, float depth, int stencil, Rectangle regions[]);
			void Clear(ClearOptions_t options, Vector4 color, float depth, int stencil, Rectangle regions[]);
			void Dispose();
			void DrawIndexedPrimitives(PrimitiveType_t primitiveType, int baseVertex, int minVertexIndex, int numVertices, int startIndex, int primitiveCount);
			void DrawPrimitives(PrimitiveType primitiveType, int startVertex, int primitiveCount);
			template <class T>
			void DrawUserIndexedPrimitives(PrimitiveType_t primitiveType, T vertexData[], int vertexOffset, int numVertices, int indexData[], int indexOffset, int primitiveCount);
			template <class T>
			void DrawUserIndexedPrimitives(PrimitiveType_t primitiveType, T vertexData[], int vertexOffset, int numVertices, short indexData[], int indexOffset, int primitiveCount);
			template <class T>
			void DrawUserPrimitives(PrimitiveType_t primitiveType, T vertexData[], int vertexOffset, int primitiveCount);
			void EvictManagedResources();
			GammaRamp GetGammaRamp();
			int* GetPixelShaderBooleanConstant(int startRegister, int constantCount);
			int* GetPixelShaderInt32Constant(int startRegister, int constantCount);
			Matrix* GetPixelShaderMatrixArrayConstant(int startRegister, int constantCount);
			Matrix GetPixelShaderMatrixConstant(int startRegister);
			Quaternion* GetPixelShaderQuaternionArrayConstant(int startRegister, int constantCount);
			Quaternion GetPixelShaderQuaternionConstant(int startRegister);
			float* GetPixelShaderSingleConstant(int startRegister, int constantCount);
			Vector2* GetPixelShaderVector2ArrayConstant(int startRegister, int constantCount);
			Vector2 GetPixelShaderVector2Constant(int startRegister);
		};
	}
}

#endif //_XFX_GRAPHICS_GRAPHICSDEVICE_
