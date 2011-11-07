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

#include <System/String.h>
#include <System/IO/FileStream.h>

extern "C"
{
#include <hal/fileio.h>
}

#if DEBUG
#include <stdio.h>
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
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "FileStream", "The stream has been closed.");
#endif
				return -1;
			}

			if(!canSeek)
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "The stream does not support seeking.");
#endif
				return -1;
			}

			UInt32 length;
			if(XGetFileSize(handle, &length) != STATUS_SUCCESS)
			{
#if DEBUG
				printf("IO in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Could not determine file size. The file may be corrupt.");
#endif
				return -1;
			}

			if ((_writePos > 0) && ((_pos + _writePos) > length))
	        {
				length = _writePos + _pos;
			}
			return length;
		}

		Int64 FileStream::Position()
		{
			if (handle == -1)
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "FileStream", "The stream has been closed.");
#endif
				return -1;
			}

			if (!canSeek)
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "The stream does not support seeking.");
#endif
				return -1;
			}

			return (_pos + ((_readPos - _readLen) + _writePos));
		}

		void FileStream::Position(Int64 newPosition)
		{
			if(canSeek == false)
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "The stream does not support seeking.");
#endif
				return;
			}

			if(newPosition < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "newPosition", "Attempt to set the position to a negative value.");
#endif
				return;
			}

			Seek(newPosition, SeekOrigin::Begin);
		}

		FileStream::FileStream()
		{
			handle = -1;
		}

		FileStream::FileStream(char* path, FileMode_t mode)
		{
			if (String::IsNullOrEmpty(path))
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "path", "path was either NULL or an empty string.");
#endif
				handle = -1;
				return;
			}

			_access = (mode == FileMode::Append ? FileAccess::Write : FileAccess::ReadWrite);

			XCreateFile(&handle, path, _access, FileShare::Read, mode, FILE_ATTRIBUTE_NORMAL);
		}

		FileStream::FileStream(char* path, FileMode_t mode, FileAccess_t access)
		{
			if (String::IsNullOrEmpty(path))
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "path", "path was either NULL or an empty string.");
#endif
				handle = -1;
				return;
			}

			_access = access;

			XCreateFile(&handle, path, access, FILE_SHARE_READ | FILE_SHARE_WRITE, mode, FILE_ATTRIBUTE_NORMAL);
		}

		FileStream::FileStream(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share)
		{
			if (String::IsNullOrEmpty(path))
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "path", "path was either NULL or an empty string.");
#endif
				handle = -1;
				return;
			}

			_access = access;

			XCreateFile(&handle, path, access, share, mode, FILE_ATTRIBUTE_NORMAL);
		}

		FileStream::FileStream(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share, int bufferSize)
		{
			if (bufferSize <= 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "bufferSize", "Positive number required.");
#endif
				handle = -1;
				return;
			}

			XCreateFile(&handle, path, access, share, mode, FILE_ATTRIBUTE_NORMAL);
		}

		FileStream::FileStream(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share, int bufferSize, bool useAsync)
		{
			if (bufferSize <= 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "bufferSize", "Positive number required.");
#endif
				handle = -1;
				return;
			}

			XCreateFile(&handle, path, access, share, mode, FILE_ATTRIBUTE_NORMAL);
		}

		FileStream::~FileStream()
		{
			Dispose(false);
		}

		void FileStream::Dispose(bool disposing)
		{
			if((handle != -1) && (_writePos > 0))
			{
				FlushWrite(!disposing);
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
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s\n: %s\n", __FUNCTION__, __LINE__, __FILE__, "FileStream", "The stream has been closed.");
#endif
				return;
			}

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
			Write(_buffer, 0, _writePos);
			_writePos = 0;
		}

		int FileStream::Read(byte array[], int offset, int count)
		{
			if(handle == -1)
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s\n: %s\n", __FUNCTION__, __LINE__, __FILE__, "FileStream", "The stream has been closed.");
#endif
				return -1;
			}

			if(array == null)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "array");
#endif
				return -1;
			}

			if (!CanRead())
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Stream does not support reading");
#endif
				return -1;
			}

			int len = (sizeof(array)/sizeof(byte));
			if (offset < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "offset", "Non-negative number required.");
#endif
				return -1;
			}

			if (count < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "count", "Non-negative number required.");
#endif
				return -1;
			}
			if (offset > len)
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "destination offset is beyond array size");
#endif
				return -1;
			}

			if (offset > len - count)
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Reading would overrun buffer");
#endif
			}

			UInt32 bytesRead;
			XReadFile(handle, &array[offset], count, &bytesRead);
			return bytesRead;
		}

		int FileStream::ReadByte()
		{
			byte data;
			UInt32 bytesRead;
			XReadFile(handle, &data, 1, &bytesRead);

			if(bytesRead != 1)
				return -1;

			return (int)data;
		}

		long long FileStream::Seek(long long offset, SeekOrigin_t origin)
		{
			if(handle == -1)
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s\n: %s\n", __FUNCTION__, __LINE__, __FILE__, "FileStream", "The stream has been closed.");
#endif
				return -1;
			}

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
			positionInfo.CurrentByteOffset.u.LowPart = targetPointer.u.LowPart;
	
			// Set the new position
			status = NtSetInformationFile((void*)handle, &ioStatusBlock, &positionInfo, sizeof(positionInfo), FilePositionInformation);
			if (!NT_SUCCESS(status))
				return RtlNtStatusToDosError(status);
			else
			{
				return targetPointer.QuadPart;
			}
		}

		void FileStream::SetLength(long long value)
		{
			if(!CanSeek())
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "The stream does not support seeking.");
#endif
				return;
			}

			if(!CanWrite())
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "The stream does not support writing.");
#endif
				return;
			}

			if(value < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "value is less than 0");
#endif
				return;
			}

			Flush();

			if (Position() > value)
				Position(value);
		}

		void FileStream::Write(byte array[], int offset, int count)
		{
			XWriteFile(handle, &array[offset], count, null);
		}

		void FileStream::WriteByte(byte value)
		{
			XWriteFile(handle, &value, 1, null);
		}
	}
}
