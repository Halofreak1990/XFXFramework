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

#include <Graphics/SpriteBatch.h>
#include <Graphics/SpriteFont.h>
#include <Matrix.h>
#include <System/Array.h>
#include <System/Math.h>

#if DEBUG
#include <stdio.h>
#endif

namespace XFX
{
	namespace Graphics
	{
		SpriteFont::SpriteFont(Texture2D texture, List<Rectangle> glyphs, List<Rectangle> cropping, List<char> charMap, int lineSpacing, float spacing, List<Vector3> kerning)
		{
			textureValue = texture;
			glyphData = glyphs;
			croppingData = cropping;
			characterMap = charMap;
			this->lineSpacing = lineSpacing;
			this->spacing = spacing;
			this->kerning = kerning;
		}

		void SpriteFont::Draw(char* text, SpriteBatch spriteBatch, Vector2 textblockPosition, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteEffects_t spriteEffects, float depth)
		{
			Vector2 vector2;
			Matrix matrix;
			Matrix matrix2;

			if (text == null)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "text");
#endif
				return;
			}

			Matrix::CreateRotationZ(rotation, matrix2);
			Matrix::CreateTranslation(-origin.X * scale.X, -origin.Y * scale.Y, 0.0f, matrix);
			Matrix::Multiply(matrix, matrix2, matrix2);
			int num2 = 1;
			float num4 = 0.0f;
			bool flag = true;
			if ((spriteEffects & SpriteEffects::FlipHorizontally) == SpriteEffects::FlipHorizontally)
			{
				num4 = MeasureString(text).X * scale.X;
				num2 = -1;
			}
			if ((spriteEffects & SpriteEffects::FlipVertically) == SpriteEffects::FlipVertically)
			{
				vector2.Y = (MeasureString(text).Y - lineSpacing) * scale.Y;
			}
			else
			{
				vector2.Y = 0.0f;
			}
			vector2.X = num4;
			for (int i = 0; i < Array::Length(text); i++)
			{
				char character = text[i];
				switch (character)
				{
					case '\r':
						break;

					case '\n':
						flag = true;
						vector2.X = num4;
						if ((spriteEffects & SpriteEffects::FlipVertically) == SpriteEffects::FlipVertically)
						{
							vector2.Y -= lineSpacing * scale.Y;
						}
						else
						{
							vector2.Y += lineSpacing * scale.Y;
						}
						break;

					default:
					{
						int indexForCharacter = GetIndexForCharacter(character);
						Vector3 vector3 = kerning[indexForCharacter];
						if (flag)
						{
							vector3.X = Math::Max(vector3.X, 0.0f);
						}
						else
						{
							vector2.X += (spacing * scale.X) * num2;
						}
						vector2.X += (vector3.X * scale.X) * num2;
						Rectangle rectangle = glyphData[indexForCharacter];
						Rectangle rectangle2 = croppingData[indexForCharacter];
						if ((spriteEffects & SpriteEffects::FlipVertically) == SpriteEffects::FlipVertically)
						{
							rectangle2.Y = (lineSpacing - rectangle.Height) - rectangle2.Y;
						}
						if ((spriteEffects & SpriteEffects::FlipHorizontally) == SpriteEffects::FlipHorizontally)
						{
							rectangle2.X -= rectangle2.Width;
						}
						Vector2 position = vector2;
						position.X += rectangle2.X * scale.X;
						position.Y += rectangle2.Y * scale.Y;
						Vector2::Transform(position, matrix2, position);
						position.X += textblockPosition.X;
						position.Y += textblockPosition.Y;
						spriteBatch.Draw(textureValue, position, rectangle, color, rotation, Vector2::Zero, scale, spriteEffects, depth);
						flag = false;
						vector2.X += ((vector3.Y + vector3.Z) * scale.X) * num2;
						break;
					}
				}
			}
		}

		int SpriteFont::GetIndexForCharacter(char character)
		{
			int num2 = 0;
			int num3 = characterMap.Count() - 1;
			while (num2 <= num3)
			{
				int num = num2 + ((num3 - num2) >> 1);
				char ch = characterMap[num];
				if (ch == character)
				{
					return num;
				}
				if (ch < character)
				{
					num2 = num + 1;
				}
				else
				{
					num3 = num - 1;
				}
			}
#if DEBUG
			printf("ARGUMENT in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "character");
#endif
		}
	}
}
