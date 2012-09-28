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

#include <sassert.h>

namespace System
{
	namespace IO
	{
		const int StreamWriter::DefaultBufferSize = 0x400;

		StreamWriter::StreamWriter(Stream* stream)
			: TextWriter(null)
		{
			sassert(stream != null, String::Format("stream; %s", FrameworkResources::ArgumentNull_Generic));

			sassert(stream->CanWrite(), FrameworkResources::NotSupported_UnwritableStream);

			Init(stream, DefaultBufferSize);
		}

		StreamWriter::StreamWriter(const String& path)
			: TextWriter(null)
		{
			sassert(path != null, FrameworkResources::ArgumentNull_Path);
			Stream* stream = CreateFile(path, true);
			Init(stream, 0x400);
		}

		StreamWriter::StreamWriter(const String& path, const bool append)
			: TextWriter(null)
		{
			sassert(path != null, FrameworkResources::ArgumentNull_Path);

			Stream* stream = CreateFile(path, append);
			Init(stream, 0x400);
		}

		StreamWriter::StreamWriter(Stream* stream, const int bufferSize)
			: TextWriter(null)
		{
			sassert(stream != null, "stream cannot be null.");

			sassert(stream->CanWrite(), FrameworkResources::NotSupported_UnwritableStream);

			sassert(!(bufferSize < 0), "bufferSize must be non-negative.");

			Init(stream, bufferSize);
		}

		StreamWriter::StreamWriter(const String& path, const bool append, const int bufferSize)
			: TextWriter(null)
		{
			sassert(path != null, FrameworkResources::ArgumentNull_Path);

			Stream* stream = CreateFile(path, append);
			Init(stream, bufferSize);
		}

		void StreamWriter::Close()
		{
			Dispose(true);
		}

		Stream* StreamWriter::CreateFile(const String& path, const bool append)
		{
			return new FileStream(path, append ? FileMode::Append : FileMode::Create, FileAccess::Write, FileShare::Read, 0x1000, FileOptions::SequentialScan);
		}

		void StreamWriter::Dispose(bool disposing)
		{
			if(!closable)
			{
				Flush(true);
			}
		}

		void StreamWriter::Flush()
		{
			Flush(true);
		}

		void StreamWriter::Flush(bool flushStream)
		{
			if ((charPos != 0) || flushStream)
			{
				// TODO: calculate how many bytes to write out (calculate buffer contents)

				/*int count = encoder.GetBytes(charBuffer, 0, charPos, byteBuffer, 0, flushEncoder);
				charPos = 0;
				if (count > 0)
				{
					stream->Write(byteBuffer, 0, count);
				}*/
				if(flushStream)
				{
					stream->Flush();
				}
			}
		}

		void StreamWriter::Init(Stream* stream, const int bufferSize)
		{
			this->stream = stream;
			int bufSiz = bufferSize;

			if (bufSiz < 0x80)
			{
				bufSiz = 0x80;
			}
			charBuffer = new char[bufSiz];
			byteBuffer = new byte[bufSiz];
			charLen = bufSiz;
			if (stream->CanSeek() && (stream->Position > 0L))
			{
				haveWrittenPreamble = true;
			}
			closable = true;
		}

		void StreamWriter::Write(const char value)
		{
			if(charPos == charLen)
			{
				Flush(false);
			}
			charBuffer[charPos] = value;
			charPos++;
			if (autoFlush)
			{
				Flush(true);
			}
		}

		void StreamWriter::Write(const char buffer[], const int arrayIndex, const int count)
		{
			sassert(buffer != null, FrameworkResources::ArgumentNull_Buffer);

			for (int i = arrayIndex; i < (arrayIndex + count); i++)
			{
				Write(buffer[i]);
			}
		}

		void StreamWriter::Write(const String& value)
		{
			if (String::IsNullOrEmpty(value))
				return;
			
			Write(value.ToString(), 0, value.Length);
		}
	}
}
