/********************************************************
 *	KeyNotFoundException.h								*
 *														*
 *	XFX KeyNotFoundException class definition file		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_KEYNOTFOUNDEXCEPTION_
#define _SYSTEM_COLLECTIONS_GENERIC_KEYNOTFOUNDEXCEPTION_

#include <System/Exception.h>

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			/// <summary>
			/// The exception that is thrown when the key specified for accessing an element in a collection does not match any
			/// key in the collection.
			/// </summary>
			class KeyNotFoundException : public SystemException
			{
			public:
				KeyNotFoundException();
				KeyNotFoundException(char* message);
				KeyNotFoundException(char* message, Exception* innerException);
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_KEYNOTFOUNDEXCEPTION_
