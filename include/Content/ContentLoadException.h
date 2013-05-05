#ifndef _CONTENT_CONTENTLOADEXCEPTION_
#define _CONTENT_CONTENTLOADEXCEPTION_

#include <System/Exception.h>
#include <System/Types.h>

using namespace System;

namespace XFX
{
	namespace Content
	{
		class ContentLoadException : public Exception
		{
		public:
			ContentLoadException();
			ContentLoadException(char* message);
			ContentLoadException(char* message, Exception innerException);
		};
	}
}

#endif //_CONTENT_CONTENTLOADEXCEPTION_
