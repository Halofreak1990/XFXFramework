/********************************************************
 *	XsltException.h										*
 *														*
 *	XFX XsltException definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_XML_XSLTEXCEPTION_
#define _SYSTEM_XML_XSLTEXCEPTION_

#include <System/Exception.h>

namespace System
{
	namespace Xml
	{
		namespace Xsl
		{
			/// <summary>
			/// The exception that is thrown when an error occurs while processing an XSLT transformation.
			/// </summary>
			class XsltException : public SystemException
			{
			public:
				int LineNumber(); // Gets the line number indicating where the error occurred in the style sheet.
				int LinePosition(); // Gets the line position indicating where the error occurred in the style sheet.
				const char* SourceUri(); // Gets the location path of the style sheet.
	
				XsltException();
				XsltException(char *message);
				XsltException(char *message, Exception* innerException);
			};
		}
	}
}

#endif //_SYSTEM_XML_XSLTEXCEPTION_
