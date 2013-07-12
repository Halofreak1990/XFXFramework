/*****************************************************************************
 *	XmlNode.h																 *
 *																			 *
 *	System::Xml::XmlNode definition file									 *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_XML_XMLNODE_
#define _SYSTEM_XML_XMLNODE_

#include <System/String.h>
#include <System/Xml/Enums.h>
#include <System/Xml/Schema/Interfaces.h>
#include <System/Xml/XPath/Interfaces.h>

using namespace System::Xml::Schema;
using namespace System::Xml::XPath;

namespace System
{
	class XmlAttributeCollection;
	class XmlDocument;
	class XmlElement;
	class XmlNamespaceManager;
	class XmlNodeList;
	class XmlWriter;

	namespace Xml
	{
		/**
		 * Represents a single node in the XML document.
		 */
		class XmlNode : public IXPathNavigable, public Object
		{
		public:
			virtual XmlAttributeCollection* getAttributes();
			virtual String getBaseURI();
			virtual XmlNodeList getChildNodes();
			virtual XmlNode* getFirstChild();
			virtual bool HasChildNodes();
			virtual String getInnerText();
			virtual void setInnerText(const String& value);
			virtual String getInnerXml();
			virtual void setInnerXml(const String& value);
			virtual bool IsReadOnly();
			virtual XmlNode* getLastChild();
			virtual String getLocalName() =0;
			virtual String getName() =0;
			virtual String getNamespaceURI();
			virtual XmlNode* getNextSibling();
			virtual XmlNodeType_t getNodeType() =0;
			virtual String getOuterXml();
			virtual XmlDocument* getOwnerDocument();
			virtual XmlNode* getParentNode();
			virtual String getPrefix();
			virtual void setPrefix(const String& value);
			virtual XmlNode* getPreviousSibling();
			virtual IXmlSchemaInfo* getSchemaInfo();
			//virtual XmlElement* operator[](const String& localname, const String& ns);
			virtual XmlElement* operator[](const String& name);
			virtual String getValue() const;
			virtual void setValue(const String& value);

			virtual XmlNode* AppendChild(XmlNode * const newChild);
			virtual XmlNode* CloneNode(bool deep) =0;
			XPathNavigator* CreateNavigator();
			virtual String GetNamespaceOfPrefix(const String& prefix);
			virtual String GetPrefixOfNamespace(const String& namespaceURI);
			static const Type& GetType();
			virtual XmlNode* InsertAfter(XmlNode* newChild, XmlNode* refChild);
			virtual XmlNode* InsertBefore(XmlNode* newChild, XmlNode* refChild);
			virtual void Normalize();
			virtual XmlNode* PrependChild(XmlNode* newChild);
			virtual void RemoveAll();
			virtual XmlNode* RemoveChild(XmlNode* oldChild);
			virtual XmlNode* ReplaceChild(XmlNode* newChild, XmlNode* oldChild);
			XmlNodeList SelectNodes(const String& xpath);
			XmlNodeList SelectNodes(const String& xpath, XmlNamespaceManager nsmgr);
			XmlNode* SelectSingleNode(const String& xpath);
			XmlNode* SelectSingleNode(const String& xpath, XmlNamespaceManager nsmgr);
			virtual bool Supports(const String& feature, const String& version);
			virtual void WriteContentTo(XmlWriter * const w) =0;
			virtual void WriteTo(XmlWriter * const w) =0;
		};
	}
}

#endif //_SYSTEM_XML_XMLNODE_
