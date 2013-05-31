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

#include <Content/ContentReader.h>
#include <Matrix.h>
#include <Quaternion.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>

namespace XFX
{
	namespace Content
	{
		const short ContentReader::XnbVersion = 2;

		String ContentReader::getAssetName() const
		{
			return _assetName;
		}

		ContentManager* ContentReader::getContentManager() const
		{
			return contentManager;
		}

		ContentReader::ContentReader(ContentManager * const manager, Stream * const stream, GraphicsDevice * const graphicsDevice) 
			: BinaryReader(stream), contentManager(manager), _graphicsDevice(graphicsDevice)
		{
		}

		ContentReader::ContentReader(ContentManager * const manager, Stream * const input, const String& assetName)
			: BinaryReader(PrepareStream(input, assetName)), contentManager(manager), _assetName(assetName)
		{
		}

		ContentReader::~ContentReader()
		{
		}

		Stream* ContentReader::PrepareStream(Stream * const, const String& assetName)
		{
		}

		Matrix ContentReader::ReadMatrix()
		{
			Matrix result;
			result.M11 = ReadSingle();
			result.M12 = ReadSingle();
			result.M13 = ReadSingle();
			result.M14 = ReadSingle();
			result.M21 = ReadSingle();
			result.M22 = ReadSingle();
			result.M23 = ReadSingle();
			result.M24 = ReadSingle();
			result.M31 = ReadSingle();
			result.M32 = ReadSingle();
			result.M33 = ReadSingle();
			result.M34 = ReadSingle();
			result.M41 = ReadSingle();
			result.M42 = ReadSingle();
			result.M43 = ReadSingle();
			result.M44 = ReadSingle();
			return result;
		}

		Quaternion ContentReader::ReadQuaternion()
		{
			Quaternion result;
			result.X = ReadSingle();
			result.Y = ReadSingle();
			result.Z = ReadSingle();
			result.W = ReadSingle();
			return result;
		}

		Vector2 ContentReader::ReadVector2()
		{
			Vector2 result;
			result.X = ReadSingle();
			result.Y = ReadSingle();
			return result;
		}

		Vector3 ContentReader::ReadVector3()
		{
			Vector3 result;
			result.X = ReadSingle();
			result.Y = ReadSingle();
			result.Z = ReadSingle();
			return result;
		}

		Vector4 ContentReader::ReadVector4()
		{
			Vector4 result;
			result.X = ReadSingle();
			result.Y = ReadSingle();
			result.Z = ReadSingle();
			result.W = ReadSingle();
			return result;
		}
	}
}
