// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <GraphicsDeviceManager.h>
#include <Game.h>
#include <System/Event.h>

#include <sassert.h>

#if DEBUG
extern "C"
{
#include <openxdk/debug.h>
}
#endif

namespace XFX
{
	const int GraphicsDeviceManager::DefaultBackBufferWidth = 640;
	const int GraphicsDeviceManager::DefaultBackBufferHeight = 480;
	SurfaceFormat_t GraphicsDeviceManager::ValidAdapterFormats[] = { SurfaceFormat::Bgr565 }; // TODO figure out which ones are really supported
	SurfaceFormat_t GraphicsDeviceManager::ValidBackBufferFormats[] = { SurfaceFormat::Bgr565, SurfaceFormat::Bgra5551, SurfaceFormat::Color }; // idem

	GraphicsDeviceManager::GraphicsDeviceManager(Game * const game)
		: _game(game), backBufferFormat(SurfaceFormat::Color), backBufferHeight(DefaultBackBufferHeight), backBufferWidth(DefaultBackBufferWidth)
	{
		SynchronizeWithVerticalRetrace = true;
		preferredDepthStencilFormat = DepthFormat::Depth24;

		sassert(game->getServices().GetService("IGraphicsDeviceManager") == null, "A graphics device manager is already registered. The graphics device manager cannot be changed once it is set.");

#if DEBUG
		debugPrint("Registering GraphicsDeviceManager\n");
#endif
        game->getServices().AddService("IGraphicsDeviceManager", this);
		game->getServices().AddService("IGraphicsDeviceService", this);
	}

	GraphicsDeviceManager::GraphicsDeviceManager(const GraphicsDeviceManager &obj)
		: _game(obj._game), backBufferFormat(obj.backBufferFormat), backBufferHeight(obj.backBufferHeight), backBufferWidth(obj.backBufferWidth)
	{
	}

	GraphicsDeviceManager::~GraphicsDeviceManager()
	{
		// TODO: implement
	}

	GraphicsDevice* GraphicsDeviceManager::getGraphicsDevice() const
	{
		return graphicsDevice;
	}
	
	bool GraphicsDeviceManager::IsFullScreen()
	{
		return isFullScreen;
	}
	
	void GraphicsDeviceManager::ApplyChanges()
	{
		
	}

	bool GraphicsDeviceManager::BeginDraw()
	{
		return true;
	}

	bool GraphicsDeviceManager::CanResetDevice(const GraphicsDeviceInformation newDeviceInfo)
	{
		/*if (graphicsDevice->getDeviceType() != newDeviceInfo.DeviceType_)
        {
            return false;
        }*/
        return true;
	}

	void GraphicsDeviceManager::CreateDevice()
	{
#if DEBUG
		debugPrint("Creating GraphicsDevice\n");
#endif

		PresentationParameters* p = new PresentationParameters();
		p->BackBufferWidth = backBufferWidth;
		p->BackBufferHeight = backBufferHeight;
		p->BackBufferFormat = backBufferFormat;
		p->IsFullScreen = true;

		// TODO: properly construct the GraphicsDevice- requires lots of additional coding in multiple places
		graphicsDevice = new GraphicsDevice(null, p);

		graphicsDevice->Disposing += new EventHandler::T<GraphicsDeviceManager>(this, &GraphicsDeviceManager::OnDeviceDisposing);
		graphicsDevice->DeviceResetting += new EventHandler::T<GraphicsDeviceManager>(this, &GraphicsDeviceManager::OnDeviceResetting);
		graphicsDevice->DeviceReset += new EventHandler::T<GraphicsDeviceManager>(this, &GraphicsDeviceManager::OnDeviceReset);

		OnDeviceCreated(this, const_cast<EventArgs*>(EventArgs::Empty));
	}

	void GraphicsDeviceManager::Dispose()
	{
		Dispose(true);
		delete graphicsDevice;
	}

	void GraphicsDeviceManager::Dispose(bool disposing)
	{
		if (disposing)
		{
			graphicsDevice->Dispose();
		}
	}

	void GraphicsDeviceManager::EndDraw()
	{
		graphicsDevice->Present();
	}

	int GraphicsDeviceManager::GetType() const
	{
	}

	void GraphicsDeviceManager::OnDeviceCreated(Object* sender, EventArgs* args)
	{
		DeviceCreated(sender, args);
	}

	void GraphicsDeviceManager::OnDeviceDisposing(Object* sender, EventArgs* args)
	{
		DeviceDisposing(sender, args);
	}

	void GraphicsDeviceManager::OnDeviceReset(Object* sender, EventArgs* args)
	{
		DeviceReset(sender, args);
	}

	void GraphicsDeviceManager::OnDeviceResetting(Object* sender, EventArgs* args)
	{
		DeviceResetting(sender, args);
	}

	void GraphicsDeviceManager::ToggleFullscreen()
	{
		isFullScreen = !isFullScreen;
		PresentationParameters* p = graphicsDevice->getPresentationParameters();
		p->IsFullScreen = isFullScreen;
		graphicsDevice->Reset(p);
	}
}
