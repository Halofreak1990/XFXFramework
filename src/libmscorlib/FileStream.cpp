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

#include <System/FrameworkResources.h>
#include <System/String.h>
#include <System/IO/FileStream.h>

extern "C"
{
#include <hal/fileio.h>
}

#include <sassert.h>

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

		long long FileStream::Length()
		{
			sassert(handle != -1, FrameworkResources::ObjectDisposed_FileClosed);

			sassert(canSeek, FrameworkResources::NotSupported_UnseekableStream);

			uint length;
			if(XGetFileSize(handle, &length) != STATUS_SUCCESS)
			{
				//printf("IO in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Could not determine file size. The file may be corrupt.");
				return -1;
			}

			if ((_writePos > 0) && ((_pos + _writePos) > length))
	        {
				length = _writePos + _pos;
			}
			return length;
		}

		long long FileStream::getPosition()
		{
			sassert(handle != -1, FrameworkResources::ObjectDisposed_FileClosed);

			sassert(canSeek, FrameworkResources::NotSupported_UnseekableStream);

			return (_pos + ((_readPos - _readLen) + _writePos));
		}

		void FileStream::setPosition(long long newPosition)
		{
			sassert(canSeek, FrameworkResources::NotSupported_UnseekableStream);

			if(newPosition < 0)
			{
				//printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "newPosition", "Attempt to set the position to a negative value.");
				return;
			}

			Seek(newPosition, SeekOrigin::Begin);
		}

		FileStream::FileStream()
		{
			handle = -1;
		}

		FileStream::FileStream(const String& path, const FileMode_t mode)
		{
			sassert(!String::IsNullOrEmpty(path), FrameworkResources::ArgumentNull_Path);

			_access = (mode == FileMode::Append ? FileAccess::Write : FileAccess::ReadWrite);

			XCreateFile(&handle, const_cast<char *>(path.ToString()), _access, FileShare::Read, mode, FILE_ATTRIBUTE_NORMAL);
		}

		FileStream::FileStream(const String& path, const FileMode_t mode, const FileAccess_t access)
		{
			sassert(!String::IsNullOrEmpty(path), FrameworkResources::ArgumentNull_Path);

			_access = access;

			XCreateFile(&handle, const_cast<char *>(path.ToString()), access, FILE_SHARE_READ | FILE_SHARE_WRITE, mode, FILE_ATTRIBUTE_NORMAL);
		}

		FileStream::FileStream(const String& path, const FileMode_t mode, const FileAccess_t access, const FileShare_t share)
		{
			sassert(!String::IsNullOrEmpty(path), FrameworkResources::ArgumentNull_Path);

			_access = access;

			XCreateFile(&handle, const_cast<char *>(path.ToString()), access, share, mode, FILE_ATTRIBUTE_NORMAL);
		}

		FileStream::FileStream(const String& path, const FileMode_t mode, const FileAccess_t access, const FileShare_t share, const int bufferSize)
		{
			sassert (bufferSize > 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "bufferSize"), FrameworkResources::ArgumentOutOfRange_NeedPosNum));

			XCreateFile(&handle, const_cast<char *>(path.ToString()), access, share, mode, FILE_ATTRIBUTE_NORMAL);
		}

		FileStream::FileStream(const String& path, const FileMode_t mode, const FileAccess_t access, const FileShare_t share, const int bufferSize, const bool useAsync)
		{
			sassert (bufferSize > 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "bufferSize"), FrameworkResources::ArgumentOutOfRange_NeedPosNum));

			XCreateFile(&handle, const_cast<char *>(path.ToString()), access, share, mode, FILE_ATTRIBUTE_NORMAL);
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
			sassert(handle != -1, FrameworkResources::ObjectDisposed_FileClosed);

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

		int FileStream::Read(byte array[], const int offset, const int count)
		{
			sassert(handle != -1, FrameworkResources::ObjectDisposed_FileClosed);

			sassert(array != null, String::Format("array; %s", FrameworkResources::ArgumentNull_Generic));

			sassert(CanRead(), FrameworkResources::NotSupported_UnreadableStream);

			int len = (sizeof(array)/sizeof(byte));

			sassert(offset >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "offset"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(count >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "count"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(offset < len, "destination offset is beyond array size");

			sassert(!(offset > (len - count)), "Reading would overrun buffer.");

			uint bytesRead;
			XReadFile(handle, &array[offset], count, &bytesRead);
			return bytesRead;
		}

		int FileStream::ReadByte()
		{
			byte data;
			uint bytesRead;
			XReadFile(handle, &data, 1, &bytesRead);

			if(bytesRead != 1)
				return -1;

			return data;
		}

		long long FileStream::Seek(const long long offset, const SeekOrigin_t origin)
		{
			sassert(handle != -1, FrameworkResources::ObjectDisposed_FileClosed);

			FILE_POSITION_INFORMATION	positionInfo;
			LARGE_INTEGER				targetPointer;
			IO_STATUS_BLOCK				ioStatusBlock;
			NTSTATUS					status;
			uint						filesize;
						
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

		void FileStream::SetLength(const long long value)
		{
			sassert(canSeek, FrameworkResources::NotSupported_UnseekableStream);

			sassert(CanWrite(), FrameworkResources::NotSupported_UnwritableStream);

			sassert(handle != -1, FrameworkResources::ObjectDisposed_FileClosed);

			sassert(value >= 0, String::Format("value; %s", FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			if (!canSeek || !CanWrite() || (handle == -1) || value < 0)
				return;

			Flush();

			if (getPosition() > value)
				setPosition(value);
		}

		void FileStream::Write(byte array[], const int offset, const int count)
		{
			sassert(handle != -1, FrameworkResources::ObjectDisposed_FileClosed);

			XWriteFile(handle, &array[offset], count, null);
		}

		void FileStream::WriteByte(byte value)
		{
			sassert(handle != -1, FrameworkResources::ObjectDisposed_FileClosed);

			XWriteFile(handle, &value, 1, null);
		}
	}
}
