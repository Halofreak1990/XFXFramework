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

#include <System/DateTime.h>
#include <System/String.h>
#include <System/IO/File.h>
#include <System/IO/FileStream.h>
#include <System/IO/Path.h>
#include <System/IO/StreamReader.h>
#include <System/IO/StreamWriter.h>

#if ENABLE_XBOX
#include <xboxkrnl/xboxkrnl.h>
#else
#endif

#include <sassert.h>

#if DEBUG
#include <stdio.h>
#endif

namespace System
{
	namespace IO
	{
		StreamWriter File::AppendText(char* path)
		{
			return StreamWriter(path, true);
		}

		void File::Copy(char* sourceFileName, char* destFileName)
		{
			Copy(sourceFileName, destFileName, false);
		}

		void File::Copy(char* sourceFileName, char* destFileName, bool overwrite)
		{
			sassert(!(!overwrite && Exists(destFileName)), "File specified in 'destFileName' already exists.");

			//! Copy the file
			int ret;
			int sourceHandle;
			int destHandle;
			UInt32 length;
			void *buffer;
			ret = XCreateFile(&sourceHandle, sourceFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);
			if(ret == 0)
			{
				XGetFileSize(sourceHandle, &length);
				buffer = MmAllocateContiguousMemory((int)length);
				XReadFile(sourceHandle, buffer, length, NULL);
				XCloseHandle(sourceHandle);
				XCreateFile(&destHandle, destFileName, GENERIC_WRITE, FILE_SHARE_WRITE, CREATE_NEW, FILE_ATTRIBUTE_NORMAL);
				XWriteFile(destHandle, buffer, length, NULL);
				XCloseHandle(destHandle);
			}
		}

		FileStream File::Create(char* path)
		{
			return FileStream(path, FileMode::CreateNew, FileAccess::ReadWrite, FileShare::None);
		}

		FileStream File::Create(char* path, int bufferSize)
		{
			return FileStream(path, FileMode::CreateNew, FileAccess::ReadWrite, FileShare::None, bufferSize);
		}

		StreamWriter File::CreateText(char* path)
		{
			return StreamWriter(path, false);
		}

		void File::Delete(char* path)
		{
			XDeleteFile(path);
		}

		bool File::Exists(char* path)
		{
			bool flag = false;
			if (String::IsNullOrEmpty(path))
				return false;

			path = Path::GetFullPath(path);
			XBOX_FIND_DATA data;
			flag = ((FileAttributeInfo(path, &data, false, false) == 0) && (data.dwFileAttributes != -1) && ((data.dwFileAttributes & 0x10) == 0));
			
			return flag;			
		}

		DateTime File::GetCreationTime(char* path)
		{
			XBOX_FIND_DATA data;
			path = Path::GetFullPath(path);
			FileAttributeInfo(path, &data, false, false);
			return DateTime::FromFileTimeUtc(data.ftCreationTime);
		}

		DateTime File::GetLastAccessTime(char* path)
		{
			XBOX_FIND_DATA data;
			path = Path::GetFullPath(path);
			FileAttributeInfo(path, &data, false, false);
			return DateTime::FromFileTimeUtc(data.ftLastAccessTime);
		}

		DateTime File::GetLastWriteTime(char* path)
		{
			XBOX_FIND_DATA data;
			path = Path::GetFullPath(path);
			FileAttributeInfo(path, &data, false, false);
			return DateTime::FromFileTimeUtc(data.ftLastWriteTime);
		}

		void File::Move(char* sourceFileName, char* destFileName)
		{
			char* fullPath = Path::GetFullPath(sourceFileName);
			char* dst = Path::GetFullPath(destFileName);

			// TODO: Actually MOVE the file
			// I suspect MoveFile is simply copying the file, and then removing the source file.
		}

		FileStream File::Open(char* path, FileMode_t mode)
		{
			return Open(path, mode, (mode == FileMode::Append) ? FileAccess::Write : FileAccess::ReadWrite, FileShare::None);
		}

		FileStream File::Open(char* path, FileMode_t mode, FileAccess_t access)
		{
			return FileStream(path, mode, access, FileShare::None);
		}

		FileStream File::Open(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share)
		{
			return FileStream(path, mode, access, share);
		}

		FileStream File::OpenRead(char* path)
		{
			return FileStream(path, FileMode::Open, FileAccess::Read, FileShare::Read);
		}

		StreamReader File::OpenText(char* path)
		{
			return StreamReader(path);
		}
		
		FileStream File::OpenWrite(char* path)
		{
			return FileStream(path, FileMode::OpenOrCreate, FileAccess::Write, FileShare::None);
		}
	}
}
