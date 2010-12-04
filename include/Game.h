/********************************************************
 *	Game.h												*
 *														*
 *	XFX Game class definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAME_
#define _XFX_GAME_

#include <System/Types.h>
#include <System/Delegates.h>

#include "Content/ContentManager.h"
#include "GameComponentCollection.h"
#include "GameServiceContainer.h"
#include "GameTime.h"
#include "Graphics/GraphicsDevice.h"
#include "Graphics/IGraphicsDeviceService.h"
#include "Interfaces.h"

using namespace System;
using namespace XFX::Content;
using namespace XFX::Graphics;

namespace XFX
{
	/// <summary>
	/// Provides basic graphics device initialization, game logic, and rendering code.
	/// </summary>
	class Game : public IDisposable
	{
	private:
		bool exiting;
		bool inRun;
		bool isActive;

		GameComponentCollection components;
		List<IDrawable*> visibleDrawable;
		List<IUpdateable*> enabledUpdateable;
		GameServiceContainer services;
		bool disposed;
		GameTime gameTime;
		TimeSpan inactiveSleepTime;
		IGraphicsDeviceManager* graphicsManager;
		IGraphicsDeviceService graphicsService; 

#if !ENABLE_XBOX
		private bool isMouseVisible;
#endif
		static const Int64 DefaultTargetElapsedTicks;

	protected:
		virtual bool BeginDraw();
		virtual void BeginRun();
		virtual void Dispose(bool disposing);
		virtual void Draw(GameTime gameTime);
		virtual void EndDraw();
		virtual void EndRun();
		void Finalize();
		virtual void LoadContent();
		virtual void Initialize();
#if !ENABLE_XBOX
		virtual void OnActivated(void* sender, EventArgs args);
		virtual void OnDeactivated(void* sender, EventArgs args);
#endif
		virtual void OnExiting(void* sender, EventArgs args);
		virtual void UnloadContent();
		virtual void Update(GameTime gameTime);

	public:
		GameComponentCollection Components();
		ContentManager Content;
		GraphicsDevice GraphicsDevice_();
		GameServiceContainer Services();
		bool IsActive();

		bool IsFixedTimeStep;
		bool IsMouseVisible;
		TimeSpan TargetElapsedTime;

#if !ENABLE_XBOX
		EventHandler Activated;
		EventHandler Deactivated;
#endif
		EventHandler Disposed;
		EventHandler Exiting; 

		void Dispose();
		void Exit();
		Game();
		void ResetElapsedTime();
		void Run();
		void SuppressDraw();
		void Tick();
	};
	
	/// <summary>
	/// Base class for all XNA Framework game components.
	/// </summary>
	class GameComponent : IGameComponent, IUpdateable, IDisposable
	{
	private:
		Game _game;
		bool _disposed;
		bool _enabled;
		int _updateOrder;
		
	protected:
		virtual void Dispose(bool disposing);
		virtual ~GameComponent();

		virtual void OnEnabledChanged(void* sender, EventArgs args);
		virtual void OnUpdateOrderChanged(void* sender, EventArgs args);
		
	public:
		bool Enabled();
		void Enabled(bool value);
		int UpdateOrder();
		void UpdateOrder(int value);
		Game Game_();

		EventHandler EnabledChanged;
		EventHandler UpdateOrderChanged;
		EventHandler Disposed;
		
		GameComponent(Game game);
		GameComponent();
		
		virtual void Dispose();
		virtual void Initialize();
		virtual void Update(GameTime gameTime);
	};
	
	/// <summary>
	/// A game component that is notified when it needs to draw itself.
	/// </summary>
	class DrawableGameComponent : GameComponent, IDrawable
	{
	private:
		int _drawOrder;
		bool _visible;
		IGraphicsDeviceService _graphicsService;
    
    protected:
    	void Dispose(bool disposing);
    	virtual void LoadContent();
		virtual void OnDrawOrderChanged(void* sender, EventArgs args);
		virtual void OnVisibleChanged(void* sender, EventArgs args);
    	virtual void UnloadContent();
    
    public:
    	int DrawOrder(); 
		void DrawOrder(int value);
    	GraphicsDevice GraphicsDevice_();
    	bool Visible();
		void Visible(bool value);

		EventHandler DrawOrderChanged;
		EventHandler VisibleChanged;
    
		DrawableGameComponent(Game game);
		virtual void Draw(GameTime gameTime);
		void Initialize();
		virtual void Update(GameTime gameTime);
	};
}

#endif //_XFX_GAME_
