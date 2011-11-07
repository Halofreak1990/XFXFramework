// Copyright (C) 2010-2012, XFX Team
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

#include <System/Array.h>
#include <System/Buffer.h>
#include <System/String.h>
#include <System/IO/BinaryReader.h>
#include <System/IO/MemoryStream.h>

#if DEBUG
#include <stdio.h>
#endif

namespace System
{
	namespace IO
	{
		Stream* BinaryReader::BaseStream()
		{
			return m_stream;
		}

		BinaryReader::BinaryReader(Stream* input)
		{
			if (!input->CanRead())
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "The stream doesn't support reading.");
#endif
				return;
			}

			m_disposed = false;
			m_stream = input;
			m_encoding = Encoding::UTF8();
			m_decoder = m_encoding.GetDecoder();
			m_buffer = new byte[32];
		}

		BinaryReader::BinaryReader(Stream* input, Encoding encoding)
		{
			if (!input->CanRead())
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "The stream doesn't support reading.");
#endif
				return;
			}

			m_disposed = false;
			m_stream = input;
			m_encoding = encoding;
			m_decoder = encoding.GetDecoder();
			m_buffer = new byte[32];
		}

		BinaryReader::~BinaryReader()
		{
			Dispose(false);
		}

		void BinaryReader::Close()
		{
			Dispose(true);
		}

		void BinaryReader::Dispose()
		{
			Dispose(true);
		}

		void BinaryReader::Dispose(bool disposing)
		{
			m_stream->Close();

			m_disposed = true;
			delete m_buffer;
			m_buffer = null;
			m_encoding = null;
			m_stream->Close();
			m_stream = null;
			delete[] m_charBuffer;
			m_charBuffer = null;
		}

		void BinaryReader::FillBuffer(int numBytes)
		{
			if (m_disposed)
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "BinaryReader", "Cannot read from a closed BinaryReader.");
#endif
				return;
			}
			
			int offset = 0;
			int num2 = 0;
			if (numBytes == 1)
			{
				num2 = m_stream->ReadByte();
				if (num2 == -1)
				{
#if DEBUG
					printf("END_OF_STREAM in function %s, at line %i in file %s: %s", __FUNCTION__, __LINE__, __FILE__, "Attempted to read beyond End Of File.");
#endif
					return;
				}
				m_buffer[0] = (byte)num2;
			}
			else
			{
				do
				{
					num2 = m_stream->Read(m_buffer, offset, numBytes - offset);
					if (num2 == 0)
					{
#if DEBUG
						printf("END_OF_STREAM in function %s, at line %i in file %s: %s", __FUNCTION__, __LINE__, __FILE__, "Attempted to read beyond End Of File.");
#endif
						return;
					}
					offset += num2;
				}
				while (offset < numBytes);
			}
		}

		int BinaryReader::InternalReadChars(char buffer[], int index, int count)
		{
			int num = 0;
			int num2 = 0;
			int num3 = count;
			if (!m_charBytes)
			{
				m_charBytes = new byte[0x80];
			}
			while (num3 > 0)
			{
				num2 = num3;
				if (m_2BytesPerChar)
				{
					num2 = num2 << 1;
				}
				if (num2 > 0x80)
				{
					num2 = 0x80;
				}
				if (m_isMemoryStream)
				{
					/*MemoryStream stream = (MemoryStream)m_stream;
					int position = stream.InternalGetPosition();
					num2 = stream.InternalEmulateRead(num2);
					if (num2 == 0)
					{
						return (count - num3);
					}
					num = m_decoder.GetChars(stream.InternalGetBuffer(), position, num2, buffer, index);*/
				}
				else
				{
					num2 = m_stream->Read(m_charBytes, 0, num2);
					if (num2 == 0)
					{
						return (count - num3);
					}
					num = m_decoder.GetChars(m_charBytes, 0, num2, buffer, index);
				}
				num3 -= num;
				index += num;
			}
			return count;
		}

		int BinaryReader::InternalReadOneChar()
		{
			/*Int64 position;
			int num = 0;
			int byteCount = 0;
			position = 0LL;
			if (m_stream->CanSeek())
			{
				position = m_stream->Position;
			}
			if (m_charBytes == null)
			{
				m_charBytes = new byte[0x80];
			}
			if (m_singleChar == null)
			{
				m_singleChar = new char[1];
			}
			while (num == 0)
			{
				byteCount = m_2BytesPerChar ? 2 : 1;
				int num4 = m_stream->ReadByte();
				m_charBytes[0] = (byte) num4;
				if (num4 == -1)
				{
					byteCount = 0;
				}
				if (byteCount == 2)
				{
					num4 = m_stream->ReadByte();
					m_charBytes[1] = (byte) num4;
					if (num4 == -1)
					{
						byteCount = 1;
					}
				}
				if (byteCount == 0)
				{
					return -1;
				}
				try
				{
					num = m_decoder.GetChars(m_charBytes, 0, byteCount, m_singleChar, 0);
					continue;
				}
				catch (Exception)
				{
					if (m_stream->CanSeek())
					{
						m_stream->Seek(position - m_stream->Position, SeekOrigin::Current);
					}
					throw;
				}
			}
			if (num == 0)
			{
				return -1;
			}
			return m_singleChar[0];*/

			return -1;
		}

		int BinaryReader::PeekChar()
		{
			if (!m_stream->CanSeek())
			{
				return -1;
			}
			Int64 position = m_stream->Position;
			int num2 = this->Read();
			m_stream->Position = position;
			return num2;
		}

		int BinaryReader::Read()
		{
			return InternalReadOneChar();
		}

		int BinaryReader::Read(byte buffer[], int index, int count)
		{
			if(!m_stream)
			{
				if (m_disposed)
				{
#if DEBUG
					printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "BinaryReader", "Cannot read from a closed BinaryReader.");
#endif
					return -1;
				}

#if DEBUG
				printf("IO in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Stream is invalid");
#endif
			}
			
			if (!buffer)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "buffer");
#endif
				return -1;
			}
			
			if (index < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "index is less than 0");
#endif
				return -1;
			}
			
			if (count < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "count is less than 0");
#endif
				return -1;
			}

			if (Array::Length(buffer) < index + count)
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "buffer is too small");
#endif
				return -1;
			}

			int bytes_read = m_stream->Read(buffer, index, count);

			return(bytes_read);
		}

		int BinaryReader::Read(char buffer[], int index, int count)
		{
			if (m_disposed)
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "BinaryReader", "Cannot read from a closed BinaryReader.");
#endif
				return -1;
			}

			if (!buffer)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "buffer");
#endif
				return -1;
			}
			
			if (index < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "index is less than 0");
#endif
				return -1;
			}
			
			if (count < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "count is less than 0");
#endif
				return -1;
			}
			
			if ((Array::Length(buffer) - index) < count)
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "buffer is too small");
#endif
				return -1;
			}

			return InternalReadChars(buffer, index, count);
		}

		bool BinaryReader::ReadBoolean()
		{
			FillBuffer(1);
			return (m_buffer[0] != 0);
		}

		byte BinaryReader::ReadByte()
		{
			if (!m_stream)
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "BinaryReader", "Cannot read from a closed BinaryReader.");
#endif
				return 0;
			}

			int num = m_stream->ReadByte();
			if (num == -1)
			{
#if DEBUG
				printf("END_OF_STREAM in function %s, at line %i in file %s: %s", __FUNCTION__, __LINE__, __FILE__, "Attempted to read beyond End Of File.");
#endif
				return 0;
			}
			return (byte)num;
		}

		byte* BinaryReader::ReadBytes(int count)
		{
			if (count < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "count", "Non-negative number required.");
#endif
				return null;
			}

			if (!m_stream)
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "BinaryReader", "Cannot read from a closed BinaryReader.");
#endif
				return null;
			}

			byte* buffer = new byte[count];
			int offset = 0;
			do
			{
				int num2 = m_stream->Read(buffer, offset, count);
				if (num2 == 0)
					break;
				offset += num2;
				count -= num2;
			}
			while (count > 0);
			if (offset > Array::Length(buffer))
			{
				byte* dst = new byte[offset];
				Buffer::BlockCopy(buffer, 0, dst, 0, offset);
				buffer = dst;
			}
			return buffer;
		}

		char BinaryReader::ReadChar()
		{
			int num = this->Read();
			if (num == -1)
			{
#if DEBUG
				printf("END_OF_STREAM in function %s, at line %i in file %s: %s", __FUNCTION__, __LINE__, __FILE__, "Attempted to read beyond End Of File.");
#endif
				return -1;
			}

			return (char)num;
		}

		char* BinaryReader::ReadChars(int count)
		{
			if (count < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "count", "Non-negative number required.");
#endif
				return null;
			}

			if (!m_stream)
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "BinaryReader", "Cannot read from a closed BinaryReader.");
#endif
				return null;
			}

			char* buffer = new char[count];
			int num = InternalReadChars(buffer, 0, count);
			if (num != count)
			{
				char* dst = new char[num];
				Buffer::BlockCopy(buffer, 0, dst, 0, num);
				buffer = dst;
			}
			return buffer;
		}

		double BinaryReader::ReadDouble()
		{
			FillBuffer(8);
			uint num = (uint) (((m_buffer[0] | (m_buffer[1] << 8)) | (m_buffer[2] << 0x10)) | (m_buffer[3] << 0x18));
			uint num2 = (uint) (((m_buffer[4] | (m_buffer[5] << 8)) | (m_buffer[6] << 0x10)) | (m_buffer[7] << 0x18));
			ulong num3 = ((ulong)num2 << 0x20) | num;
			return *(((double*) &num3));
		}

		float BinaryReader::ReadSingle()
		{
			FillBuffer(4);
			uint num = (uint) (((m_buffer[0] | (m_buffer[1] << 8)) | (m_buffer[2] << 0x10)) | (m_buffer[3] << 0x18));
			return *(((float*) &num));
		}

		short BinaryReader::ReadInt16()
		{
			FillBuffer(2);
			return (short)(m_buffer[0] | (m_buffer[1] << 8));
		}

		int BinaryReader::ReadInt32()
		{
			FillBuffer(4);
			return (((m_buffer[0] | (m_buffer[1] << 8)) | (m_buffer[2] << 0x10)) | (m_buffer[3] << 0x18));
		}

		Int64 BinaryReader::ReadInt64()
		{
			FillBuffer(8);
			uint num = (uint)(((m_buffer[0] | (m_buffer[1] << 8)) | (m_buffer[2] << 0x10)) | (m_buffer[3] << 0x18));
			uint num2 = (uint)(((m_buffer[4] | (m_buffer[5] << 8)) | (m_buffer[6] << 0x10)) | (m_buffer[7] << 0x18));
			return (Int64) (((Int64)num2 << 0x20) | num);
		}

		sbyte BinaryReader::ReadSByte()
		{
			FillBuffer(1);
			return (sbyte)m_buffer[0];
		}

		String BinaryReader::ReadString()
		{
			short length = ReadInt16();
			char* buffer = ReadChars(length);
			return String(buffer, 0, length);
		}

		ushort BinaryReader::ReadUInt16()
		{
			FillBuffer(2);
			return (ushort) (m_buffer[0] | (m_buffer[1] << 8));
		}

		uint BinaryReader::ReadUInt32()
		{
			FillBuffer(4);
			return (uint)(((m_buffer[0] | (m_buffer[1] << 8)) | (m_buffer[2] << 0x10)) | (m_buffer[3] << 0x18));
		}

		ulong BinaryReader::ReadUInt64()
		{
			FillBuffer(8);
			uint num = (uint) (((m_buffer[0] | (m_buffer[1] << 8)) | (m_buffer[2] << 0x10)) | (m_buffer[3] << 0x18));
			uint num2 = (uint) (((m_buffer[4] | (m_buffer[5] << 8)) | (m_buffer[6] << 0x10)) | (m_buffer[7] << 0x18));
			return (((ulong)num2 << 0x20) | num);
		}
	}
}
