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

#include <Graphics/Color.h>
#include <Graphics/GraphicsDevice.h>
#include <Game.h>

namespace XFX
{
	GraphicsDevice* DrawableGameComponent::getGraphicsDevice() const
	{
		return _graphicsService->getGraphicsDevice();
	}
	
	DrawableGameComponent::DrawableGameComponent(Game * const game)
		: GameComponent(game), _visible(true)
	{
	}
	
	void DrawableGameComponent::Dispose(bool disposing)
	{
		if(disposing)
		{
			UnloadContent();
		}
		GameComponent::Dispose();
	}

	int DrawableGameComponent::getDrawOrder() const
	{
		return _drawOrder;
	}

	void DrawableGameComponent::setDrawOrder(const int value)
	{
		if (_drawOrder != value)
		{
			_drawOrder = value;  
			OnDrawOrderChanged(this, EventArgs::Empty);
		}  
	}
	
	void DrawableGameComponent::Initialize()
	{
		LoadContent();
	}

	void DrawableGameComponent::OnDrawOrderChanged(Object* sender, EventArgs* args)
	{
		DrawOrderChanged(sender, args);
	}

	void DrawableGameComponent::OnVisibleChanged(Object* sender, EventArgs* args)
	{
		VisibleChanged(sender, args);
	}
	
	void DrawableGameComponent::Update(GameTime gameTime) 
	{
		if(getEnabled())
		{
		}
		
		GameComponent::Update(gameTime);
	}

	bool DrawableGameComponent::getVisible() const
	{
		return _visible;
	}

	void DrawableGameComponent::setVisible(const bool value)
	{
		if (_visible != value)
		{
			_visible = value;
			OnVisibleChanged(this, EventArgs::Empty);
		}
	}
}
