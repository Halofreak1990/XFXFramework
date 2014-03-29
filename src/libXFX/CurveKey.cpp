// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       software without specific prior written permission.
// 
// SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <CurveKey.h>
#include <System/Type.h>

namespace XFX
{
	const Type CurveKeyTypeInfo("CurveKey", "XFX::CurveKey", TypeCode::Object);

	float CurveKey::getPosition() const
	{
		return position;
	}

	CurveKey::CurveKey(float position, float value)
		: position(position), Continuity(CurveContinuity::Smooth), Value(value)
	{
	}

	CurveKey::CurveKey(float position, float value, float tangentIn, float tangentOut)
		: position(position), Continuity(CurveContinuity::Smooth), TangentIn(tangentIn), TangentOut(tangentOut), Value(value)
	{
	}

	CurveKey::CurveKey(float position, float value, float tangentIn, float tangentOut, CurveContinuity_t continuity)
		: position(position), Continuity(continuity), TangentIn(tangentIn), TangentOut(tangentOut), Value(value)
	{
	}

	CurveKey CurveKey::Clone()
	{
		return CurveKey(position, Value, TangentIn, TangentOut, Continuity);
	}

	int CurveKey::CompareTo(const CurveKey other) const
	{
		if (position > other.position)
		{
			return 1;
		}
		else if (position < other.position)
		{
			return -1;
		}

		return 0;
	}

	bool CurveKey::Equals(Object const * const obj) const
	{
		return is(obj, this) ? *this == *(CurveKey *)obj : false;
	}

	bool CurveKey::Equals(const CurveKey other) const
	{
		return *this == other;
	}

	int CurveKey::GetHashCode() const
	{
		return (int)position ^ (int)Value ^ (int)TangentIn ^ (int)TangentOut ^ (int)Continuity;
	}

	const Type& CurveKey::GetType()
	{
		return CurveKeyTypeInfo;
	}

	bool CurveKey::operator!=(const CurveKey& right) const
	{
		return ((position != right.position) ||
				(Value != right.Value) ||
				(TangentIn != right.TangentIn) ||
				(TangentOut != right.TangentOut) ||
				(Continuity != right.Continuity));
	}

	bool CurveKey::operator==(const CurveKey& right) const
	{
		return ((position == right.position) &&
				(Value == right.Value) &&
				(TangentIn == right.TangentIn) &&
				(TangentOut == right.TangentOut) &&
				(Continuity == right.Continuity));
	}
}
