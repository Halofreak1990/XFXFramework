#ifndef _XSLTEXCEPTION_
#define _XSLTEXCEPTION_

#include "../../SystemException.h"

namespace System
{
	namespace Xml
	{
		namespace Xsl
		{
			/// <summary>
			/// The exception that is thrown when an error occurs while processing an XSLT transformation.
			/// </summary>
			class XsltException : SystemException
			{
			public:
				int LineNumber();
				int LinePosition();
				const char* SourceUri();
	
				XsltException();
				XsltException(const char *message);
				XsltException(const char *message, Exception &innerException);
			};
		}
	}
}

#endif //_XSLTEXCEPTION_
