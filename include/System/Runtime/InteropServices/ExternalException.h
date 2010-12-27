/********************************************************
 *	ExternalException.h									*
 *														*
 *	XFX ExternalException definition					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_RUNTIME_INTEROPSERVICES_
#define _SYSTEM_RUNTIME_INTEROPSERVICES_

#include <System/Exception.h>

namespace System
{
	namespace Runtime
	{
		namespace InteropServices
		{
			/// <summary>
			/// The base exception type for all COM interop exceptions and structured exception handling (SEH) exceptions.
			/// </summary>
			class ExternalException : public SystemException
			{
			public:
				ExternalException();
				ExternalException(char* message);
				ExternalException(char* message, Exception inner);
			};
		}
	}
}

#endif //_SYSTEM_RUNTIME_INTEROPSERVICES_
