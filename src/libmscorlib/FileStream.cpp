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

#include <System/IO/FileStream.h>
#include <System/IO/IOException.h>

#if ENABLE_XBOX
extern "C" {
#include <hal/fileio.h>
}
#else
#endif

namespace System
{
	namespace IO
	{
		bool FileStream::CanRead()
		{
			return _access == FileAccess::Read || _access == FileAccess::ReadWrite;
		}

		bool FileStream::CanSeek()
		{
			return canSeek;
		}

		bool FileStream::CanWrite()
		{
			return _access == FileAccess::Write || _access == FileAccess::ReadWrite;
		}

		Int64 FileStream::Length()
		{
			if(handle == -1)
				throw ObjectDisposedException("FileStream", "The stream has been closed.");

			if(!canSeek)
				throw NotSupportedException("The stream does not support seeking.");

			Int64 length;
#if ENABLE_XBOX
			if(XGetFileSize(handle, (unsigned int *)length) != STATUS_SUCCESS)
				throw IOException("Could not determine file size. The file may be corrupt.");
#else
#endif
			if ((_writePos > 0) && ((_pos + _writePos) > length))
	        {
				length = _writePos + _pos;
			}
			return length;
		}

		Int64 FileStream::Position()
		{
			if (handle == -1)
				throw ObjectDisposedException("FileStream", "The stream has been closed.");

			if (!canSeek)
				throw NotSupportedException("The stream does not support seeking.");

			return (_pos + ((_readPos - _readLen) + _writePos));
		}

		void FileStream::Position(Int64 newPosition)
		{
			if(canSeek == false)
				throw NotSupportedException("The stream does not support seeking");

			if(newPosition < 0)
				throw ArgumentOutOfRangeException("newPosition", "Attempt to set the position to a negative value.");

			Seek(newPosition, SeekOrigin::Begin);
		}

		FileStream::FileStream()
		{
			handle = -1;
		}

		FileStream::FileStream(char* path, FileMode_t mode)
		{
			if(path == null || path == "")
				throw ArgumentNullException("path", "path was either NULL or an empty string.");

			_access = (mode == FileMode::Append ? FileAccess::Write : FileAccess::ReadWrite);
#if ENABLE_XBOX
			XCreateFile(&handle, path, _access, FileShare::Read, mode, FILE_ATTRIBUTE_NORMAL);
#else
#endif
		}

		FileStream::FileStream(char* path, FileMode_t mode, FileAccess_t access)
		{
			if(path == null || path == "")
				throw ArgumentNullException("path", "path was either NULL, or an empty string.");

			_access = access;
#if ENABLE_XBOX
			XCreateFile(&handle, path, access, FILE_SHARE_READ | FILE_SHARE_WRITE, mode, FILE_ATTRIBUTE_NORMAL);
#else
#endif
		}

		FileStream::FileStream(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share)
		{
			if(path == null || path == "")
				throw ArgumentNullException("path", "path was either NULL, or an empty string.");

#if ENABLE_XBOX
			XCreateFile(&handle, path, access, share, mode, FILE_ATTRIBUTE_NORMAL);
#else
#endif
		}

		FileStream::FileStream(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share, int bufferSize)
		{
			FileStream(path, mode, access, share, bufferSize, false);
		}

		FileStream::FileStream(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share, int bufferSize, bool useAsync)
		{
			if (bufferSize <= 0)
				throw ArgumentOutOfRangeException("bufferSize", "Positive number required.");

#if ENABLE_XBOX
			isAsync = useAsync;

			if(isAsync)
			{
			}
			else
			{
				XCreateFile(&handle, path, access, share, mode, FILE_ATTRIBUTE_NORMAL);
			}
#else
#endif
		}

		FileStream::~FileStream()
		{
			Dispose(false);
		}

		void FileStream::Dispose(bool disposing)
		{
			try
			{
				if((handle != -1) && (_writePos > 0))
				{
					FlushWrite(!disposing);
				}
			}
			catch(Exception)
			{	
			}
			if((handle != -1))
			{
				// ! Invalidate the handle
				handle = -1;
			}
		}

		void FileStream::Flush()
		{
			if(handle == -1)
				throw ObjectDisposedException("FileStream", "The stream has been closed.");

			if (_writePos > 0)
			{
				FlushWrite(false);
			}
			else if ((_readPos < _readLen) && canSeek)
			{
				FlushRead();
			}
			_readPos = 0;
		    _readLen = 0;
		}

		void FileStream::FlushWrite(bool calledFromFinalizer)
		{
			if (isAsync)
			{
				IAsyncResult asyncResult = BeginWrite(_buffer, 0, _writePos, null, null);
				if (!calledFromFinalizer)
				{
					EndWrite(asyncResult);
				}
			}
			else
			{
				Write(_buffer, 0, _writePos);
			}
			_writePos = 0;
		}

		int FileStream::Read(byte array[], int offset, int count)
		{
			if(handle == -1)
				throw ObjectDisposedException("FileStream", "The stream has been closed.");

			if(array == null)
				throw ArgumentNullException("array");

			if (!CanRead())
				throw NotSupportedException("Stream does not support reading");

			int len = (sizeof(array)/sizeof(byte));
			if (offset < 0)
				throw ArgumentOutOfRangeException("offset", "< 0");
			if (count < 0)
				throw ArgumentOutOfRangeException("count", "< 0");
			if (offset > len)
				throw ArgumentException("destination offset is beyond array size");
			// reordered to avoid possible integer overflow
			if (offset > len - count)
				throw ArgumentException("Reading would overrun buffer");

			if(isAsync)
			{
				IAsyncResult ares = BeginRead(array, offset, count, null, null);
				return EndRead(ares);
			}

#if ENABLE_XBOX
			UInt32 bytesRead;
			XReadFile(handle, &array[offset], count, &bytesRead);
			return bytesRead;
#else
#endif
		}

		int FileStream::ReadByte()
		{
			void* data;
			UInt32 bytesRead;
			XReadFile(handle, data, 1, &bytesRead);

			if(bytesRead != 1)
				return -1;

			return (int)data;
		}

		long long FileStream::Seek(long long offset, SeekOrigin_t origin)
		{
			if(handle == -1)
				throw ObjectDisposedException("FileStream", "The stream has been closed.");

#if ENABLE_XBOX
			FILE_POSITION_INFORMATION positionInfo;
			LARGE_INTEGER             targetPointer;
			IO_STATUS_BLOCK           ioStatusBlock;
			NTSTATUS                  status;
			UInt32                    filesize;
						
			// Calculate the target pointer
			switch (origin)
			{
			case SeekOrigin::Begin:      // From the beginning of the file
				targetPointer.QuadPart = offset;
				break;
			case SeekOrigin::Current:    // From the current position
				status = NtQueryInformationFile((void*)handle, &ioStatusBlock, &positionInfo, sizeof(positionInfo), FilePositionInformation);
				if (!NT_SUCCESS(status))
					return RtlNtStatusToDosError(status);
				targetPointer.QuadPart = positionInfo.CurrentByteOffset.QuadPart + offset;
				break;
			case SeekOrigin::End:       // From the end of the file
				status = XGetFileSize(handle, &filesize);
				if (!NT_SUCCESS(status))
					return RtlNtStatusToDosError(status);
				targetPointer.QuadPart -= offset;
				break;
			}
	
			// Fill in the new position information
			positionInfo.CurrentByteOffset.u.HighPart = targetPointer.u.HighPart;
			positionInfo.CurrentByteOffset.u.LowPart= targetPointer.u.LowPart;
	
			// Set the new position
			status = NtSetInformationFile((void*)handle, &ioStatusBlock, &positionInfo, sizeof(positionInfo), FilePositionInformation);
			if (!NT_SUCCESS(status))
				return RtlNtStatusToDosError(status);
			else
			{
				return targetPointer.QuadPart;
			}
#else
#endif
		}

		void FileStream::SetLength(long long value)
		{
			if(!CanSeek())
				throw NotSupportedException("The stream does not support seeking.");

			if(!CanWrite())
				throw NotSupportedException("The stream does not support writing.");

			if(value < 0)
				throw ArgumentOutOfRangeException("value is less than 0");

			Flush();

			//

			if (Position() > value)
				Position(value);
		}

		void FileStream::Write(byte array[], int offset, int count)
		{
			if(isAsync)
			{
				IAsyncResult asyncResult = BeginWrite(array, offset, count, null, null);
				EndWrite(asyncResult);
			}
			else
			{
#if ENABLE_XBOX
				XWriteFile(handle, &array[offset], count, null);
#else
#endif
			}
		}

		void FileStream::WriteByte(byte value)
		{
#if ENABLE_XBOX
			XWriteFile(handle, (void*)value, 1, null);
#else
#endif
		}
	}
}
