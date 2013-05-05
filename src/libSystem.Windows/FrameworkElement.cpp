#include <System/Windows/FrameworkElement.h>
#include <System/Int32.h>
#include <System/Windows/Size.h>

namespace System
{
	namespace Windows
	{
		FrameworkElement::FrameworkElement()
			: Height(Int32::MinValue), HorizontalAlignment(HorizontalAlignment::Stretch),
			Margin(0), VerticalAlignment(VerticalAlignment::Stretch), Width(Int32::MinValue)
		{
		}

		FrameworkElement::~FrameworkElement()
		{
			delete Parent;
		}

		Size FrameworkElement::ArrangeOverride(const Size finalSize)
		{
		}

		int FrameworkElement::GetType() const
		{
		}

		Size FrameworkElement::MeasureOverride(const Size finalSize)
		{
		}
	}
}
