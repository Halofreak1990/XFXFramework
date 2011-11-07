/********************************************************
 *	Game.h												*
 *														*
 *	XFX Game class definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GAME_
#define _XFX_GAME_

#include <System/Delegates.h>
#include <System/Object.h>
#include <System/Types.h>

#include "Content/ContentManager.h"
#include "GameComponentCollection.h"
#include "GameServiceContainer.h"
#include "GameTime.h"
#include "Graphics/IGraphicsDeviceService.h"
#include "Interfaces.h"

using namespace System;
using namespace XFX::Content;
using namespace XFX::Graphics;

namespace XFX
{
	// Provides basic graphics device initialization, game logic, and rendering code.
	class Game : public IDisposable, virtual Object
	{
	private:
		bool exiting;
		bool inRun;
		bool isActive;

		GameComponentCollection components;
		List<IDrawable*> currentlyDrawingComponents;
		List<IUpdateable*> currentlyUpdatingComponents;
		List<IDrawable*> drawableComponents;
		List<IUpdateable*> enabledUpdateable;
		List<IGameComponent*> notYetInitialized;
		GameServiceContainer services;
		bool disposed;
		GameTime gameTime;
		TimeSpan inactiveSleepTime;
		static const TimeSpan maximumElapsedTime;
		IGraphicsDeviceManager* graphicsManager;
		IGraphicsDeviceService* graphicsService; 

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
		virtual void OnActivated(Object* sender, EventArgs args);
		virtual void OnDeactivated(Object* sender, EventArgs args);
		virtual void OnExiting(Object* sender, EventArgs args);
		virtual void UnloadContent();
		virtual void Update(GameTime gameTime);

	public:
		GameComponentCollection Components();
		//ContentManager Content;
		GraphicsDevice getGraphicsDevice();
		GameServiceContainer getServices();
		bool IsActive();

		bool IsFixedTimeStep;
		bool IsMouseVisible;
		TimeSpan TargetElapsedTime;

		EventHandler Activated;
		EventHandler Deactivated;
		EventHandler Disposed;
		EventHandler Exiting; 

		Game();
		virtual ~Game();

		void Dispose();
		void Exit();
		void ResetElapsedTime();
		virtual void Run();
		void SuppressDraw();
		void Tick();
	};
	
	// Base class for all XNA Framework game components.
	class GameComponent : public IGameComponent, public IUpdateable, public IDisposable, virtual Object
	{
	private:
		Game _game;
		bool _disposed;
		bool _enabled;
		int _updateOrder;
		
	protected:
		virtual void Dispose(bool disposing);
		virtual ~GameComponent();

		virtual void OnEnabledChanged(Object* sender, EventArgs args);
		virtual void OnUpdateOrderChanged(Object* sender, EventArgs args);
		
	public:
		bool Enabled();
		void Enabled(bool value);
		int UpdateOrder();
		void UpdateOrder(int value);
		Game getGame();

		EventHandler EnabledChanged;
		EventHandler UpdateOrderChanged;
		EventHandler Disposed;
		
		GameComponent(Game game);
		GameComponent();
		
		virtual void Dispose();
		virtual void Initialize();
		virtual void Update(GameTime gameTime);
	};
	
	// A game component that is notified when it needs to draw itself.
	class DrawableGameComponent : public GameComponent, public IDrawable, virtual Object
	{
	private:
		int _drawOrder;
		bool _visible;
		IGraphicsDeviceService* _graphicsService;
    
    protected:
    	void Dispose(bool disposing);
    	virtual void LoadContent();
		virtual void OnDrawOrderChanged(Object* sender, EventArgs args);
		virtual void OnVisibleChanged(Object* sender, EventArgs args);
    	virtual void UnloadContent();
    
    public:
    	int DrawOrder(); 
		void DrawOrder(int value);
    	GraphicsDevice getGraphicsDevice();
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
