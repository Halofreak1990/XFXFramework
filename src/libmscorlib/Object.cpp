// Copyright (C) XFX Team
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

#include <System/Object.h>
#include <System/String.h>
#include <System/Type.h>
#include <string.h>

namespace System
{
	const Type ObjectTypeInfo("Object", "System::Object", TypeCode::Object);

	bool Object::Equals(Object const * const obj) const
	{
		return is(this, obj);
	}

	bool Object::Equals(Object const * const objA, Object const * const objB)
	{
		return ((objA == objB) || ((objA) && (objB) && objA->Equals(objB)) || ((!objA) && (!objB)));
	}

	int Object::GetHashCode() const
	{
		return (int)this;
	}

	const Type& Object::GetType()
	{
		return ObjectTypeInfo;
	}

	bool Object::ReferenceEquals(const Object& objA, const Object& objB)
	{
		return (&objA == &objB);
	}

	const String Object::ToString() const
	{
		return "Object";
	}

	bool is(Object const * const obj1, Object const * const obj2)
	{
		if ((obj1 == NULL) && (obj2 == NULL))
			return true;

		if ((obj1 != NULL) && (obj2 != NULL))
		{
			return (obj1->GetType() == obj2->GetType());
		}

		return false;
	}

	template <typename T, typename U>
	U * as(T * const source)
	{
		int typeCode = T::GetType(); // make sure source is an Object
		int destTypeCode = U::GetType(); // same here, but now for U

		return (typeCode == destTypeCode) ? (U *)source : NULL;
	}
}
