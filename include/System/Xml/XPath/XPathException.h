/********************************************************
 *	XPathException.h									*
 *														*
 *	XFX XPathException definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_XML_XPATH_XPATHEXCEPTION_
#define _SYSTEM_XML_XPATH_XPATHEXCEPTION_

#include <System/Exception.h>

namespace System
{
	namespace Xml
	{
		namespace XPath
		{
			// Provides the exception thrown when an error occurs while processing an XPath expression. 
			class XPathException : public SystemException
			{
			public:
				XPathException();
				XPathException(char *message);
				XPathException(char *message, Exception* innerException);
			};
		}
	}
}

#endif //_SYSTEM_XML_XPATH_XPATHEXCEPTION_
