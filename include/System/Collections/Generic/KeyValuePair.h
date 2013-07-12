/*****************************************************************************
 *	KeyValuePair.h															 *
 *																			 *
 *	XFX System::Collections::Generic::KeyValuePair structure definition file *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_KEYVALUEPAIR_
#define _SYSTEM_COLLECTIONS_GENERIC_KEYVALUEPAIR_

#include <System/Object.h>
#include <System/Type.h>

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			/**
			 * Defines a key/value pair that can be set or retrieved.
			 */
			template <class TKey, class TValue>
			struct KeyValuePair : public Object
			{
			public:
				const TKey Key;
				const TValue Value;

				KeyValuePair(const TKey& key, const TValue& value)
					: Key(key), Value(value)
				{
				}

				KeyValuePair(const KeyValuePair &obj)
					: Key(obj.Key), Value(obj.Value)
				{
				}

				const Type& GetType()
				{
					static const Type KeyValuePairTypeInfo("KeyValuePair", "System::Collections::Generic::KeyValuePair", TypeCode::Object, true);

					return KeyValuePairTypeInfo;
				}
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_KEYVALUEPAIR_
