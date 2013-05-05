#pragma once

#include <System/Windows/FrameworkElement.h>
#include <System/Windows/Controls/UIElementCollection.h>
#include <System/Windows/Media/Brush.h>

using namespace System::Windows::Media;

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			// Provides a base class for all System::Windows::Controls::Panel elements. Use System::Windows::Controls::Panel elements to position and arrange child objects in applications.
			class Panel : public FrameworkElement
			{
			protected:
				Panel();

			public:
				Brush* Background;
				UIElementCollection Children;
				bool IsItemsHost() const;

				virtual ~Panel();

				int GetType() const;

				bool operator==(const Panel& right) const;
				bool operator!=(const Panel& right) const;
			};
		}
	}
}
