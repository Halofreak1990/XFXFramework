/********************************************************
 *	Buffer.h											*
 *														*
 *	XFX Buffer class definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_BUFFER_
#define _SYSTEM_BUFFER_

#include "Types.h"

#if DEBUG
#include <stdio.h>
#endif

namespace System
{
	// Manipulates arrays of primitive types.
	class Buffer
	{
	public:
		template <class T>
		static void BlockCopy(const T src[], const int srcOffset, T dst[], const int dstOffset, const int count)
		{
			if (!src)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "src");
#endif
				return;
			}

			if (!dst)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "dst");
#endif
				return;
			}

			if (srcOffset < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "srcOffset", "Non-negative number required.");
#endif
				return;
			}

			if (dstOffset < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "dstOffset", "Non-negative number required.");
#endif
				return;
			}

			if (count < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "count", "Non-negative number required.");
#endif
				return;
			}
			
			if ((srcOffset > ByteLength(src) - count) || (dstOffset > ByteLength(dst) - count))
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Offset and length were out of bounds for the array or count is greater than the number of elements from index to the end of the source collection.");
#endif
				return;
			}

			for(int i = srcOffset, j = dstOffset; i < (srcOffset + count); i++, j++)
			{
				dst[j] = src[i];
			}
		}

		template <class T>
		static int ByteLength(const T array[])
		{
			return sizeof(array);
		}

		template <class T>
		static byte GetByte(const T array[], const int index)
		{
			if (index < 0 || index >= ByteLength(array))
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "index", "Value must be non-negative and less than the size of the collection.");
#endif
			}

			return ((byte *) &array[index]);
		}

		template <class T>
		static void SetByte(T array[], const int index, const byte value)
		{
			if (index < 0 || index >= ByteLength(array))
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "index", "Value must be non-negative and less than the size of the collection.");
#endif
				return;
			}
		}
	};
}

#endif //_SYSTEM_BUFFER_
