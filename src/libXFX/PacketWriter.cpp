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

#include <Net/PacketWriter.h>
#include <System/IO/MemoryStream.h>

#include <Matrix.h>
#include <Quaternion.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>

namespace XFX
{
	namespace Net
	{
		int PacketWriter::Length()
		{
			return (int)BaseStream.Length;
		}

		int PacketWriter::Position()
		{
			return (int)BaseStream.Position;
		}

		void PacketWriter::Position(int newValue)
		{
			BaseStream.Position = newValue);
		}

		PacketWriter::PacketWriter()
			: BinaryWriter(MemoryStream(0))
		{
		}

		PacketWriter::PacketWriter(int capacity)
			: BinaryWriter(MemoryStream(capacity))
		{
		}

		void PacketWriter::Write(Matrix value)
		{
			Write(value.M11);
			Write(value.M12);
			Write(value.M13);
			Write(value.M14);
			Write(value.M21);
			Write(value.M22);
			Write(value.M23);
			Write(value.M24);
			Write(value.M31);
			Write(value.M32);
			Write(value.M33);
			Write(value.M34);
			Write(value.M41);
			Write(value.M42);
			Write(value.M43);
			Write(value.M44);
		}

		void PacketWriter::Write(Quaternion value)
		{
			Write(value.X);
			Write(value.Y);
			Write(value.Z);
			Write(value.W);
		}

		void PacketWriter::Write(Vector2 value)
		{
			Write(value.X);
			Write(value.Y);
		}

		void PacketWriter::Write(Vector3 value)
		{
			Write(value.X);
			Write(value.Y);
			Write(value.Z);
		}

		void PacketWriter::Write(Vector4 value)
		{
			Write(value.X);
			Write(value.Y);
			Write(value.Z);
			Write(value.W);
		}
	}
}
