#pragma once

#include <System/Windows/Controls/Primitives/ButtonBase.h>
#include <System/Nullable.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				// Base class for controls that can switch states, such as System::Windows::Controls::CheckBox and System::Windows::Controls::RadioButton.
				class ToggleButton : public ButtonBase
				{
				protected:
					void OnClick();
					void OnContentChanged(Object* oldContent, Object* newContent);
					virtual void OnToggle();

				public:
					Nullable<bool> IsChecked;
					bool IsThreeState;

					ToggleButton();
					virtual ~ToggleButton();

					int GetType() const;
					const char* ToString() const;

					bool operator==(const ToggleButton& right) const;
					bool operator!=(const ToggleButton& right) const;

					RoutedEventHandler Checked;
					RoutedEventHandler Indeterminate;
					RoutedEventHandler Unchecked;
				};
			}
		}
	}
}
