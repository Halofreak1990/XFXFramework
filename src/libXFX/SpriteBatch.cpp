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

#include <Graphics/Color.h>
#include <Graphics/Sprite.h>
#include <Graphics/SpriteBatch.h>
#include <Graphics/SpriteFont.h>
#include <Graphics/Texture2D.h>
#include <Matrix.h>
#include <Rectangle.h>
#include <Vector2.h>

using namespace XFX;

namespace XFX
{
	namespace Graphics
	{
		SpriteBatch::GraphicsDevice_()
		{
			return device;
			spriteBlendMode = SpriteBlendMode::None
		}
		
		SpriteBatch::IsDisposed()
		{
			return disposed;
		}
		
		SpriteBatch::~SpriteBatch()
		{
			Dispose(false);
		}
		
		SpriteBatch::SpriteBatch(GraphicsDevice graphicsDevice)
		{
			device = graphicsDevice;
		}
	
		void SpriteBatch::Begin() 
        { 
            Begin(SpriteBlendMode::AlphaBlend, SpriteSortMode::Deferred, SaveStateMode::None, Matrix::Identity); 
        }
        
        void SpriteBatch::Begin(SpriteBlendMode blendMode, SpriteSortMode sortMode, SaveStateMode stateMode)
        {
	        Begin(blendMode, sortMode, stateMode, Matrix::Identity);
        }
        
        void Begin(SpriteBlendMode blendMode, SpriteSortMode sortMode, SaveStateMode stateMode, Matrix transformMatrix) 
        { 
            //to respect order Begin/Draw/end 
            if (isRunning) 
                return;
  
            if (stateMode == SaveStateMode::SaveState) 
                saveState = StateBlock(device); 
  
            spriteBlendMode = blendMode; 
            this.sortMode = sortMode; 
            if (sortMode == SpriteSortMode::Immediate) 
                applyGraphicsDeviceSettings(); 
        	isRunning = true; 
        }
         
        void SpriteBatch::Dispose(int disposing)
        {
	        if (!disposed) 
            { 
                if (disposing) 
                { 
  		            // Release any managed components 
                } 
                disposed = true; 
                // Release any unmanaged components 
            } 
        }
         
        void SpriteBatch::Dispose()
        {
	        Dispose(true);
        }
         
        void SpriteBatch::Draw(Texture2D &texture, Rectangle &destinationRectangle, Color &color)
        {
	        Draw(texture, destinationRectangle, Rectangle::Zero, color, 0f, Vector2::Zero, SpriteEffects::None, 0f);
        }
         
        void SriteBatch::Draw(Texture2D &texture, Rectangle &destinationRectangle, Rectangle &sourceRectangle, Color &color)
        {
	        Draw(texture, destinationRectangle, sourceRectangle, color, 0f, Vector2::Zero, SpriteEffects::None, 0f);
        }
         
        void SpriteBatch::Draw(Texture2D &texture, Vector2 &position, Color &color)
        {
	        Draw(texture, position, Rectangle::Zero, color);
        }
        
        void SpriteBatch::Draw(Texture2D &texture, Vector2 &position, Rectangle &sourceRectangle, Color &color)
        {
	        Rectangle destination = Rectangle((int)vector.X, (int)vector.Y, texture.Width, texture.Height); 
         	Draw(texture, destination, sourceRectangle, color, 0f, Vector2::Zero, SpriteEffects::None, 0f); 
        }
        
        void SpriteBatch::Draw(Texture2D &texture, Vector2 &position, Rectangle &sourceRectangle, Color &color, float rotation, Vector2 &origin, float scale, SpriteEffects_t effects, float layerDepth)
        {
	        int width; 
            int height; 
            if (sourceRectangle != Rectangle::Zero) 
            { 
            	width = (int)(sourceRectangle.Width * scale); 
         		height = (int)(sourceRectangle.Height * scale); 
            } 
            else 
            { 
                width = (int)(texture.Width * scale); 
                height = (int)(texture.Height * scale); 
            } 
            Rectangle destination = Rectangle((int)vector.X, (int)vector.Y, width, height); 
            Draw(texture, destination, sourceRectangle, color, rotation, origin, effects, layerDepth); 
        }
        
        void SpriteBatch::Draw(Texture2D &texture, Vector2 &position, Rectangle &sourceRectangle, Color &color, float rotation, Vector2 &origin, Vector2 &scale, SpriteEffects_t effects, float layerDepth) 
        { 
            int width; 
            int height; 
            if (sourceRectangle != Rectangle::Zero) 
            { 
                width = (int)(sourceRectangle.Width * scale.X); 
                height = (int)(sourceRectangle.Height * scale.Y); 
            } 
            else 
            { 
                width = (int)(texture.Width * scale.X); 
                height = (int)(texture.Height * scale.Y); 
            } 
            Rectangle destination = Rectangle((int)vector.X, (int)vector.Y, width, height); 
            Draw(texture, destination, sourceRectangle, color, rotation, origin, effects, layerDepth); 
        }
        
        void SpriteBatch::Draw(Texture2D &texture, Rectangle &destinationRectangle, Rectangle &sourceRectangle, Color &color, float rotation, Vector2 &origin, SpriteEffects_t &effects, float layerDepth) 
        { 
            if (!isRunning) 
                return;
  
            Sprite temp = Sprite(texture, (sourceRectangle != Rectangle::Zero) ? sourceRectangle : Rectangle(0, 0, texture.Width, texture.Height), 
                destinationRectangle, color, rotation, origin, effects, layerDepth); 
                          
            spriteList.Add(temp); 
  
            if (sortMode == SpriteSortMode::Immediate) 
                flush(); 
        }
        
        void SpriteBatch::DrawString(SpriteFont &spriteFont, char* text, Vector2 &position, Color &color)
        {
	        if (!spriteFont) 
            	return;
            if (!text) 
            	return; 
            
           	spriteFont.Draw(text, *this, position, color, 0f, Vector2::Zero, Vector2::One, SpriteEffects::None, 0f); 
        }
        
        void SpriteBatch::DrawString(SpriteFont &spriteFont, char* text, Vector2 &position, Color &color, float rotation, Vector2 &origin, float scale, SpriteEffects_t effects, float layerDepth)
        {
	        Vector2 vector; 
            if (!spriteFont) 
            	return;
            if (!text) 
				return;
				
            vector.X = scale; 
            vector.Y = scale; 
            spriteFont.Draw(text, *this, position, color, rotation, origin, vector, effects, layerDepth); 
        }
        
        void SpriteBatch::End() 
        { 
            if (!isRunning) 
                return; 
             
            if (sortMode != SpriteSortMode::Immediate) 
            { 
                applyGraphicsDeviceSettings(); 
                flush(); 
            } 
                          
            glDisable(GL_TEXTURE_2D); 
  
            Gl::glMatrixMode(Gl::GL_PROJECTION); 
            Gl::glPopMatrix(); 
            Gl::glMatrixMode(Gl::GL_MODELVIEW); 
            Gl::glPopMatrix(); 
  
            restoreRenderState(); 
            isRunning = false; 
        }
        
        void SpriteBatch::restoreRenderState()
        {
	        if (stateMode == SaveStateMode::SaveState) 
                saveState.Apply(); 
        }
        
        void SpriteBatch::flush()
        {
	        switch (sortMode) 
            { 
                case SpriteSortMode::BackToFront: 
                    spriteList.Sort(BackToFrontSpriteComparer<Sprite>()); 
                    break; 
                case SpriteSortMode::FrontToBack: 
                    spriteList.Sort(FrontToBackSpriteComparer<Sprite>()); 
                    break; 
                case SpriteSortMode::Texture: // nothing here? 
                    break; 
            }
            
            spriteList.First();
            Sprite temp;
            while(spriteList.Next(temp))
            {
	            // Set the color, bind the texture for drawing and prepare the texture source 
                if (temp.Color.A <= 0) continue; 
                Gl::glColor4f((float)temp.Color.R / 255f, (float)temp.Color.G / 255f, (float)temp.Color.B / 255f, (float)temp.Color.A / 255f); 
                Gl::glBindTexture(Gl::GL_TEXTURE_2D, temp.Texture.textureId); 
  
                // Setup the matrix 
                Gl::glPushMatrix(); 
                if ((temp.DestinationRectangle.X != 0) || (temp.DestinationRectangle.Y != 0)) 
                    Gl::glTranslatef(temp.DestinationRectangle.X, temp.DestinationRectangle.Y, 0f); // Position 
                if (temp.Rotation != 0) 
                    Gl::glRotatef(MathHelper.ToDegrees(temp.Rotation), 0f, 0f, 1f); // Rotation 
                if ((temp.DestinationRectangle.Width != 0 && temp.Origin.X != 0) || (temp.DestinationRectangle.Height != 0 && temp.Origin.Y != 0)) 
                    Gl::glTranslatef( // Orientation 
                        -temp.Origin.X * (float)temp.DestinationRectangle.Width / (float)temp.SourceRectangle.Width, 
                        -temp.Origin.Y * (float)temp.DestinationRectangle.Height / (float)temp.SourceRectangle.Height, 0f); 
  
                // Calculate the points on the texture 
                float x = (float)temp.SourceRectangle.X / (float)temp.Texture.Width; 
                float y = (float)temp.SourceRectangle.Y / (float)temp.Texture.Height; 
                float twidth = (float)temp.SourceRectangle.Width / (float)temp.Texture.Width; 
                float theight = (float)temp.SourceRectangle.Height / (float)temp.Texture.Height; 
                                  
                                // Draw 
                Gl::glBegin(Gl::GL_QUADS); 
                { 
                    Gl::glTexCoord2f(x,y + theight); 
                    Gl::glVertex2f(0f, temp.DestinationRectangle.Height); 
  
                    Gl::glTexCoord2f(x + twidth, y + theight); 
                    Gl::glVertex2f(temp.DestinationRectangle.Width, temp.DestinationRectangle.Height); 
  
                    Gl::glTexCoord2f(x + twidth,y); 
                    Gl::glVertex2f(temp.DestinationRectangle.Width, 0f); 
  
                    Gl::glTexCoord2f(x,y); 
                    Gl::glVertex2f(0f, 0f); 
                } 
                Gl::glEnd(); 
                Gl::glPopMatrix(); // Finish with the matrix 
            }
            spriteList.Clear();
        }
        
        void SpriteBatch::applyGraphicsDeviceSettings() 
        { 
            // Set the blend mode 
            switch (spriteBlendMode) 
            { 
                case SpriteBlendMode::AlphaBlend: 
                    glEnable(GL_BLEND); 
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
                    break; 
                case SpriteBlendMode::Additive: 
                    glEnable(GL_BLEND); 
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
                    break; 
                case SpriteBlendMode::None: 
                    glDisable(GL_BLEND);
                    break; 
                default: 
                    return; 
            } 
                          
            glEnable(GL_TEXTURE_2D); 
  
            // Reset the projection matrix and use the orthographic matrix 
            int[] viewPort = new int[4]; 
            Gl::glGetIntegerv(Gl::GL_VIEWPORT, viewPort); 
            Gl::glMatrixMode(Gl::GL_PROJECTION); 
            Gl::glPushMatrix(); 
            Gl::glLoadIdentity(); 
            Gl::glOrtho(0, viewPort[2], viewPort[3], 0, -1, 1); // viewPort[2] = width, viewPort[3] = height 
            Gl::glMatrixMode(Gl::GL_MODELVIEW); 
            Gl::glPushMatrix(); 
            Gl::glLoadIdentity(); 
        }
	}
}
