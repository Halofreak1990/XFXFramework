#pragma once

#include <System/Windows/Controls/Control.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			class TextBox : public Control
			{
			private:
				int selectionLength;
				int selectionStart;
				String _text;

			public:
				// Gets or sets a value that determines if the user can change the text in the text box.
				bool IsReadOnly;
				String getSelectedText() const;
				String getText() const;
				void setText(const String& value);

				TextBox();

				int GetType() const;
				void Select(const int start, const int length);
				void SelectAll();
				const char* ToString() const;
			};
		}
	}
}
