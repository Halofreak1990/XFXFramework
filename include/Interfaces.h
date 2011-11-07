/********************************************************
 *	Interfaces.h										*
 *														*
 *	XFX interfaces definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_INTERFACES_
#define _XFX_INTERFACES_

#include <System/Types.h>
#include <System/Delegates.h>

using namespace System;

namespace XFX
{
	class GameTime;

	// Defines the interface for a drawable game component.
	interface IDrawable
	{
	public:
		virtual int DrawOrder()=0;
		virtual bool Visible()=0;

		virtual void Draw(GameTime gameTime)=0;
		virtual ~IDrawable() {}

		EventHandler DrawOrderChanged;
		EventHandler VisibleChanged;
	};

	// Defines an interface for game components.
	interface IGameComponent
	{
	public:
		virtual void Initialize()=0;
		virtual ~IGameComponent() {}
	};

	// Defines the interface for an object that manages a Graphics.GraphicsDevice.
	interface IGraphicsDeviceManager
	{
	public:
		virtual bool BeginDraw()=0;
		virtual void CreateDevice()=0;
		virtual void EndDraw()=0;

		virtual ~IGraphicsDeviceManager() {}
	};

	// Defines an interface for a game component that should be updated in Game.Update.
	interface IUpdateable
	{
	public:
		virtual bool Enabled()=0;
		virtual void Enabled(int value)=0;
		virtual int UpdateOrder()=0;
		virtual void UpdateOrder(int value)=0;

		virtual ~IUpdateable() {}
		virtual void Update(GameTime gameTime)=0;

		EventHandler EnabledChanged;
		EventHandler UpdateOrderChanged;
	};
}

#endif //_XFX_INTERFACES_
