
#include <System/Types.h>

namespace System
{
	namespace Xml
	{
		namespace XPath
		{
			class XPathNavigator;

			// Provides an accessor to the System::Xml::XPath::XPathNavigator class.
			interface IXPathNavigable
			{
			public:
				// Returns a new System.Xml.XPath.XPathNavigator object.
				virtual XPathNavigator* CreateNavigator();

				virtual ~IXPathNavigable() { }
			};
		}
	}
}
