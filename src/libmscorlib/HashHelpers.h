/********************************************************
 *	HashHelpers.h										*
 *														*
 *	XFX HashHelpers class definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_COLLECTIONS_HASHHELPERS_
#define _SYSTEM_COLLECTIONS_HASHHELPERS_

namespace System
{
	namespace Collections
	{
		/// <summary>
		/// This helper class is not meant to be used by the end user.
		/// Only XFX source files should reference this class.
		/// </summary>
		class HashHelpers
		{
		private:
			static const int primes[];

			HashHelpers();

		public:
			static int GetPrime(int min);
			static bool IsPrime(int candidate);
		};
	}
}

#endif //_SYSTEM_COLLECTIONS_HASHHELPERS_
