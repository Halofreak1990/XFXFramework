/********************************************************
 *	GraphicsDeviceManager.h								*
 *														*
 *	XFX GraphicsDeviceManager definition file			*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICSDEVICEMANAGER_
#define _XFX_GRAPHICSDEVICEMANAGER_

#include "Graphics/GraphicsDevice.h"
#include "Graphics/Enums.h"
#include "Graphics/IGraphicsDeviceService.h"
#include "GraphicsDeviceInformation.h"
#include "Interfaces.h"
#include <System/Interfaces.h>

using namespace System;
using namespace XFX::Graphics;

namespace XFX
{
	class Game;

	// Handles the configuration and management of the graphics device.
	class GraphicsDeviceManager : public IGraphicsDeviceService, public IDisposable, public IGraphicsDeviceManager
	{
	private:
		bool isFullScreen;
		Game* _game;
		SurfaceFormat_t backBufferFormat;
		int backBufferHeight;
		int backBufferWidth;
		GraphicsDevice* graphicsDevice;
		DepthFormat_t preferredDepthStencilFormat;

		void CreateDevice();
	
	protected:
		virtual bool CanResetDevice(const GraphicsDeviceInformation newDeviceInfo);
		virtual void Dispose(bool disposing);
		virtual void OnDeviceCreated(Object* sender, EventArgs* args);
		virtual void OnDeviceDisposing(Object* sender, EventArgs* args);
		virtual void OnDeviceReset(Object* sender, EventArgs* args);
		virtual void OnDeviceResetting(Object* sender, EventArgs* args);

	public:
		GraphicsDevice* getGraphicsDevice() const;
		bool IsFullScreen();
		float MinimumPixelShaderProfile;
		float MinimumVertexShaderProfile;
		bool PreferMultiSampling;
		SurfaceFormat_t PreferredBackBufferFormat;
		int PreferredBackBufferWidth;
		int PreferredBackBufferHeight;
		DepthFormat_t PreferredDepthStencilFormat;
		bool SynchronizeWithVerticalRetrace;

		static const int DefaultBackBufferWidth;
		static const int DefaultBackBufferHeight;
		static SurfaceFormat_t ValidAdapterFormats[];
		static SurfaceFormat_t ValidBackBufferFormats[];

		GraphicsDeviceManager(Game * const game);
		GraphicsDeviceManager(const GraphicsDeviceManager &obj);
		~GraphicsDeviceManager();

		EventHandler DeviceCreated;
		EventHandler DeviceDisposing;
		EventHandler DeviceReset;
		EventHandler DeviceResetting;
		EventHandler Disposed;
		
		void ApplyChanges();
		bool BeginDraw();
		void Dispose();
		void EndDraw();
		static int GetType();
		void ToggleFullscreen();
	};
}

#endif //_XFX_GRAPHICSDEVICEMANAGER_
