#ifndef _SYSTEM_XML_INTERFACES_
#define _SYSTEM_XML_INTERFACES_

#include <System/Collections/Generic/Interfaces.h>
#include <System/Types.h>
#include <System/Xml/Enums.h>

using namespace System::Collections::Generic;

namespace System
{
	namespace Xml
	{
		class XmlNode;

		/// <summary>
		/// Enables a class to return an System::Xml::XmlNode from the current context or position.
		/// </summary>
		interface IHasXmlNode
		{
		public:
			virtual XmlNode GetNode()=0;
		};

		/// <summary>
		/// Provides an interface to enable a class to return line and position information.
		/// </summary>
		interface IXmlLineInfo
		{
		public:
			virtual bool HasLineInfo()=0;

			virtual int LineNumber();
			virtual int LinePosition();
		};

		/// <summary>
		/// Provides read-only access to a set of prefix and namespace mappings.
		/// </summary>
		interface IXmlNamespaceResolver
		{
		public:
			virtual IDictionary<char*, char*>* GetNamespacesInScope(XmlNamespaceScope_t scope)=0;
			virtual char* LookupNamespace(char* prefix)=0;
			virtual char* LookupPrefix(char* namespaceName)=0;
		};
	}
}

#endif //_SYSTEM_XML_INTERFACES_
