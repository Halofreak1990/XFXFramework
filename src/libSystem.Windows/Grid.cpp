#include <System/Int32.h>
#include <System/Windows/Controls/Grid.h>
#include <System/Windows/Size.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			const String Grid::ColumnProperty = "Column";
			const String Grid::ColumnSpanProperty = "ColumnSpan";
			const String Grid::RowProperty = "Row";
			const String Grid::RowSpanProperty = "RowSpan";

			Size Grid::ArrangeOverride(const Size arrangeSize)
			{
			}

			Size Grid::MeasureOverride(const Size constraint)
			{
			}

			Grid::Grid()
			{
			}

			Grid::~Grid()
			{
			}

			int Grid::GetColumn(FrameworkElement const * const element)
			{
				Int32* columnValue = (Int32*)element->GetValue(Grid::ColumnProperty);
				return (columnValue) ? columnValue->getValue() : 0;
			}

			int Grid::GetColumnSpan(FrameworkElement const * const element)
			{
				Int32* columnSpanValue = (Int32*)element->GetValue(Grid::ColumnSpanProperty);
				return (columnSpanValue) ? columnSpanValue->getValue() : 0;
			}

			int Grid::GetRow(FrameworkElement const * const element)
			{
				Int32* rowValue = (Int32*)element->GetValue(Grid::RowProperty);
				return (rowValue) ? rowValue->getValue() : 0;
			}

			int Grid::GetRowSpan(FrameworkElement const * const element)
			{
				Int32* rowSpanValue = (Int32*)element->GetValue(Grid::RowSpanProperty);
				return (rowSpanValue) ? rowSpanValue->getValue() : 0;
			}

			int Grid::GetType() const
			{
			}

			void Grid::SetColumn(FrameworkElement * const element, const int column)
			{
				if (!element)
					return;

				element->SetValue(Grid::ColumnProperty, new Int32(column));
			}

			void Grid::SetColumnSpan(FrameworkElement * const element, const int columnSpan)
			{
				if (!element)
					return;

				element->SetValue(Grid::ColumnSpanProperty, new Int32(columnSpan));
			}

			void Grid::SetRow(FrameworkElement * const element, const int row)
			{
				if (!element)
					return;

				element->SetValue(Grid::RowProperty, new Int32(row));
			}

			void Grid::SetRowSpan(FrameworkElement * const element, const int rowSpan)
			{
				if (!element)
					return;

				element->SetValue(Grid::RowSpanProperty, new Int32(rowSpan));
			}

			bool Grid::operator ==(const Grid &right) const
			{
				return Object::ReferenceEquals(*this, right);
			}

			bool Grid::operator !=(const Grid &right) const
			{
				return !Object::ReferenceEquals(*this, right);
			}
		}
	}
}
