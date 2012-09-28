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

#include <System/String.h>
#include <System/Version.h>

#include <sassert.h>

namespace System
{
	Version::Version(int major, int minor)
		: Build(0), Major(major), Minor(minor), Revision(0)
	{
	}

	Version::Version(int major, int minor, int build)
		: Build(build), Major(major), Minor(minor), Revision(0)
	{
	}
	
	Version::Version(int major, int minor, int build, int revision)
		: Build(build), Major(major), Minor(minor), Revision(revision)
	{
	}

	Version::Version(const Version &obj)
		: Build(obj.Build), Major(obj.Major), Minor(obj.Minor), Revision(obj.Revision)
	{
	}

	Version Version::Clone() const
	{
		return Version(Major, Minor, Build, Revision);
	}

	int Version::CompareTo(const Version value) const
	{
		if (*this < value)
			return -1;
		if (*this > value)
			return 1;
		return 0;
	}

	bool Version::Equals(const Version obj) const
	{
		return ((Build == obj.Build) && (Major == obj.Major) &&
				(Minor == obj.Minor) && (Revision == obj.Revision));
	}

	int Version::GetHashCode() const
	{
		return (Build ^ Major ^ Minor ^ Revision);
	}

	int Version::GetType() const
	{
	}

	const char* Version::ToString() const
	{
		return String::Format("%i.%i.%i.%i", Major, Minor, Build, Revision);
	}

	const char* Version::ToString(int fieldCount) const
	{
		switch(fieldCount)
		{
		case 0:
			return "";
			break;
		case 1:
			return String::Format("%i", Major);
			break;
		case 2:
			return String::Format("%i.%i", Major, Minor);
			break;
		case 3:
			return String::Format("%i.%i.%i", Major, Minor, Build);
			break;
		case 4:
			return String::Format("%i.%i.%i.%i", Major, Minor, Build, Revision);
			break;
		default:
			sassert(fieldCount <= 4, "fieldCount is out of range");
			return "";
		}
	}

	bool Version::operator !=(const Version other) const
	{
		return !Equals(other);
	}

	bool Version::operator <(const Version other) const
	{
		return ((Build < other.Build) && (Major < other.Major) &&
				(Minor < other.Minor) && (Revision < other.Revision));
	}

	bool Version::operator <=(const Version other) const
	{
		return ((Build <= other.Build) && (Major <= other.Major) &&
				(Minor <= other.Minor) && (Revision <= other.Revision));
	}

	bool Version::operator ==(const Version other) const
	{
		return Equals(other);
	}

	bool Version::operator >(const Version other) const
	{
		return ((Build > other.Build) && (Major > other.Major) &&
				(Minor > other.Minor) && (Revision > other.Revision));
	}

	bool Version::operator >=(const Version other) const
	{
		return ((Build >= other.Build) && (Major >= other.Major) &&
				(Minor >= other.Minor) && (Revision >= other.Revision));
	}
}
