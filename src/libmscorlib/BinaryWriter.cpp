#include <System/IO/BinaryWriter.h>
#include <System/String.h>

#include <sassert.h>
#include <stdlib.h>

namespace System
{
	namespace IO
	{
		const int BinaryWriter::LargeByteBufferSize = 0x100;

		BinaryWriter::BinaryWriter()
		{
			_tmpOneCharBuffer = new char[1];
			OutStream = new Stream();
			_buffer = new byte[0x10];
		}

		BinaryWriter::BinaryWriter(Stream* output)
		{
			_tmpOneCharBuffer = new char[1];

			sassert(output != null, "");

			OutStream = output;
			_buffer = new byte[0x10];
		}

		void BinaryWriter::Close()
		{
			this->Dispose(true);
		}

		void BinaryWriter::Dispose(bool disposing)
		{
			this->OutStream->Flush();
		}

		void BinaryWriter::Flush()
		{
			this->OutStream->Flush();
		}

		void BinaryWriter::Write(const bool value)
		{
			_buffer[0] = value ? ((byte)1) : ((byte)0);
			this->OutStream->Write(_buffer, 0, 1);
		}

		void BinaryWriter::Write(const String value)
		{
			this->Write(value.Length);
			char* chars = value.ToCharArray();
			this->Write(chars, 0, value.Length);
			free(chars);
		}

		void BinaryWriter::Write(const int value)
		{
			_buffer[0] = (byte)value;
			_buffer[1] = (byte)(value >> 8);
			_buffer[2] = (byte)(value >> 16);
			_buffer[3] = (byte)(value >> 24);
			this->OutStream->Write(_buffer, 0, 4);
		}

		void BinaryWriter::Write(const long long value)
		{
			_buffer[0] = (byte)value;
			_buffer[1] = (byte)(value >> 8);
			_buffer[2] = (byte)(value >> 16);
			_buffer[3] = (byte)(value >> 24);
			_buffer[4] = (byte)(value >> 32);
			_buffer[5] = (byte)(value >> 40);
			_buffer[6] = (byte)(value >> 48);
			_buffer[7] = (byte)(value >> 56);
			this->OutStream->Write(_buffer, 0, 8);
		}
	}
}
