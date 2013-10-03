/*****************************************************************************
 *	Enums.h 																 *
 *																			 *
 *	System::Xml::XPath Interfaces definition file.  						 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_XML_XPATH_XPATHNAVIGATOR_
#define _SYSTEM_XML_XPATH_XPATHNAVIGATOR_

#include <System/Types.h>

namespace System
{
	namespace Xml
	{
		namespace XPath
		{
			class XPathNavigator;

			/**
			 * Provides an accessor to the System::Xml::XPath::XPathNavigator class.
			 */
			interface IXPathNavigable
			{
			public:
				/**
				 * Returns a new System.Xml.XPath.XPathNavigator object.
				 */
				virtual XPathNavigator* CreateNavigator();

				virtual ~IXPathNavigable() { }
			};
		}
	}
}

#endif //_SYSTEM_XML_XPATH_XPATHNAVIGATOR_
