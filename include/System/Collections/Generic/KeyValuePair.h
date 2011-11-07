/********************************************************
 *	KeyValuePair.h										*
 *														*
 *	XFX KeyValuePair definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_KEYVALUEPAIR_
#define _SYSTEM_COLLECTIONS_GENERIC_KEYVALUEPAIR_

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			// Defines a key/value pair that can be set or retrieved.
			template <class TKey, class TValue>
			struct KeyValuePair
			{
			private:
				TKey _key;
				TValue _value;

			public:
				TKey Key();
				TValue Value();

				KeyValuePair(TKey key, TValue value);
				KeyValuePair(const KeyValuePair &obj); //! Copy constructor
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_KEYVALUEPAIR_
