#include <System/Windows/UIElement.h>
#include <System/Windows/Size.h>

namespace System
{
	namespace Windows
	{
		void UIElement::Arrange(const Rect finalRect)
		{
		}

		int UIElement::GetType() const
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
