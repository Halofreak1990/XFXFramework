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
#include "Graphics/Enums.h"
#include "Graphics/IGraphicsDeviceService.h"
#include "GraphicsDeviceInformation.h"
#include "Interfaces.h"
#include "System/Interfaces.h"

using namespace System;
using namespace XFX::Graphics;

namespace XFX
{
	// Handles the configuration and management of the graphics device.
	class GraphicsDeviceManager : public IGraphicsDeviceService, public IDisposable, public IGraphicsDeviceManager, virtual Object
	{
	private:
		bool isFullScreen;
		Game _game;
		SurfaceFormat_t backBufferFormat;
		int backBufferHeight;
		int backBufferWidth;
		GraphicsDevice graphicsDevice;
		ShaderProfile_t minimumVertexShaderProfile;

		void CreateDevice();
	
	protected:
		virtual bool CanResetDevice(GraphicsDeviceInformation newDeviceInfo);
		virtual void Dispose(bool disposing);
		virtual GraphicsDeviceInformation FindBestDevice(bool anySuitableDevice);
		virtual void OnDeviceCreated(Object* sender, EventArgs args);
		virtual void OnDeviceDisposing(Object* sender, EventArgs args);
		virtual void OnDeviceReset(Object* sender, EventArgs args);
		virtual void OnDeviceResetting(Object* sender, EventArgs args);
		virtual void RankDevices(List<GraphicsDeviceInformation> foundDevices);

	public:
		GraphicsDevice getGraphicsDevice();
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
		static const DeviceType_t ValidDeviceTypes[];

		GraphicsDeviceManager();
		GraphicsDeviceManager(Game game);

		EventHandler DeviceCreated;
		EventHandler DeviceDisposing;
		EventHandler DeviceReset;
		EventHandler DeviceResetting;
		EventHandler Disposed;
		
		void ApplyChanges();
		bool BeginDraw();
		void Dispose();
		void EndDraw();
		void ToggleFullscreen();
	};
}

#endif //_XFX_GRAPHICSDEVICEMANAGER_
