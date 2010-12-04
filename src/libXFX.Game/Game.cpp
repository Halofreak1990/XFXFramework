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

extern "C" {
#ifdef ENABLE_XBOX
#include "../libXFX/xinput.h"
#include <hal/xbox.h>
#else
#endif
}

#include <Game.h>

namespace XFX
{
	const Int64 Game::DefaultTargetElapsedTicks = 10000000L / 60L;
	
	bool Game::IsActive()
	{
		return isActive;
	}
	
	Game::Game()
	{
		inRun = false;
		
		IsFixedTimeStep = true;

		visibleDrawable = List<IDrawable*>();
		enabledUpdateable = List<IUpdateable*>();

		components = new GameComponentCollection();
		
		services = new GameServiceContainer();

		content = new ContentManager();
		
		gameTime = GameTime(TimeSpan::Zero, TimeSpan::Zero, TimeSpan::Zero, TimeSpan::Zero);

		inactiveSleepTime = TimeSpan::FromTicks(0);
		TargetElapsedTime = TimeSpan::FromTicks(DefaultTargetElapsedTicks);

		isActive = true;
	}

	GameComponentCollection Game::Components()
	{
		return components;
	}

	GraphicsDevice Game::GraphicsDevice_()
	{
		return graphicsService.GraphicsDevice_;
	}

	GameServiceContainer Game::Services()
	{
		return services;
	}

	bool Game::BeginDraw()
	{
		return graphicsManager.BeginDraw();
	}

	void Game::Dispose()
	{
		Dispose(true);
	}

	void Game::Dispose(bool disposing)
	{
		if(disposed)
			return;

		if(disposing)
		{
			/*
			foreach (IGameComponent component in components)
			{
				IDisposable disposable = component as IDisposable;
				if (disposable != null)
					disposable.Dispose();
			}  
			*/
		}

		disposed = true;
		if(Disposed != null)
			Disposed(*this, EventArgs::Empty);
	}

	void Game::Draw(GameTime gameTime)
	{
		/*
		foreach (IDrawable drawable in visibleDrawable)
		{
			drawable.Draw(gameTime);
		}  
		*/
	}

	void Game::EndDraw()
	{
		graphicsManager.EndDraw();
	}
	
	void Game::Exit()
	{
		XSleep(1000);
		XReboot();
	}

	void Game::Initialize()
	{
		/*
		this.graphicsService = this.Services.GetService(typeof(IGraphicsDeviceService)) as IGraphicsDeviceService;
		
		foreach (IGameComponent component in components)
		{
			component.Initialize();
		}*/

		LoadContent();
	}

#if !ENABLE_XBOX
	void Game::OnActivated(void* sender, EventArgs args)
	{
		if (Activated != null)
			Activated(sender, args);
	}

	void Game::OnDeactivated(void* sender, EventArgs args)
	{
		if (Deactivated != null)
			Deactivated(sender, args);
	}
#endif
	
	void Game::OnExiting(void* sender, EventArgs args)
	{
		if (Exiting != null)
			Exiting(sender, args);
	}

	void Game::Run()
	{
		if(inRun)
			throw InvalidOperationException("Run Method called more than once"); 

		inRun = true;
		BeginRun();
			
		Initialize(); 
        
        Tick();
        
        EndRun();
	}
	
	void Game::Tick()
	{

		Update(gameTime);
		
		if(BeginDraw())
		{
			Draw(gameTime);
			EndDraw();
		}
	}

	void Game::Update(GameTime gameTime)
	{
		/*
		foreach (IUpdateable updateable in enabledUpdateable)
		{
			updateable.Update(gameTime);
		}
		*/
	}
}
