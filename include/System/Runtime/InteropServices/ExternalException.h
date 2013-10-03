/*****************************************************************************
 *	ExternalException.h 													 *
 *																			 *
 *	System::Runtime::InteropServices::ExternalException definition file.	 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_RUNTIME_INTEROPSERVICES_ExternalException_
#define _SYSTEM_RUNTIME_INTEROPSERVICES_ExternalException_

#include <System/Exception.h>

namespace System
{
	namespace Runtime
	{
		namespace InteropServices
		{
			/**
			 * The base exception type for all COM interop exceptions and structured exception handling (SEH) exceptions.
			 */
			class ExternalException : public SystemException
			{
			public:
				ExternalException();
				ExternalException(const String& message);
				ExternalException(const String& message, Exception * const inner);
			};
		}
	}
}

#endif //_SYSTEM_RUNTIME_INTEROPSERVICES_ExternalException_
