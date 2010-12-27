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
#include "../libXFX/pbKit.h"

namespace XFX
{
	const int GraphicsDeviceManager::DefaultBackBufferWidth = 640;
	const int GraphicsDeviceManager::DefaultBackBufferHeight = 480;
	const DeviceType_t GraphicsDeviceManager::ValidDeviceTypes[] = { DeviceType::Hardware };
	SurfaceFormat_t GraphicsDeviceManager::ValidAdapterFormats[] = { SurfaceFormat::Bgr32, SurfaceFormat::Bgr555, SurfaceFormat::Bgr565, SurfaceFormat::Bgra1010102 };
	SurfaceFormat_t GraphicsDeviceManager::ValidBackBufferFormats[] = { SurfaceFormat::Bgr565, SurfaceFormat::Bgr555, SurfaceFormat::Bgra5551, SurfaceFormat::Bgr32, SurfaceFormat::Color, SurfaceFormat::Bgra1010102 };
	
	GraphicsDevice GraphicsDeviceManager::GraphicsDevice_()
	{
		return graphicsDevice;
	}
	
	bool IsFullScreen()
	{
		return true;
	}
	
	void GraphicsDeviceManager::ApplyChanges()
	{
		
	}

	bool GraphicsDeviceManager::CanResetDevice(GraphicsDeviceInformation newDeviceInfo)
	{
		if (graphicsDevice.CreationParameters().DeviceType_() != newDeviceInfo.DeviceType_)
        {
            return false;
        }
        return true;
	}

	GraphicsDeviceManager::GraphicsDeviceManager(Game game)
	{
		_game = game;
        /*	
		if (game.Services().GetService((Object*)IGraphicsDeviceManager) != null)
            throw ArgumentException("A graphics device manager is already registered.  The graphics device manager cannot be changed once it is set.");*/

        game.Services().AddService((Object*)this);
        game.Services().AddService((Object*)this);
	}

	GraphicsDeviceInformation GraphicsDeviceManager::FindBestDevice(bool anySuitableDevice)
	{
		GraphicsDeviceInformation result;
		
		return result;
	}

	void GraphicsDeviceManager::OnDeviceCreated(Object* sender, EventArgs args)
	{
		if (DeviceCreated != null)
			DeviceCreated(sender, args);
	}

	void GraphicsDeviceManager::OnDeviceDisposing(Object* sender, EventArgs args)
	{
		if (DeviceDisposing != null)
			DeviceDisposing(sender, args);
	}

	void GraphicsDeviceManager::OnDeviceReset(Object* sender, EventArgs args)
	{
		if (DeviceReset != null)
			DeviceReset(sender, args);
	}

	void GraphicsDeviceManager::OnDeviceResetting(Object* sender, EventArgs args)
	{
		if (DeviceResetting != null)
			DeviceResetting(sender, args);
	}

	void GraphicsDeviceManager::RankDevices(List<GraphicsDeviceInformation> foundDevices)
	{
		int index = 0;
        while (index < foundDevices.Count())
        {
            DeviceType_t deviceType = foundDevices[index].DeviceType_;
            GraphicsAdapter adapter = foundDevices[index].Adapter;
            PresentationParameters presentationParameters = foundDevices[index].PresentationParameters_;
			if (!adapter.CheckDeviceFormat(deviceType, adapter.CurrentDisplayMode().Format, TextureUsage::None, QueryUsages::PostPixelShaderRendering, ResourceType::Texture2D, presentationParameters.BackBufferFormat))
            {
                foundDevices.RemoveAt(index);
            }
            else
            {
                index++;
            }
		}
	}

	void GraphicsDeviceManager::ToggleFullscreen()
	{

	}

	bool IGraphicsDeviceManager::BeginDraw()
	{
		return true;
	}

	void IGraphicsDeviceManager::EndDraw()
	{
		
	}
}
