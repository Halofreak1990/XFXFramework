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
			return (int)BaseStream()->Length();
		}

		int PacketWriter::Position()
		{
			return (int)BaseStream()->Position;
		}

		void PacketWriter::Position(int newValue)
		{
			BaseStream()->Position = newValue;
		}

		PacketWriter::PacketWriter()
			: BinaryWriter(new MemoryStream(0))
		{
		}

		PacketWriter::PacketWriter(int capacity)
			: BinaryWriter(new MemoryStream(capacity))
		{
		}

		void PacketWriter::Write(Matrix value)
		{
			BinaryWriter::Write(value.M11);
			BinaryWriter::Write(value.M12);
			BinaryWriter::Write(value.M13);
			BinaryWriter::Write(value.M14);
			BinaryWriter::Write(value.M21);
			BinaryWriter::Write(value.M22);
			BinaryWriter::Write(value.M23);
			BinaryWriter::Write(value.M24);
			BinaryWriter::Write(value.M31);
			BinaryWriter::Write(value.M32);
			BinaryWriter::Write(value.M33);
			BinaryWriter::Write(value.M34);
			BinaryWriter::Write(value.M41);
			BinaryWriter::Write(value.M42);
			BinaryWriter::Write(value.M43);
			BinaryWriter::Write(value.M44);
		}

		void PacketWriter::Write(Quaternion value)
		{
			BinaryWriter::Write(value.X);
			BinaryWriter::Write(value.Y);
			BinaryWriter::Write(value.Z);
			BinaryWriter::Write(value.W);
		}

		void PacketWriter::Write(Vector2 value)
		{
			BinaryWriter::Write(value.X);
			BinaryWriter::Write(value.Y);
		}

		void PacketWriter::Write(Vector3 value)
		{
			BinaryWriter::Write(value.X);
			BinaryWriter::Write(value.Y);
			BinaryWriter::Write(value.Z);
		}

		void PacketWriter::Write(Vector4 value)
		{
			BinaryWriter::Write(value.X);
			BinaryWriter::Write(value.Y);
			BinaryWriter::Write(value.Z);
			BinaryWriter::Write(value.W);
		}
	}
}
