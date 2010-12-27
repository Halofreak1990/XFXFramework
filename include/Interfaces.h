/********************************************************
 *	Interfaces.h										*
 *														*
 *	XFX interfaces definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_INTERFACES_
#define _XFX_INTERFACES_

#include <System/Types.h>

namespace XFX
{
	class GameTime;

	/// <summary>
	/// Defines the interface for a drawable game component.
	/// </summary>
	interface IDrawable
	{
	public:
		virtual int DrawOrder()=0;
		virtual bool Visible()=0;

		virtual void Draw(GameTime gameTime)=0;
		virtual ~IDrawable();

		EventHandler DrawOrderChanged;
		EventHandler VisibleChanged;
	};

	/// <summary>
	/// Defines an interface for game components.
	/// </summary>
	interface IGameComponent
	{
	public:
		virtual void Initialize()=0;
		virtual ~IGameComponent();
	};

	/// <summary>
	/// Defines the interface for an object that manages a Graphics.GraphicsDevice.
	/// </summary>
	interface IGraphicsDeviceManager
	{
	public:
		virtual bool BeginDraw()=0;
		virtual void CreateDevice()=0;
		virtual void EndDraw()=0;

		virtual ~IGraphicsDeviceManager();
	};

	/// <summary>
	/// Defines an interface for a game component that should be updated in Game.Update.
	/// </summary>
	interface IUpdateable
	{
	public:
		virtual bool Enabled()=0;
		virtual void Enabled(int value)=0;
		virtual int UpdateOrder()=0;
		virtual void UpdateOrder(int value)=0;

		virtual ~IUpdateable();
		virtual void Update(GameTime gameTime)=0;

		EventHandler EnabledChanged;
		EventHandler UpdateOrderChanged;
	};
}

#endif //_XFX_INTERFACES_
