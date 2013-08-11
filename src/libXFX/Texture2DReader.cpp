// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
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

#include "Enums.h"
#include "Texture2DReader.h"

#include <System/BitConverter.h>
#include <Content/ContentReader.h>
#include <System/Diagnostics/Debug.h>

using namespace System;

namespace XFX
{
	namespace Content
	{
		Texture2D* Texture2DReader::Read(ContentReader * reader, Texture2D * existingInstance)
		{
			Texture2D* texture = null;

			SurfaceFormat_t surfaceFormat;

			if (reader->getVersion() < 5)
			{
				SurfaceFormat_Legacy_t legacyFormat = (SurfaceFormat_Legacy_t)reader->ReadInt32();
				switch(legacyFormat)
				{
				case SurfaceFormat_Legacy::Dxt1:
					surfaceFormat = SurfaceFormat::Dxt1;
					break;
				case SurfaceFormat_Legacy::Dxt3:
					surfaceFormat = SurfaceFormat::Dxt3;
					break;
				case SurfaceFormat_Legacy::Dxt5:
					surfaceFormat = SurfaceFormat::Dxt5;
					break;
				case SurfaceFormat_Legacy::Color:
					surfaceFormat = SurfaceFormat::Color;
					break;
				default:
					//throw new NotImplementedException();
					break;
				}
			}
			else
			{
				surfaceFormat = (SurfaceFormat_t)reader->ReadInt32();
			}

			int width = reader->ReadInt32();
			int height = reader->ReadInt32();
			int levelCount = reader->ReadInt32();
			int levelCountOutput = levelCount;

			// If the system does not fully support Power of Two textures,
			// skip any mip maps supplied with any non PoT textures.
			if (levelCount > 1 && !GraphicsCapabilities.SupportsNonPowerOfTwo &&
				(!MathHelper::IsPowerOfTwo(width) || !MathHelper::IsPowerOfTwo(height)))
			{
				levelCountOutput = 1;
				System::Diagnostics::Debug::WriteLine(
					"Device does not support non Power of Two textures. Skipping mipmaps.");
			}

			SurfaceFormat_t convertedFormat = surfaceFormat;
			switch (surfaceFormat)
			{
			case SurfaceFormat::Dxt1:
			//case SurfaceFormat::Dxt1a:
				if (!GraphicsCapabilities.SupportsDxt1)
					convertedFormat = SurfaceFormat::Color;
				break;
			case SurfaceFormat::Dxt3:
			case SurfaceFormat::Dxt5:
				if (!GraphicsCapabilities.SupportsS3tc)
					convertedFormat = SurfaceFormat::Color;
				break;
			case SurfaceFormat::NormalizedByte4:
				convertedFormat = SurfaceFormat::Color;
				break;
			}

			if (existingInstance == null)
			{
				texture = new Texture2D(reader->getGraphicsDevice(), width, height, levelCountOutput > 1, convertedFormat);
			}
			else
			{
				texture = existingInstance;

				texture->Dispose();

				texture = new Texture2D(reader->getGraphicsDevice(), width, height, levelCountOutput > 1, convertedFormat);
			}

			for (int level=0; level<levelCount; level++)
			{
				int levelDataSizeInBytes = reader->ReadInt32();
				byte* levelData = reader->ReadBytes(levelDataSizeInBytes);
				int levelWidth = width >> level;
				int levelHeight = height >> level;

				if (level >= levelCountOutput)
				{
					continue;
				}

				switch (surfaceFormat)
				{
				case SurfaceFormat::Dxt1:
				//case SurfaceFormat::Dxt1a:
					if (!GraphicsCapabilities.SupportsDxt1)
						levelData = DxtUtil::DecompressDxt1(levelData, levelWidth, levelHeight);
					break;
				case SurfaceFormat::Dxt3:
					if (!GraphicsCapabilities.SupportsS3tc)
						levelData = DxtUtil::DecompressDxt3(levelData, levelWidth, levelHeight);
					break;
				case SurfaceFormat::Dxt5:
					if (!GraphicsCapabilities.SupportsS3tc)
						levelData = DxtUtil::DecompressDxt5(levelData, levelWidth, levelHeight);
					break;
				case SurfaceFormat::Bgr565:
					{
						/*
						// BGR -> BGR
						int offset = 0;
						for (int y = 0; y < levelHeight; y++)
						{
							for (int x = 0; x < levelWidth; x++)
							{
								ushort pixel = BitConverter.ToUInt16(levelData, offset);
								pixel = (ushort)(((pixel & 0x0FFF) << 4) | ((pixel & 0xF000) >> 12));
								levelData[offset] = (byte)(pixel);
								levelData[offset + 1] = (byte)(pixel >> 8);
								offset += 2;
							}
						}
							*/
					}
					break;
				case SurfaceFormat::Bgra5551:
					{
#if OPENGL
						// Shift the channels to suit OPENGL
						int offset = 0;
						for (int y = 0; y < levelHeight; y++)
						{
							for (int x = 0; x < levelWidth; x++)
							{
								ushort pixel = BitConverter::ToUInt16(levelData, offset);
								pixel = (ushort)(((pixel & 0x7FFF) << 1) | ((pixel & 0x8000) >> 15));
								levelData[offset] = (byte)(pixel);
								levelData[offset + 1] = (byte)(pixel >> 8);
								offset += 2;
							}
						}
#endif
					}
					break;
				case SurfaceFormat::Bgra4444:
					{
#if OPENGL
						// Shift the channels to suit OPENGL
						int offset = 0;
						for (int y = 0; y < levelHeight; y++)
						{
							for (int x = 0; x < levelWidth; x++)
							{
								ushort pixel = BitConverter::ToUInt16(levelData, offset);
								pixel = (ushort)(((pixel & 0x0FFF) << 4) | ((pixel & 0xF000) >> 12));
								levelData[offset] = (byte)(pixel);
								levelData[offset + 1] = (byte)(pixel >> 8);
								offset += 2;
							}
						}
#endif
					}
					break;
				case SurfaceFormat::NormalizedByte4:
					{
						int bytesPerPixel = surfaceFormat.Size();
						int pitch = levelWidth * bytesPerPixel;
						for (int y = 0; y < levelHeight; y++)
						{
							for (int x = 0; x < levelWidth; x++)
							{
								int color = BitConverter::ToInt32(levelData, y * pitch + x * bytesPerPixel);
								levelData[y * pitch + x * 4] = (byte)(((color >> 16) & 0xff)); //R:=W
								levelData[y * pitch + x * 4 + 1] = (byte)(((color >> 8) & 0xff)); //G:=V
								levelData[y * pitch + x * 4 + 2] = (byte)(((color) & 0xff)); //B:=U
								levelData[y * pitch + x * 4 + 3] = (byte)(((color >> 24) & 0xff)); //A:=Q
							}
						}
					}
					break;
				}

				//texture->SetData(levelData, 0, 
			}
			return texture;
		}
	}
}
