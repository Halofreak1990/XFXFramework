/********************************************************
 *	GraphicsDevice.h									*
 *														*
 *	XFX GraphicsDevice definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_GRAPHICSDEVICE_
#define _XFX_GRAPHICS_GRAPHICSDEVICE_

#include "Color.h"
#include "DepthStencilBuffer.h"
#include "Enums.h"
#include "GraphicsAdapter.h"
#include "PresentationParameters.h"
#include "RenderTarget2D.h"
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
		class DepthStencilBuffer;
		class GammaRamp;
		
		// Performs primitive-based rendering, creates resources, handles system-level variables, adjusts gamma ramp levels, and creates shaders.
		class GraphicsDevice : public IDisposable, virtual Object
		{
		private:
			GraphicsAdapter* _adapter;
			DepthStencilBuffer _depthStencilBuffer;
			DeviceType_t _deviceType;
			bool isDisposed;
			PresentationParameters* p_cachedParameters;
			TextureCollection textures;
			Color clearColor;
			Viewport viewport;

			void setPresentationParameters(PresentationParameters* presentationParameters);
			
		protected:
			virtual void Dispose(bool disposing);
			virtual void raise_DeviceLost(Object* sender, EventArgs e);
			virtual void raise_DeviceReset(Object* sender, EventArgs e);
			virtual void raise_DeviceResetting(Object* sender, EventArgs e);
			virtual void raise_Disposing(Object* sender, EventArgs e);
		
		public:
			EventHandler DeviceLost;
			EventHandler DeviceReset;
			EventHandler DeviceResetting;
			EventHandler Disposing;

			DepthStencilBuffer getDepthStencilBuffer();
			void setDepthStencilBuffer(DepthStencilBuffer buffer);
			PresentationParameters* getPresentationParameters();
			TextureCollection getTextures();
			Viewport getViewport() const;
			void setViewport(const Viewport value);
		
			GraphicsDevice(GraphicsAdapter* adapter, const DeviceType_t deviceType, PresentationParameters* presentationParameters);
			virtual ~GraphicsDevice();
			
			void Clear(const Color color);
			void Clear(const ClearOptions_t options, const Color color, const float depth, const int stencil);
			void Clear(const ClearOptions_t options, const Vector4 color, const float depth, const int stencil);
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
			GammaRamp* GetGammaRamp();
			bool* GetPixelShaderBooleanConstant(int startRegister, int constantCount);
			int* GetPixelShaderInt32Constant(int startRegister, int constantCount);
			Matrix* GetPixelShaderMatrixArrayConstant(int startRegister, int constantCount);
			Matrix GetPixelShaderMatrixConstant(int startRegister);
			Quaternion* GetPixelShaderQuaternionArrayConstant(int startRegister, int constantCount);
			Quaternion GetPixelShaderQuaternionConstant(int startRegister);
			float* GetPixelShaderSingleConstant(int startRegister, int constantCount);
			Vector2* GetPixelShaderVector2ArrayConstant(int startRegister, int constantCount);
			Vector2 GetPixelShaderVector2Constant(int startRegister);
			void Present();
			void Reset();
			void Reset(PresentationParameters* presentationParameters);
			void SetGammaRamp(const bool calibrate, GammaRamp* ramp);
			void SetRenderTarget(RenderTarget2D* renderTarget);
			void SetVertexShaderConstant(const int startRegister, const Matrix constantData);
			void SetVertexShaderConstant(const int startRegister, const Vector4 constantData);
		};
	}
}

#endif //_XFX_GRAPHICS_GRAPHICSDEVICE_
