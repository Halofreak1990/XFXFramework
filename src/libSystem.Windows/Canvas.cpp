#include <System/Int32.h>
#include <System/Windows/Controls/Canvas.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			const String Canvas::LeftProperty = "Left";
			const String Canvas::TopProperty = "Top";
			const String Canvas::ZIndexProperty = "ZIndex";

			Canvas::Canvas()
			{
			}

			Size Canvas::ArrangeOverride(const Size arrangeSize)
			{
			}

			int Canvas::GetLeft(const UIElement& element)
			{
				return ((Int32*)element.GetValue(Canvas::LeftProperty))->getValue();
			}

			int Canvas::GetTop(const UIElement& element)
			{
				return ((Int32*)element.GetValue(Canvas::TopProperty))->getValue();
			}

			int Canvas::GetZIndex(const UIElement &element)
			{
				return ((Int32*)element.GetValue(Canvas::ZIndexProperty))->getValue();
			}

			int Canvas::GetType() const
			{
			}

			Size Canvas::MeasureOverride(const Size constraint)
			{
			}

			void Canvas::SetLeft(const UIElement& element, const int left)
			{
				element.SetValue(Canvas::LeftProperty, new Int32(left));
			}

			void Canvas::SetTop(const UIElement& element, const int top)
			{
				element.SetValue(Canvas::TopProperty, new Int32(top));
			}

			void Canvas::SetZIndex(const UIElement& element, const int zIndex)
			{
				element.SetValue(Canvas::ZIndexProperty, new Int32(zIndex));
			}

			bool Canvas::operator ==(const Canvas& right) const
			{
			}

			bool Canvas::operator !=(const Canvas& right) const
			{
			}
		}
	}
}
