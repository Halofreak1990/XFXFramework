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

#include <System/Exception.h>
#include <System/String.h>
#include <System/Version.h>

namespace System
{
	int Version::Build()
	{
		return _build;
	}

	int Version::Major()
	{
		return _major;
	}

	int Version::Minor()
	{
		return _minor;
	}

	int Version::Revision()
	{
		return _revision;
	}

	Version::Version(int major, int minor)
	{
		_major = major;
		_minor = minor;
	}

	Version::Version(char* version)
	{
		
	}

	Version Version::Clone()
	{
		return Version(_major, _minor, _build, _revision);
	}

	bool Version::Equals(Version obj)
	{
		return ((_build == obj._build) && (_major == obj._major) &&
				(_minor == obj._minor) && (_revision == obj._revision));
	}

	int Version::GetHashCode()
	{
		return (_build ^ _major ^ _minor ^ _revision);
	}

	char* Version::ToString()
	{
		return String::Format("%d.%d.%d.%d", _major, _minor, _build, _revision);
	}

	char* Version::ToString(int fieldCount)
	{
		if(fieldCount <= 0 || fieldCount > 4)
			throw ArgumentOutOfRangeException("fieldCount");


	}

	bool Version::operator !=(Version other)
	{
		return !Equals(other);
	}

	bool Version::operator <(Version other)
	{
		return ((_build < other._build) && (_major < other._major) &&
				(_minor < other._minor) && (_revision < other._revision));
	}

	bool Version::operator <=(Version other)
	{
		return ((_build <= other._build) && (_major <= other._major) &&
				(_minor <= other._minor) && (_revision <= other._revision));
	}

	bool Version::operator ==(Version other)
	{
		return Equals(other);
	}

	bool Version::operator >(Version other)
	{
		return ((_build > other._build) && (_major > other._major) &&
				(_minor > other._minor) && (_revision > other._revision));
	}

	bool Version::operator >=(Version other)
	{
		return ((_build >= other._build) && (_major >= other._major) &&
				(_minor >= other._minor) && (_revision >= other._revision));
	}
}
