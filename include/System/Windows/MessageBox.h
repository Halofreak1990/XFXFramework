#pragma once

#include <System/Windows/Enums.h>

namespace System
{
	class String;

	namespace Windows
	{
		// Displays a message to the user and optionally prompts for a response.
		class MessageBox
		{
		private:
			MessageBox();
			MessageBox(const MessageBox &obj);

		public:
			// Displays a message box that contains the specified text and an OK button.
			static MessageBoxResult_t Show(const String& messageBoxText);
			// Displays a message box that contains the specified text, title bar caption, and response buttons.
			static MessageBoxResult_t Show(const String& messageBoxText, const String& caption, const MessageBoxButton_t button);
		};
	}
}
