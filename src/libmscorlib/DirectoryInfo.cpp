// Copyright (C) Halofreak_1990
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

#include <System/Collections/Generic/List.h>
#include <System/FrameworkResources.h>
#include <System/IO/Directory.h>
#include <System/IO/DirectoryInfo.h>
#include <System/String.h>

#include <string.h>

#include <sassert.h>

using namespace System::Collections::Generic;

namespace System
{
	namespace IO
	{
		DirectoryInfo::DirectoryInfo(const String& path)
		{
			sassert(path != null, FrameworkResources::ArgumentNull_Path);

			if ((path.Length == 2) && (path[1] == ':'))
			{
				OriginalPath = ".";
			}
			else
			{
				OriginalPath = path;
			}
		}

		void DirectoryInfo::Create()
		{
		}

		DirectoryInfo DirectoryInfo::CreateSubDirectory(const String& path)
		{
			
		}

		void DirectoryInfo::Delete()
		{
			Directory::Delete(FullPath, false);
		}

		void DirectoryInfo::Delete(const bool recursive)
		{
			Directory::Delete(FullPath, recursive);
		}

		DirectoryInfo* DirectoryInfo::GetDirectories()
		{
			return GetDirectories("*");
		}

		DirectoryInfo* DirectoryInfo::GetDirectories(const String& searchPattern)
		{
			sassert(!String::IsNullOrEmpty(searchPattern), String::Format("searchPattern; %s", FrameworkResources::ArgumentNull_Generic));

			List<DirectoryInfo> infos = List<DirectoryInfo>();

			//! TODO: Implement

			return infos.ToArray();
		}

		bool DirectoryInfo::operator !=(const DirectoryInfo& right) const
		{
			return ((strncmp(current, right.current, strlen(current)) != 0) ||
				(strncmp(parent, right.parent, strlen(parent)) != 0));
		}

		bool DirectoryInfo::operator ==(const DirectoryInfo& right) const
		{
			return ((strncmp(current, right.current, strlen(current)) == 0) &&
				(strncmp(parent, right.parent, strlen(parent)) == 0));
		}
	}
}
