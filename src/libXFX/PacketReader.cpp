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

#include <System/IO/MemoryStream.h>
#include <Net/PacketReader.h>
#include <Matrix.h>
#include <Quaternion.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>

namespace XFX
{
	namespace Net
	{
		int PacketReader::Length()
		{
			return (int)BaseStream()->Length();
		}

		int PacketReader::getPosition()
		{
			return (int)BaseStream()->Position;
		}

		void PacketReader::setPosition(int newValue)
		{
			BaseStream()->Position = newValue;
		}

		PacketReader::PacketReader()
			: BinaryReader(new MemoryStream(0))
		{
		}

		PacketReader::PacketReader(int capacity)
			: BinaryReader(new MemoryStream(capacity))
		{
		}

		Matrix PacketReader::ReadMatrix()
		{
			Matrix matrix;
			matrix.M11 = ReadSingle();
			matrix.M12 = ReadSingle();
			matrix.M13 = ReadSingle();
			matrix.M14 = ReadSingle();
			matrix.M21 = ReadSingle();
			matrix.M22 = ReadSingle();
			matrix.M23 = ReadSingle();
			matrix.M24 = ReadSingle();
			matrix.M31 = ReadSingle();
			matrix.M32 = ReadSingle();
			matrix.M33 = ReadSingle();
			matrix.M34 = ReadSingle();
			matrix.M41 = ReadSingle();
			matrix.M42 = ReadSingle();
			matrix.M43 = ReadSingle();
			matrix.M44 = ReadSingle();
			return matrix;
		}

		Quaternion PacketReader::ReadQuaternion()
		{
			return Quaternion(
				ReadSingle(),
				ReadSingle(),
				ReadSingle(),
				ReadSingle()
			);
		}

		Vector2 PacketReader::ReadVector2()
		{
			return Vector2(
				ReadSingle(),
				ReadSingle()
			);
		}

		Vector3 PacketReader::ReadVector3()
		{
			return Vector3(
				ReadSingle(),
				ReadSingle(),
				ReadSingle()
			);
		}

		Vector4 PacketReader::ReadVector4()
		{
			return Vector4(
				ReadSingle(),
				ReadSingle(),
				ReadSingle(),
				ReadSingle()
			);
		}
	}
}
