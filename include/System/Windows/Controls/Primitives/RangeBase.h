#ifndef _SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_RANGEBASE_
#define _SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_RANGEBASE_

#include <System/Windows/Controls/Control.h>
#include <System/Windows/RoutedPropertyChangedEventArgs.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				// Represents an element that has a value within a specific range, such as the System::Windows::Controls::ProgressBar, System::Windows::Controls::Primitives::ScrollBar, and System::Windows::Controls::Slider controls.
				class RangeBase : public Control
				{
				private:
					int maximum;
					int minimum;
					int value;

				protected:
					RangeBase();

					virtual void OnMaximumChanged(const int oldValue, int newValue);
					virtual void OnMinimumChanged(const int oldValue, int newValue);
					virtual void OnValueChanged(const int oldValue, int newValue);

				public:
					int getMaximum() const;
					void setMaximum(const int value);
					int getMinimum() const;
					void setMinimum(const int value);
					int LargeChange;
					int SmallChange;
					int getValue() const;
					void setValue(const int value);

					virtual ~RangeBase();

					int GetType() const;
					const String& ToString() const;

					Event<Object * const, RoutedPropertyChangedEventArgs<int> * const> ValueChanged;

					bool operator ==(const RangeBase& right) const;
					bool operator !=(const RangeBase& right) const;
				};
			}
		}
	}
}

#endif //_SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_RANGEBASE_
