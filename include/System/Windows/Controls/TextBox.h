/*****************************************************************************
 *	TextBox.h																 *
 *																			 *
 *	System::Windows::Controls::TextBox definition file  					 *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_CONTROLS_TEXTBOX_
#define _SYSTEM_WINDOWS_CONTROLS_TEXTBOX_

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
				/**
				 * Gets a value that determines if the user can change the text in the text box.
				 */
				bool getIsReadOnly() const;
				/**
				 * Sets a value that determines if the user can change the text in the text box.
				 */
				void setIsReadOnly(const bool value);

				static const DependencyProperty<bool> IsReadOnlyProperty;

				String getSelectedText() const;
				String getText() const;
				void setText(const String& value);

				TextBox();

				static const Type& GetType();
				void Select(const int start, const int length);
				void SelectAll();
				const String ToString() const;
			};
		}
	}
}

#endif //_SYSTEM_WINDOWS_CONTROLS_TEXTBOX_
