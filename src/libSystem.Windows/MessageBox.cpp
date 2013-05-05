#include <System/Windows/MessageBox.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		MessageBoxResult_t MessageBox::Show(const String& messageBoxText)
		{
			return Show(messageBoxText, String::Empty, MessageBoxButton::Ok);
		}

		MessageBoxResult_t MessageBox::Show(const String& messageBoxText, const String& caption, const MessageBoxButton_t buttons)
		{
			//! TODO: implement
		}
	}
}
