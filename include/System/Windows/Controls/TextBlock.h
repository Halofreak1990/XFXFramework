#ifndef _SYSTEM_WINDOWS_CONTROLS_TEXTBLOCK_
#define _SYSTEM_WINDOWS_CONTROLS_TEXTBLOCK_

#include <System/String.h>
#include <System/Windows/FrameworkElement.h>
#include <System/Windows/Thickness.h>
#include <System/Windows/Media/Brush.h>

using namespace System::Windows::Media;

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			// Provides a lightweight control for displaying small amounts of text.
			class TextBlock : public FrameworkElement
			{
			public:
				Brush* Foreground;
				Thickness Padding;
				String Text;

				TextBlock();
				~TextBlock();

				int GetType() const;
				const String& ToString() const;
			};
		}
	}
}

#endif //_SYSTEM_WINDOWS_CONTROLS_TEXTBLOCK_
