#include <System/Windows/Controls/TextBox.h>
#include <System/Windows/Media/SolidColorBrush.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			TextBox::TextBox()
				: _text(String::Empty)
			{
				Background = new SolidColorBrush(Color::Gray);
				Foreground = new SolidColorBrush(Color::Black);
			}

			String TextBox::getSelectedText() const
			{
				return _text.SubString(selectionStart, selectionLength);
			}

			String TextBox::getText() const
			{
				return _text;
			}

			void TextBox::setText(const String& value)
			{
				_text = value;
			}

			int TextBox::GetType() const
			{
			}

			void TextBox::Select(const int start, const int length)
			{
				selectionStart = start;
				selectionLength = length;
			}

			void TextBox::SelectAll()
			{
				Select(0, _text.Length);
			}

			const String& TextBox::ToString() const
			{
				return _text;
			}
		}
	}
}
