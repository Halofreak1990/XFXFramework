#ifndef _SYSTEM_WINDOWS_CONTROLS_CONTENTCONTROL_
#define _SYSTEM_WINDOWS_CONTROLS_CONTENTCONTROL_

#include <System/String.h>
#include <System/Windows/Controls/Control.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			// Represents a control with a single piece of content. Controls such as Button, CheckBox, and ScrollViewer directly, or indirectly inherit from this class.
			class ContentControl : public Control
			{
			protected:
				virtual void AddChild(Object* value);
				virtual void AddText(const String& text);
				virtual void OnContentChanged(Object* oldContent, Object* newContent);
				virtual void OnContentStringFormatChanged(String& oldContentStringFormat, String& newContentStringFormat);

			public:
				Object* Content;
				String ContentStringFormat;
				bool HasContent() const;

				ContentControl();

				int GetType() const;
			};
		}
	}
}

#endif
