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

#include <System/Array.h>
#include <System/Buffer.h>
#include <System/IO/FileStream.h>
#include <System/IO/StreamWriter.h>
#include <System/Text/UTF8Encoding.h>

#if DEBUG
#include <stdio.h>
#endif

namespace System
{
	namespace IO
	{
		const int StreamWriter::DefaultBufferSize = 0x400;
		Encoding StreamWriter::_UTF8NoBOM = UTF8Encoding(false, true);

		StreamWriter::StreamWriter(Stream* stream)
			: TextWriter(null)
		{
			if (!stream)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "stream");
#endif
				return;
			}
			if (!stream->CanWrite())
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Stream does not support writing.");
#endif
				return;
			}
			Init(stream, _UTF8NoBOM, DefaultBufferSize);
		}

		StreamWriter::StreamWriter(char* path)
			: TextWriter(null)
		{
			if (!path)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "path");
#endif
				return;
			}
			Stream* stream = CreateFile(path, true);
			Init(stream, _UTF8NoBOM, 0x400);
		}

		StreamWriter::StreamWriter(Stream* stream, Encoding encoding)
			: TextWriter(null)
		{
			if (!stream)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "stream");
#endif
				return;
			}
			if (!stream->CanWrite())
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Stream does not support writing.");
#endif
				return;
			}
			Init(stream, encoding, DefaultBufferSize);
		}

		StreamWriter::StreamWriter(char* path, bool append)
			: TextWriter(null)
		{
			if (!path)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "path");
#endif
				return;
			}
			Stream* stream = CreateFile(path, append);
			Init(stream, _UTF8NoBOM, 0x400);
		}

		StreamWriter::StreamWriter(Stream* stream, Encoding encoding, int bufferSize)
			: TextWriter(null)
		{
			if (!stream)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "stream");
#endif
				return;
			}
			if (!stream->CanWrite())
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Stream does not support writing.");
#endif
				return;
			}
			if (bufferSize < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "bufferSize", "Non-negative number required.");
#endif
				return;
			}
			Init(stream, encoding, bufferSize);
		}

		StreamWriter::StreamWriter(char* path, bool append, Encoding encoding)
			: TextWriter(null)
		{
			if (!path)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "path");
#endif
				return;
			}
			Stream* stream = CreateFile(path, append);
			Init(stream, encoding, 0x400);
		}

		StreamWriter::StreamWriter(char* path, bool append, Encoding encoding, int bufferSize)
			: TextWriter(null)
		{
			if (!path)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "path");
#endif
				return;
			}
			Stream* stream = CreateFile(path, append);
			Init(stream, encoding, bufferSize);
		}

		void StreamWriter::Close()
		{
			Dispose(true);
		}

		Stream* StreamWriter::CreateFile(char* path, bool append)
		{
			return new FileStream(path, append ? FileMode::Append : FileMode::Create, FileAccess::Write, FileShare::Read, 0x1000, FileOptions::SequentialScan);
		}

		void StreamWriter::Dispose(bool disposing)
		{
			if(!closable)
			{
				Flush(true, true);
			}
		}

		void StreamWriter::Flush()
		{
			Flush(true, true);
		}

		void StreamWriter::Flush(bool flushStream, bool flushEncoder)
		{
			if (((charPos != 0) || flushStream) || flushEncoder)
			{
				if (!haveWrittenPreamble)
				{
					haveWrittenPreamble = true;
					byte* preamble = encoding.GetPreamble();
					if (Array::Length(preamble) > 0)
					{
						stream->Write(preamble, 0, Array::Length(preamble));
					}
				}
				int count = encoder.GetBytes(charBuffer, 0, charPos, byteBuffer, 0, flushEncoder);
				charPos = 0;
				if (count > 0)
				{
					stream->Write(byteBuffer, 0, count);
				}
				if(flushStream)
				{
					stream->Flush();
				}
			}
		}

		void StreamWriter::Init(Stream* stream, Encoding encoding, int bufferSize)
		{
			this->stream = stream;
			this->encoding = encoding;
			encoder = this->encoding.GetEncoder();
			if (bufferSize < 0x80)
			{
				bufferSize = 0x80;
			}
			charBuffer = new char[bufferSize];
			byteBuffer = new byte[encoding.GetMaxByteCount(bufferSize)];
			charLen = bufferSize;
			if (stream->CanSeek() && (stream->Position > 0L))
			{
				haveWrittenPreamble = true;
			}
			closable = true;
		}

		void StreamWriter::Write(char value)
		{
			if(charPos == charLen)
			{
				Flush(false, false);
			}
			charBuffer[charPos] = value;
			charPos++;
			if (autoFlush)
			{
				Flush(true, false);
			}
		}

		void StreamWriter::Write(char buffer[])
		{
			if (buffer)
			{
				int num3;
				int num = 0;
				for (int i = Array::Length(buffer); i > 0; i -= num3)
				{
					if (charPos == charLen)
					{
						Flush(false, false);
					}
					num3 = charLen - charPos;
					if (num3 > i)
					{
						num3 = i;
					}
					Buffer::BlockCopy(buffer, num * 2, charBuffer, charPos * 2, num3 * 2);
					charPos += num3;
					num += num3;
				}
				if (autoFlush)
				{
					Flush(true, false);
				}
			}
		}
	}
}
