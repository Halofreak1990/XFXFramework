/*****************************************************************************
 *	Enums.h 																 *
 *																			 *
 *	System::Xml::XPath Enumerations definition file.						 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_XML_XPATH_ENUMS_
#define _SYSTEM_XML_XPATH_ENUMS_

namespace System
{
	namespace Xml
	{
		namespace XPath
		{
			struct XmlCaseOrder
			{
				enum type
				{
					/**
					 * Ignore the case.
					 */
					None,
					/**
					 * Uppercase letters are sorted before lowercase letters.
					 */
					UpperFirst,
					/**
					 * Lowercase letters are sorted before uppercase letters.
					 */
					LowerFirst
				};
			};

			struct XmlDataType
			{
				enum type
				{
					/**
					 * Values are sorted alphabetically.
					 */
					Text = 1,
					/**
					 * Values are sorted numerically.
					 */
					Number
				};
			};

			struct XmlSortOrder
			{
				enum type
				{
					/**
					 * Nodes are sorted in ascending order. For example, if the numbers 1,2,3, and 4 are sorted in ascending order, they appear as 1,2,3,4.
					 */
					Ascending = 1,
					/**
					 * Nodes are sorted in descending order. For example, if the numbers 1,2,3, and 4 are sorted in descending order, they appear as, 4,3,2,1.
					 */
					Descending
				};
			};

			struct XPathNamespaceScope
			{
				enum type
				{
					/**
					 * Returns all namespaces defined in the scope of the current node. This includes the xmlns:xml namespace which is always declared implicitly. The order of the namespaces returned is not defined.
					 */
					All,
					/**
					 * Returns all namespaces defined in the scope of the current node, excluding the xmlns:xml namespace. The xmlns:xml namespace is always declared implicitly. The order of the namespaces returned is not defined.
					 */
					ExcludeXml,
					/**
					 * Returns all namespaces that are defined locally at the current node.
					 */
					Local
				};
			};

			struct XPathNodeType
			{
				enum type
				{
					/**
					 * The root node of the XML document or node tree.
					 */
					Root,
					/**
					 * An element, such as <element>.
					 */
					Element,
					/**
					 * An attribute, such as id='123'.
					 */
					Attribute,
					/**
					 * A namespace, such as xmlns="namespace".
					 */
					Namespace,
					/**
					 * The text content of a node. Equivalent to the Document Object Model (DOM) Text and CDATA node types. Contains at least one character.
					 */
					Text,
					/**
					 * A node with white space characters and xml:space set to preserve.
					 */
					SignificantWhitespace,
					/**
					 * A node with only white space characters and no significant white space. White space characters are #x20, #x9, #xD, or #xA.
					 */
					Whitespace,
					/**
					 * A processing instruction, such as <?pi test?>. This does not include XML declarations, which are not visible to the System::Xml::XPath::XPathNavigator class.
					 */
					ProcessingInstruction,
					/**
					 * A comment, such as <!-- my comment -->
					 */
					Comment,
					/**
					 * Any of the System::Xml::XPath::XPathNodeType node types.
					 */
					All
				};
			};

			struct XPathResultType
			{
				enum type
				{
					/**
					 * Any of the XPath node types.
					 */
					Any = 5,
					/**
					 * A System::Boolean true or false value.
					 */
					Boolean = 2,
					/**
					 * The expression does not evaluate to the correct XPath type.
					 */
					Error = 6,
					/**
					 * A tree fragment.
					 */
					Navigator = 1,
					/**
					 * A node collection.
					 */
					NodeSet = 3,
					/**
					 * A numeric value.
					 */
					Number = 0,
					/**
					 * A System::String value.
					 */
					String = 4,
				};
			};

			/**
			 * Specifies the sort order for uppercase and lowercase letters.
			 */
			typedef XmlCaseOrder::type			XmlCaseOrder_t;
			/**
			 * Specifies the data type used to determine sort order.
			 */
			typedef XmlDataType::type			XmlDataType_t;
			/**
			 * Specifies the sort order.
			 */
			typedef XmlSortOrder::type			XmlSortOrder_t;
			/**
			 * Defines the namespace scope.
			 */
			typedef XPathNamespaceScope::type	XPathNamespaceScope_t;
			/**
			 * Defines the XPath node types that can be returned from the System::Xml::XPath::XPathNavigator class.
			 */
			typedef XPathNodeType::type			XPathNodeType_t;
			/**
			 * Specifies the return type of the XPath expression.
			 */
			typedef XPathResultType::type		XPathResultType_t;
		}
	}
}

#endif //_SYSTEM_XML_XPATH_ENUMS_
