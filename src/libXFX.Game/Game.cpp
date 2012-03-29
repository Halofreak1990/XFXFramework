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

#if ENABLE_XBOX
extern "C"
{
#include <hal/input.h>
#include <hal/xbox.h>
#include "../libXFX/pbKit.h"
}
#endif

#include <Game.h>
#include <System/Collections/Generic/List.h>
//#include <Graphics/Color.h>
#include <Graphics/DepthStencilBuffer.h>
#include <Graphics/GraphicsDevice.h>

#include <sassert.h>

namespace XFX
{
	const Int64 Game::DefaultTargetElapsedTicks = 10000000L / 60L;
	const TimeSpan Game::maximumElapsedTime = TimeSpan::FromMilliseconds(500.0);
	
	bool Game::IsActive()
	{
		return isActive;
	}
	
	Game::Game()
	{
		inRun = false;
		
		IsFixedTimeStep = true;

		//content = ContentManager(services);
		
		gameTime = GameTime(TimeSpan::Zero, TimeSpan::Zero, TimeSpan::Zero, TimeSpan::Zero);

		TargetElapsedTime = TimeSpan::FromTicks(0x28b0bL);
		inactiveSleepTime = TimeSpan::FromMilliseconds(20.0);

		isActive = true;
	}

	Game::~Game()
	{

	}

	GameComponentCollection Game::Components()
	{
		return components;
	}

	GraphicsDevice* Game::getGraphicsDevice()
	{
		return graphicsService->getGraphicsDevice();
	}

	GameServiceContainer Game::getServices()
	{
		return services;
	}

	void Game::BeginRun()
	{
	}

	bool Game::BeginDraw()
	{
		if (IsFixedTimeStep && gameTime.IsRunningSlowly())
            return false;

		return graphicsManager->BeginDraw();
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
			for (int i = 0; i < components.Count(); i++)
			{
				IDisposable* disposable = dynamic_cast<IDisposable*>(components[i]);
				if (disposable)
					disposable->Dispose();
			}
		}

		disposed = true;
		if(Disposed != null)
			Disposed(this, EventArgs::Empty);
	}

	void Game::Draw(GameTime gameTime)
	{
		/*for (int i = 0; i < drawableComponents.Count(); i++)
		{
			currentlyDrawingComponents.Add(drawableComponents[i]);
		}
		for (int j = 0; j < currentlyDrawingComponents.Count(); j++)
		{
			IDrawable* drawable = currentlyDrawingComponents[j];
			if (drawable->Visible())
			{
				drawable->Draw(gameTime);
			}
		}
		currentlyDrawingComponents.Clear();*/
	}

	void Game::EndDraw()
	{
		if(graphicsManager)
			graphicsManager->EndDraw();
	}

	void Game::EndRun()
	{
	}
	
	void Game::Exit()
	{
		XSleep(1000);
		XReboot();
	}

	void Game::Initialize()
	{
		graphicsService = dynamic_cast<IGraphicsDeviceService*>(services.GetService("IGraphicsDeviceService"));

		for (int i = 0; i < components.Count(); i++)
		{
			components[i]->Initialize();
		}

		XInput_Init();

		LoadContent();
	}

	void Game::LoadContent()
	{
	}

	void Game::OnActivated(Object* sender, EventArgs args)
	{
		if (Activated)
			Activated(sender, args);
	}

	void Game::OnDeactivated(Object* sender, EventArgs args)
	{
		if (Deactivated)
			Deactivated(sender, args);
	}
	
	void Game::OnExiting(Object* sender, EventArgs args)
	{
		if (Exiting)
			Exiting(sender, args);
	}

	void Game::Run()
	{
		sassert(!inRun, "Run Method called more than once.");

		inRun = true;
		BeginRun();
			
		graphicsManager = dynamic_cast<IGraphicsDeviceManager*>(services.GetService("IGraphicsDeviceManager"));
		if (graphicsManager != null)
			graphicsManager->CreateDevice();

		Initialize(); 
        
		while(1)
			Tick();
        
        EndRun();
		inRun = false;
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

	void Game::UnloadContent()
	{
	}

	void Game::Update(GameTime gameTime)
	{
		/*for (int i = 0; i < this.updateableComponents.Count; i++)
		{
			currentlyUpdatingComponents.Add(updateableComponents[i]);
		}
		for (int j = 0; j < currentlyUpdatingComponents.Count(); j++)
		{
			IUpdateable* updateable = currentlyUpdatingComponents[j];
			if (updateable->Enabled())
			{
				updateable->Update(gameTime);
			}
		}
		currentlyUpdatingComponents.Clear();*/
	}
}
