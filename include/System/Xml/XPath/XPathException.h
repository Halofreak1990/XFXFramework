namespace System
{
	namespace Xml
	{
		namespace XPath
		{
			/// <summary>
			/// Provides the exception thrown when an error occurs while processing an XPath expression. 
			/// </summary>
			class XPathException : SystemException
			{
			public:
				XPathException();
				XPathException(const char *message);
				XPathException(const char *message, Exception &innerException);
			};
		}
	}
}
