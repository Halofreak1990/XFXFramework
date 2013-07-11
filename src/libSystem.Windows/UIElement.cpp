#include <System/Windows/UIElement.h>
#include <System/Windows/Size.h>

namespace System
{
	namespace Windows
	{
		const DependencyProperty<Visibility_t> UIElement::VisibilityProperty = DependencyProperty<Visibility_t>::Register("Visibility", UIElement::GetType());

		Visibility_t UIElement::getVisibility() const
		{
			return GetValue(VisibilityProperty);
		}

		void UIElement::setVisibility(const Visibility_t value)
		{
			SetValue(VisibilityProperty, value);
		}

		void UIElement::Arrange(const Rect finalRect)
		{
		}

		int UIElement::GetType()
		{
		}

		void UIElement::InvalidateArrange()
		{
		}

		void UIElement::InvalidateMeasure()
		{
		}

		void UIElement::Measure(const Size availableSize)
		{
		}

		void UIElement::UpdateLayout()
		{
		}

		bool UIElement::operator !=(const UIElement& right) const
		{
			return Object::ReferenceEquals(*this, right);
		}

		bool UIElement::operator ==(const UIElement& right) const
		{
			return !Object::ReferenceEquals(*this, right);
		}
	}
}
