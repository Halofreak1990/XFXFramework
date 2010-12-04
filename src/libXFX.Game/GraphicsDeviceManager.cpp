// Copyright (C) 2010-2012, XFX Team
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
#include "PBKit/pbKit.h"

namespace XFX
{
#if ENABLE_XBOX
	const int GraphicsDeviceManager::DefaultBackBufferWidth = 640;
	const int GraphicsDeviceManager::DefaultBackBufferHeight = 480;
	const DeviceType_t GraphicsDeviceManager::ValidDeviceTypes[] = { DeviceType::Hardware };
#else
	const int GraphicsDeviceManager::DefaultBackBufferWidth = 800;
	const int GraphicsDeviceManager::DefaultBackBufferHeight = 600;	
#endif
	
	GraphicsDevice GraphicsDeviceManager::GraphicsDevice_()
	{
		return graphicsDevice;
	}
	
	bool IsFullScreen()
	{
#if ENABLE_XBOX //On the XBOX we always run Fullscreen
		return true;
#else
		return isFullScreen;
#endif
	}
	
	void GraphicsDeviceManager::ApplyChanges()
	{
		
	}

	void IGraphicsDeviceManager::CreateDevice()
	{
		
	}

	GraphicsDeviceManager::GraphicsDeviceManager(Game game)
	{
		_game = game;
        if (game.Services().GetService(typeof(IGraphicsDeviceManager)) != null)
        {
            throw ArgumentException("A graphics device manager is already registered.  The graphics device manager cannot be changed once it is set.");
        }
        game.Services().AddService(typeof(IGraphicsDeviceManager), this);
        game.Services().AddService(typeof(IGraphicsDeviceService), this);
#if !ENABLE_XBOX
        game.Window.ClientSizeChanged += new EventHandler(this.GameWindowClientSizeChanged);
        game.Window.ScreenDeviceNameChanged += new EventHandler(this.GameWindowScreenDeviceNameChanged);
#endif
	}

	void GraphicsDeviceManager::ToggleFullscreen()
	{
#if !ENABLE_XBOX
		isFullScreen != isFullScreen;
		//graphicsDevice.PresentationParameters.
#endif
	}

	bool IGraphicsDeviceManager::BeginDraw()
	{
		return true;
	}
}
