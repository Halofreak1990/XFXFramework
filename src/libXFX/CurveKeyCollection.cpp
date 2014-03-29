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

#include <CurveKeyCollection.h>
#include <System/Type.h>

namespace XFX
{
	const Type CurveKeyCollectionTypeInfo("CurveKeyCollection", "XFX::CurveKeyCollection", TypeCode::Object);

	int CurveKeyCollection::Count() const
	{
		return innerList.Count();
	}

	bool CurveKeyCollection::IsReadOnly() const
	{
		return isReadOnly;
	}

	CurveKeyCollection::CurveKeyCollection()
	{
	}

	void CurveKeyCollection::Add(const CurveKey& item)
	{
		if (innerList.Count() == 0)
		{
			innerList.Add(item);
			return;
		}

		for (int i = 0; i < innerList.Count(); i++)
		{
			if (item.getPosition() < innerList[i].getPosition())
			{
				innerList.Insert(i, item);
				return;
			}
		}

		innerList.Add(item);
	}

	void CurveKeyCollection::Clear()
	{
		innerList.Clear();
	}

	CurveKeyCollection CurveKeyCollection::Clone() const
	{
		CurveKeyCollection collection = CurveKeyCollection();

		collection.innerList.AddRange(&innerList);

		return collection;
	}

	bool CurveKeyCollection::Contains(const CurveKey& item) const
	{
		return innerList.Contains(item);
	}

	void CurveKeyCollection::CopyTo(CurveKey array[], const int arrayIndex) const
	{
		innerList.CopyTo(array, arrayIndex);
	}

	const Type& CurveKeyCollection::GetType()
	{
		return CurveKeyCollectionTypeInfo;
	}

	int CurveKeyCollection::IndexOf(const CurveKey& item) const
	{
		return innerList.IndexOf(item);
	}

	bool CurveKeyCollection::Remove(const CurveKey& item)
	{
		int index = IndexOf(item);

		if (index != -1)
		{
			RemoveAt(index);
			return true;
		}

		return false;
	}

	void CurveKeyCollection::RemoveAt(const int index)
	{
		innerList.RemoveAt(index);
	}

	CurveKey& CurveKeyCollection::operator[](int index) const
	{
		return innerList[index];
	}

	void CurveKeyCollection::set(int index, const CurveKey& value)
	{
		if (innerList[index].getPosition() == value.getPosition())
		{
			innerList[index] = value;
		}
		else
		{
			innerList.RemoveAt(index);
			innerList.Add(value);
		}
	}
}
