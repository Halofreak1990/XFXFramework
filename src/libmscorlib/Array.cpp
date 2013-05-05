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

#include <System/Array.h>
#include <System/Collections/Generic/Comparer.h>
#include <System/Exception.h>
#include <System/Types.h>

namespace System
{
	template <class T>
	int Array::BinarySearch(T array[], int index, int length, T value, IComparer<T>* comparer)
	{
		try
		{
			if (comparer == null)
			{
				comparer = Comparer<T>::Default();
			}
			int num = index;
			int num2 = (index + length) - 1;
			while (num <= num2)
			{
				int num3 = num + ((num2 - num) >> 1);
				int num4 = comparer->Compare(array[num3], value);
				if (num4 == 0)
				{
					return num3;
				}
				if (num4 < 0)
				{
					num = num3 + 1;
				}
				else
				{
					num2 = num3 - 1;
				}
			}
			return ~num;
		}
		catch(Exception* exception)
		{
			throw InvalidOperationException("", exception);
		}
	}

	template <class T>
	void Array::Clear(T array[], int index, int length)
	{
		for(int i = index; i < (index+length); i++)
		{
			array[i] = null;
		}
	}

	template <class T>
	void Array::Copy(T sourceArray[], int sourceIndex, T destinationArray[], int destinationIndex, int length)
	{
		if((sourceArray == null) || (destinationArray == null))
			throw ArgumentNullException(sourceArray == null ? "sourceArray" : "destinationArray");

		if(sourceIndex < 0)
			throw IndexOutOfRangeException("sourceIndex must be 0 or greater");

		if(destinationIndex < 0)
			throw IndexOutOfRangeException("destinationIndex must be 0 or greater");

		if(length < 0)
			throw IndexOutOfRangeException("length must be 0 or greater");

		if((sourceIndex + length) > Length(sourceArray))
			throw ArgumentException();

		if((destinationIndex + length) > Length(destinationArray))
			throw ArgumentException();

		for(int i = 0; i < length; i++)
		{
			sourceArray[sourceIndex] = destinationArray[destinationIndex];
			sourceIndex++;
			destinationIndex++;
		}
	}

	template <class T>
	int Array::Length(T array[])
	{
		return (sizeof(array)/sizeof(T));
	}

	template <class T>
	void Array::Reverse(T array[], int index, int length)
	{
		if (array == null)
		{
			throw ArgumentNullException("array");
		}
		if ((Length(array) - index) < length)
		{
			throw ArgumentException("Offset and length were out of bounds for the array or count is greater than the number of elements from index to the end of the source collection.");
		}
		int num = index;
        	int num2 = (index + length) - 1;
		while (num < num2)
        	{
			T obj2 = array[num];
			array[num] = array[num2];
			array[num2] = obj2;
			num++;
        		num2--;
	        }
	}
}
