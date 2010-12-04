/********************************************************
 *	GraphicsDeviceManager.h								*
 *														*
 *	XFX GraphicsDeviceManager definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICSDEVICEMANAGER_
#define _XFX_GRAPHICSDEVICEMANAGER_

#include "Game.h"
#include "Graphics/GraphicsDevice.h"
#include "GraphicsDeviceInformation.h"
#include "Interfaces.h"
#include "Graphics/IGraphicsDeviceService.h"
#include "Graphics/Enums.h"
#include "System/Interfaces.h"

using namespace System;
using namespace XFX::Graphics;

namespace XFX
{
	class GraphicsDeviceManager : public IGraphicsDeviceService, public IDisposable, public IGraphicsDeviceManager
	{
	private:
		bool isFullScreen;
		Game _game;
		GraphicsDevice graphicsDevice;
	
	protected:
		virtual void Dispose(int disposing);
		virtual int CanResetDevice(GraphicsDeviceInformation newDeviceInfo);

	public:
		GraphicsDevice GraphicsDevice_();
		bool IsFullScreen();
		float MinimumPixelShaderProfile;
		float MinimumVertexShaderProfile;
		int PreferMultiSampling;
		SurfaceFormat_t PreferredBackBufferFormat;
		int PreferredBackBufferWidth;
		int PreferredBackBufferHeight;
		DepthFormat_t PreferredDepthStencilFormat;
		int SynchronizeWithVerticalRetrace;

		static const int DefaultBackBufferWidth;
		static const int DefaultBackBufferHeight;
		static SurfaceFormat_t ValidAdapterFormats[];
		static SurfaceFormat_t ValidBackBufferFormats[];
		static const DeviceType_t ValidDeviceTypes[];

		GraphicsDeviceManager(Game game);
		
		void ApplyChanges();
		void Dispose();
		void ToggleFullscreen();
	};
}

#endif //_XFX_GRAPHICSDEVICEMANAGER_
