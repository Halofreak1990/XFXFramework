#pragma once

#include <System/Windows/PresentationFrameworkCollection.h>
#include <System/Windows/UIElement.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			class UIElementCollection : public PresentationFrameworkCollection<UIElement*>
			{
			};
		}
	}
}
