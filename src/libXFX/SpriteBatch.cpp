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

extern "C"
{
#include "pbkit.h"
}
#include <Graphics/Color.h>
#include <Graphics/GraphicsDevice.h>
#include <Graphics/Sprite.h>
#include <Graphics/SpriteBatch.h>
#include <Graphics/SpriteFont.h>
#include <Graphics/Texture2D.h>
#include <MathHelper.h>
#include <Matrix.h>
#include <Rectangle.h>
#include <Vector2.h>
#include <Vector4.h>

#if DEBUG
#include <stdio.h>
#endif

using namespace XFX;

namespace XFX
{
	namespace Graphics
	{
		SpriteBatch::SpriteBatch()
		{
			device = null;
		}
		
		SpriteBatch::SpriteBatch(GraphicsDevice* graphicsDevice)
		{
			device = graphicsDevice;
		}

		SpriteBatch::~SpriteBatch()
		{
			Dispose(false);
		}

		GraphicsDevice* SpriteBatch::getGraphicsDevice()
		{
			return device;
		}
		
		bool SpriteBatch::IsDisposed()
		{
			return isDisposed;
		}
	
		void SpriteBatch::Begin() 
        { 
            Begin(SpriteBlendMode::AlphaBlend, SpriteSortMode::Deferred, SaveStateMode::None, Matrix::Identity); 
        }

		void SpriteBatch::Begin(SpriteBlendMode_t blendMode)
		{
			Begin(blendMode, SpriteSortMode::Deferred, SaveStateMode::None, Matrix::Identity);
		}
        
        void SpriteBatch::Begin(SpriteBlendMode_t blendMode, SpriteSortMode_t sortMode, SaveStateMode_t stateMode)
        {
	        Begin(blendMode, sortMode, stateMode, Matrix::Identity);
        }
        
        void SpriteBatch::Begin(SpriteBlendMode_t blendMode, SpriteSortMode_t sortMode, SaveStateMode_t stateMode, Matrix transformMatrix) 
        { 
            if (inBeginEndPair)
			{
#if DEBUG
				printf("INVALID_OPERATION in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Begin cannot be called again until End has been successfully called.");
#endif
				return;
			}
  
			if (stateMode == SaveStateMode::SaveState)
				saveState = StateBlock(device);
			spriteBlendMode = blendMode;
			spriteSortMode = sortMode;
			if (sortMode == SpriteSortMode::Immediate)
				applyGraphicsDeviceSettings();

			inBeginEndPair = true;
        }
         
        void SpriteBatch::Dispose(bool disposing)
        {
	        if (disposing && !isDisposed)
			{
				if (Disposing != null)
				{
					Disposing(this, EventArgs::Empty);
				}
			}
			isDisposed = true;
        }
         
        void SpriteBatch::Dispose()
        {
	        Dispose(true);
        }
         
        void SpriteBatch::Draw(Texture2D texture, Rectangle destinationRectangle, Color color)
        {
			Draw(texture, destinationRectangle, Rectangle::Empty, color, 0.0f, Vector2::Zero, SpriteEffects::None, 0.0f);
        }

		void SpriteBatch::Draw(Texture2D texture, Vector2 position, Color color)
        {
			Draw(texture, position, Rectangle::Empty, color);
        }
         
        void SpriteBatch::Draw(Texture2D texture, Rectangle destinationRectangle, Rectangle sourceRectangle, Color color)
        {
			Draw(texture, destinationRectangle, sourceRectangle, color, 0.0f, Vector2::Zero, SpriteEffects::None, 0.0f);
        }
        
        void SpriteBatch::Draw(Texture2D texture, Vector2 position, Rectangle sourceRectangle, Color color)
        {
			Rectangle destination = Rectangle((int)position.X, (int)position.Y, texture.getWidth(), texture.getHeight());
			Draw(texture, destination, sourceRectangle, color, 0.0f, Vector2::Zero, SpriteEffects::None, 0.0f); 	
        }

		void SpriteBatch::Draw(Texture2D texture, Rectangle destinationRectangle, Rectangle sourceRectangle, Color color, float rotation, Vector2 origin, SpriteEffects_t effects, float layerDepth) 
        { 
			Sprite sprite = Sprite(texture, 
								sourceRectangle != Rectangle::Empty ? sourceRectangle : Rectangle(0, 0, texture.getWidth(), texture.getHeight()), 
								destinationRectangle, 
								color, 
								rotation, 
								origin, 
								effects, 
								layerDepth);

			SpriteList.Add(sprite);

			if (spriteSortMode == SpriteSortMode::Immediate)
				Flush(); 
        }

		void SpriteBatch::Draw(Texture2D texture, Vector2 position, Rectangle sourceRectangle, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteEffects_t effects, float layerDepth) 
        { 
            int width;
			int height;
			if (sourceRectangle != Rectangle::Empty)
			{
				width = (int)(sourceRectangle.Width * scale.X);
				height = (int)(sourceRectangle.Height * scale.Y);
			}
			else
			{
				width = (int)(texture.getWidth() * scale.X);
				height = (int)(texture.getHeight() * scale.Y);
			}
			Rectangle destination = Rectangle((int)position.X, (int)position.Y, width, height);
			Draw(texture, destination, sourceRectangle, color, rotation, origin, effects, layerDepth); 
        }
        
        void SpriteBatch::Draw(Texture2D texture, Vector2 position, Rectangle sourceRectangle, Color color, float rotation, Vector2 origin, float scale, SpriteEffects_t effects, float layerDepth)
        {
	        int width;
			int height;
			if (sourceRectangle != Rectangle::Empty)
			{
				width = (int)(sourceRectangle.Width * scale);
				height = (int)(sourceRectangle.Height * scale);
			}
			else
			{
				width = (int)(texture.getWidth() * scale);
				height = (int)(texture.getHeight() * scale);
			}
			Rectangle destination = Rectangle((int)position.X, (int)position.Y, width, height);
			Draw(texture, destination, sourceRectangle, color, rotation, origin, effects, layerDepth);
        }
        
        void SpriteBatch::DrawString(SpriteFont spriteFont, char* text, Vector2 position, Color color)
        {            
           	spriteFont.Draw(text, *this, position, color, 0.0f, Vector2::Zero, Vector2::One, SpriteEffects::None, 0.0f); 
        }

		void SpriteBatch::DrawString(SpriteFont spriteFont, char* text, Vector2 position, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteEffects_t effects, float layerDepth)
		{
			spriteFont.Draw(text, *this, position, color, rotation, origin, scale, effects, layerDepth);
		}
        
        void SpriteBatch::DrawString(SpriteFont spriteFont, char* text, Vector2 position, Color color, float rotation, Vector2 origin, float scale, SpriteEffects_t effects, float layerDepth)
        {
			Vector2 vector = Vector2::Zero;
            vector.X = scale; 
            vector.Y = scale; 
            spriteFont.Draw(text, *this, position, color, rotation, origin, vector, effects, layerDepth); 
        }
        
        void SpriteBatch::End() 
        { 
            if (!inBeginEndPair)
			{
#if DEBUG
				printf("INVALID_OPERATION in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Begin must be called successfully before End can be called.");
#endif
				return;
			}
			
			if (spriteSortMode != SpriteSortMode::Immediate)
			{
				applyGraphicsDeviceSettings();
				Flush();
			}
			
			/*glDisable(GL_TEXTURE_2D);
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();*/
			
			restoreRenderState(); 

			inBeginEndPair = false;
        }
        
        void SpriteBatch::restoreRenderState()
        {
	        if (saveStateMode == SaveStateMode::SaveState) 
                saveState.Apply(); 
        }
        
        void SpriteBatch::applyGraphicsDeviceSettings() 
        {
			unsigned int* p;

            // Set the blend mode 
            switch (spriteBlendMode) 
            { 
                case SpriteBlendMode::AlphaBlend: 
                    p = pb_begin();
					//Enable blending
					pb_push(p, NV20_TCL_PRIMITIVE_3D_BLEND_FUNC_ENABLE, 1); p+=2;
					//set blendmode
					pb_push2(p, NV20_TCL_PRIMITIVE_3D_BLEND_FUNC_SRC, (0x302<<16) | 0x302, (0x303<<16) | 0x303); p+=3;
					//send data to GPU
					pb_end(p);
                    break; 
                case SpriteBlendMode::Additive:
					p = pb_begin();
					//Enable blending
					pb_push(p, NV20_TCL_PRIMITIVE_3D_BLEND_FUNC_ENABLE, 1); p+=2;
					//set blendmode
					pb_push2(p, NV20_TCL_PRIMITIVE_3D_BLEND_FUNC_SRC, (0x302<<16) | 0x302, (1<<16) | 1); p+=3;
					//send data to GPU
					pb_end(p);
                    break; 
                case SpriteBlendMode::None: 
                    p = pb_begin();
					//Disable Blending
					pb_push(p, NV20_TCL_PRIMITIVE_3D_BLEND_FUNC_ENABLE, 0); p+=2;
					//send data to GPU
					pb_end(p);
                    break; 
                default: 
                    return; 
            } 
                          
            //glEnable(GL_TEXTURE_2D); 
  
            // Reset the projection matrix and use the orthographic matrix 
            /*int viewPort[4]; 
            glGetIntegerv(GL_VIEWPORT, viewPort); 
            glMatrixMode(GL_PROJECTION); 
            glPushMatrix();
            glLoadIdentity();
			glOrtho(0, device.Viewport_().Width, device.Viewport_().Height, 0, -1, 1); // viewPort[2] = width, viewPort[3] = height 
            glMatrixMode(GL_MODELVIEW); 
            glPushMatrix(); 
            glLoadIdentity();*/
        }

		void SpriteBatch::Flush()
        {
			switch (spriteSortMode)
			{
			case SpriteSortMode::BackToFront:
				//SpriteList.Sort(BackToFrontSpriteComparer<Sprite>());
				break;
			case SpriteSortMode::FrontToBack:
				//SpriteList.Sort(FrontToBackSpriteComparer<Sprite>());
				break;
			case SpriteSortMode::Texture: // nothing here?
				break;
			}
			for (int i = 0; i < SpriteList.Count(); i++)
			{
				// Set the color, bind the texture for drawing and prepare the texture source
				if (SpriteList[i].getColor().A() <= 0) continue;
				//glColor4f((float)sprite.Color_().R() / 255f, (float)sprite.getColor().G() / 255f, (float)sprite.getColor().B() / 255f, (float)sprite.getColor().A() / 255f);
				//glBindTexture(GL_TEXTURE_2D, sprite.getTexture().textureId);
				// Setup the matrix
				//if ((SpriteList[i].DestinationRectangle().X != 0) || (SpriteList[i].DestinationRectangle().Y != 0))
				//	glTranslatef(SpriteList[i].DestinationRectangle().X, SpriteList[i].DestinationRectangle().Y, 0.0f); // Position

				//if (SpriteList[i].Rotation() != 0)
				//	glRotatef(MathHelper::ToDegrees(SpriteList[i].Rotation()), 0.0f, 0.0f, 1.0f); // Rotation

				/*if ((SpriteList[i].DestinationRectangle().Width != 0 && SpriteList[i].Origin().X != 0) || (SpriteList[i].DestinationRectangle().Height != 0 && SpriteList[i].Origin().Y != 0))
					glTranslatef(
					// Orientation
					-SpriteList[i].Origin.X * (float)SpriteList[i].DestinationRectangle().Width / (float)SpriteList[i].SourceRectangle().Width,
					-SpriteList[i].Origin.Y * (float)SpriteList[i].DestinationRectangle().Height / (float)SpriteList[i].SourceRectangle().Height, 0.0f);*/
				// Calculate the points on the texture
				float x = (float)SpriteList[i].SourceRectangle().X / (float)SpriteList[i].getTexture().getWidth();
				float y = (float)SpriteList[i].SourceRectangle().Y / (float)SpriteList[i].getTexture().getHeight();
				float twidth = (float)SpriteList[i].SourceRectangle().Width / (float)SpriteList[i].getTexture().getWidth();
				float theight = (float)SpriteList[i].SourceRectangle().Height / (float)SpriteList[i].getTexture().getHeight();
				// Draw
				/*glBegin(GL_QUADS);
				{
					glTexCoord2f(x,y + theight);
					glVertex2f(0f, SpriteList[i].DestinationRectangle().Height);
					glTexCoord2f(x + twidth, y + theight);
					glVertex2f(SpriteList[i].DestinationRectangle().Width, SpriteList[i].DestinationRectangle().Height);
					glTexCoord2f(x + twidth,y);
					glVertex2f(SpriteList[i].DestinationRectangle().Width, 0f);
					glTexCoord2f(x,y);
					glVertex2f(0f, 0f);
				}
				glEnd();
				glPopMatrix(); // Finish with the matrix*/
			}
			SpriteList.Clear();  
        }
	}
}
