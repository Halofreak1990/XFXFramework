// Copyright (C) XFX Team
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

#include <System/Windows/GridLength.h>
#include <System/String.h>
#include <System/Type.h>

namespace System
{
	namespace Windows
	{
		const GridLength GridLength::Auto(0, GridUnitType::Auto);

		const Type GridLengthTypeInfo("GridLength", "System::Windows::GridLength", TypeCode::Object);

		GridUnitType_t GridLength::getGridUnitType() const
		{
			return gridUnitType;
		}

		int GridLength::getValue() const
		{
			return value;
		}

		bool GridLength::IsAbsolute() const
		{
			return gridUnitType == GridUnitType::Pixel;
		}

		bool GridLength::IsAuto() const
		{
			return gridUnitType == GridUnitType::Auto;
		}

		bool GridLength::IsStar() const
		{
			return gridUnitType == GridUnitType::Star;
		}

		GridLength::GridLength()
			: value(0), gridUnitType(GridUnitType::Auto)
		{
		}

		GridLength::GridLength(const int pixels)
			: value(pixels), gridUnitType(GridUnitType::Pixel)
		{
		}

		GridLength::GridLength(const int value, const GridUnitType_t unitType)
			: value(value), gridUnitType(unitType)
		{
		}

		GridLength::GridLength(const GridLength &obj)
			: value(obj.value), gridUnitType(obj.gridUnitType)
		{
		}

		bool GridLength::Equals(Object const * const obj) const
		{
			return is(obj, this) ? *this == *(GridLength *)obj : false;
		}

		bool GridLength::Equals(const GridLength other) const
		{
			return (*this == other);
		}

		int GridLength::GetHashCode() const
		{
			return value + gridUnitType;
		}

		const Type& GridLength::GetType()
		{
			return GridLengthTypeInfo;
		}

		const String GridLength::ToString() const
		{
			if (gridUnitType == GridUnitType::Auto)
				return "Auto";
			if (gridUnitType == GridUnitType::Star)
				return "*";
			return String::Format("%i", value);
		}

		bool GridLength::operator ==(const GridLength& right) const
		{
			if (gridUnitType == right.gridUnitType)
			{
				return (value == right.value);
			}
			return false;
		}

		bool GridLength::operator !=(const GridLength& right) const
		{
			return ((gridUnitType != right.gridUnitType) || (value != right.value));
		}
	}
}
