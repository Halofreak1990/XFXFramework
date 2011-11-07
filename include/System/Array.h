/********************************************************
 *	Array.h												*
 *														*
 *	XFX Array class definition file						*
 *	Contains array helper methods						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_ARRAY_
#define _SYSTEM_ARRAY_

#include <System/Collections/Generic/Interfaces.h>

using namespace System::Collections::Generic;

#if DEBUG
#include <stdio.h>
#endif

namespace System
{
	class Array
	{
	public:
		template <class T>
		static int BinarySearch(T array[], int index, int length, T value, IComparer<T>* comparer)
		{
			return -1;
		}

		template <class T>
		static void Clear(T array[], int index, int length)
		{
			for(int i = index; i < (index + length); i++)
			{
				array[i] = null;
			}
		}

		template <class T>
		static void Copy(T sourceArray[], int sourceIndex, T destinationArray[], int destinationIndex, int length)
		{
			if (!sourceArray)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "sourceArray");
#endif
				return;
			}

			if (!destinationArray)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray");
#endif
				return;
			}

			if (sourceIndex < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "sourceIndex must be 0 or greater");
#endif
				return;
			}

			if (destinationIndex < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "destinationIndex must be 0 or greater");
#endif
				return;
			}

			if((sourceIndex + length) > Length(sourceArray))
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s\n", __FUNCTION__, __LINE__, __FILE__);
#endif
				return;
			}

			if((destinationIndex + length) > Length(destinationArray))
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s\n", __FUNCTION__, __LINE__, __FILE__);
#endif
				return;
			}

			for (int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
			{
				destinationArray[j] = sourceArray[i];
			}
		}

		template <class T>
		static int IndexOf(T array[], T value, int startIndex, int count)
		{
			return -1;
		}

		template <class T>
		static int Length(T array[])
		{
			if (!array)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "array");
#endif
				return 0;
			}
			return (sizeof(array)/sizeof(T));
		}

		template <class T>
		static void Reverse(T array[], int index, int length)
		{
			if (!array)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "array");
#endif
				return;
			}

			if ((Length(array) - index) < length)
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Offset and length were out of bounds for the array or count is greater than the number of elements from index to the end of the source collection.");
#endif
				return;
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
	};
}

#endif //_SYSTEM_ARRAY_
