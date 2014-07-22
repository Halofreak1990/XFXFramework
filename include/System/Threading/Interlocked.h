#ifndef _SYSTEM_THREADING_INTERLOCKED_
#define _SYSTEM_THREADING_INTERLOCKED_

#include <System/Types.h>

namespace System
{
	namespace Threading
	{
		class Interlocked
		{
		public:
			// Adds two 32-bit integers and replaces the first integer with the sum, as an atomic operation.
			//	location1
			//		A variable containing the first value to be added. The sum of the two values is stored in location1.
			//	value
			//		The value to be added to the integer at location1.
			//	Returns
			//		The new value stored at location1.
			static inline int Add(volatile int* const location1, const int value)
			{
				long retval = value;
				__asm__("lock; xaddl %[retval], %[location1]" : [retval] "+r" (retval) : [location1] "m" (*location1) : "memory");
				return retval;
			}

			// Compares two 32-bit signed integers for equality and, if they are equal, replaces one of the values.
			//	location1
			//		The destination, whose value is compared with comparand and possibly replaced.
			//	value
			//		The value that replaces the destination value if the comparison results in equality. 
			//	comparand
			//		The value that is compared to the value at location1. 
			//	Returns
			//		The original value in location1.
			static inline int CompareExchange(int location1, int value, int comparand)
			{
				long retval = comparand;
				__asm__("lock; cmpxchgl %k[value], %[location1]" : [retval] "+a" (retval) : [location1] "m" (*location1), [value] "q" (value): "memory");
				return retval;
			}

			// Compares two 64-bit signed integers for equality and, if they are equal, replaces one of the values.
			//	location1
			//		The destination, whose value is compared with comparand and possibly replaced.
			//	value
			//		The value that replaces the destination value if the comparison results in equality. 
			//	comparand
			//		The value that is compared to the value at location1. 
			//	Returns
			//		The original value in location1.
			static inline long long CompareExchange(volatile long long* const location1, const long long value, const long long comparand)
			{
				long long retval = comparand;

				__asm__
				(
					"cmpxchg8b %[location1]" :
					[retval] "+A" (retval) :
						[location1] "m" (*location1),
						"b" ((unsigned long)((Exchange >>  0) & 0xFFFFFFFF)),
						"c" ((unsigned long)((Exchange >> 32) & 0xFFFFFFFF)) :
					"memory"
				);

				return retval;
			}

			// Compares two platform-specific handles or pointers for equality and, if they are equal, replaces one of them.
			//	location1
			//		The destination pointer, whose value is compared with the value of comparand and possibly replaced by value. 
			//	value
			//		The pointer that replaces the destination value if the comparison results in equality.
			//	comparand
			//		The pointer that is compared to the value at location1.
			//	Returns
			//		The original value in location1.
			static inline void* CompareExchange(void * volatile * const location1, void * const value, void * const comparand)
			{
				void * retval = (void *)comparand;
				__asm__("lock; cmpxchgl %k[value], %[location1]" : [retval] "=a" (retval) : "[retval]" (retval), [location1] "m" (*location1), [value] "q" (value) : "memory");
				return retval;
			}

			// Decrements a specified variable and stores the result, as an atomic operation.
			//	location
			//		The variable whose value is to be decremented.
			//	Returns
			//		The decremented value.
			static inline long Decrement(volatile int * const location)
			{
				return Add(location, -1) - 1;
			}

			// Sets a 32-bit signed integer to a specified value and returns the original value, as an atomic operation.
			//	location1
			//		The variable to set to the specified value.
			//	value
			//		The value to which the location1 parameter is set.
			//	Returns
			//		The original value of location1.
			static inline int Exchange(volatile int * const location1, const int value)
			{
				int retval = value;
				__asm__("xchgl %[retval], %[location1]" : [retval] "+r" (retval) : [location1] "m" (*location1) : "memory");
				return retval;
			}

			// Sets a platform-specific handle or pointer to a specified value and returns the original value, as an atomic operation.
			//	location1
			//		The variable to set to the specified value.
			//	value
			//		The value to which the location1 parameter is set.
			//	Returns
			//		The original value of location1.
			static inline void* Exchange(void * volatile * const Target, void * const Value)
			{
				void * retval = Value;
				__asm__("xchgl %[retval], %[Target]" : [retval] "+r" (retval) : [Target] "m" (*Target) : "memory");
				return retval;
			}

			// Increments a specified variable and stores the result, as an atomic operation.
			//	location
			//		The variable whose value is to be incremented.
			//	Returns
			//		The incremented value.
			static inline int Increment(volatile int * const location)
			{
				return Add(location, 1) + 1;
			}
		};
	}
}

#endif //_SYSTEM_THREADING_INTERLOCKED_
