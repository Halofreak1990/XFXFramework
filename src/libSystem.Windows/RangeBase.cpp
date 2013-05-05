#include <System/Windows/Controls/Primitives/RangeBase.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				int RangeBase::getMaximum() const
				{
					return maximum;
				}

				void RangeBase::setMaximum(const int value)
				{
					if (maximum != value)
					{
						OnMaximumChanged(maximum, value);
						maximum = value;
					}
				}

				int RangeBase::getMinimum() const
				{
					return minimum;
				}

				void RangeBase::setMinimum(const int value)
				{
					if (minimum != value)
					{
						OnMinimumChanged(minimum, value);
						minimum = value;
					}
				}

				int RangeBase::getValue() const
				{
					return value;
				}

				void RangeBase::setValue(const int value)
				{
					if (this->value != value)
					{
						OnValueChanged(this->value, value);
						this->value = value;
					}
				}

				RangeBase::RangeBase()
				{
				}

				void RangeBase::OnValueChanged(int oldValue, int newValue)
				{
					ValueChanged(this, new RoutedPropertyChangedEventArgs<int>(oldValue, newValue));
				}

				const char* RangeBase::ToString() const
				{
					return String::Format("{RangeBase Minimum:%i Maximum:%i Value:%i}", minimum, maximum, value);
				}
			}
		}
	}
}
