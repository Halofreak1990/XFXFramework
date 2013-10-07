// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/Int32.h>
#include <System/Windows/Controls/Grid.h>
#include <System/Windows/Size.h>
#include <System/Type.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			const DependencyProperty<int> Grid::ColumnProperty = DependencyProperty<int>::Register("Column", Grid::GetType());
			const DependencyProperty<int> Grid::ColumnSpanProperty = DependencyProperty<int>::Register("ColumnSpan", Grid::GetType());
			const DependencyProperty<int> Grid::RowProperty = DependencyProperty<int>::Register("Row", Grid::GetType());
			const DependencyProperty<int> Grid::RowSpanProperty = DependencyProperty<int>::Register("RowSpan", Grid::GetType());

			const Type GridTypeInfo("Grid", "System:Windows::Controls::Grid", TypeCode::Object);

			Size Grid::ArrangeOverride(const Size arrangeSize)
			{
				// TODO: implement
			}

			Size Grid::MeasureOverride(const Size constraint)
			{
				// TODO: implement
			}

			Grid::Grid()
			{
				// TODO: implement
			}

			Grid::~Grid()
			{
			}

			int Grid::GetColumn(FrameworkElement const * const element)
			{
				return element->GetValue(Grid::ColumnProperty);
			}

			int Grid::GetColumnSpan(FrameworkElement const * const element)
			{
				return element->GetValue(Grid::ColumnSpanProperty);
			}

			int Grid::GetRow(FrameworkElement const * const element)
			{
				return element->GetValue(Grid::RowProperty);
			}

			int Grid::GetRowSpan(FrameworkElement const * const element)
			{
				return element->GetValue(Grid::RowSpanProperty);
			}

			const Type& Grid::GetType()
			{
				return GridTypeInfo;
			}

			void Grid::SetColumn(FrameworkElement * const element, const int column)
			{
				if (!element)
				{
					return;
				}

				element->SetValue(Grid::ColumnProperty, column);
			}

			void Grid::SetColumnSpan(FrameworkElement * const element, const int columnSpan)
			{
				if (!element)
				{
					return;
				}

				element->SetValue(Grid::ColumnSpanProperty, columnSpan);
			}

			void Grid::SetRow(FrameworkElement * const element, const int row)
			{
				if (!element)
				{
					return;
				}

				element->SetValue(Grid::RowProperty, row);
			}

			void Grid::SetRowSpan(FrameworkElement * const element, const int rowSpan)
			{
				if (!element)
				{
					return;
				}

				element->SetValue(Grid::RowSpanProperty, rowSpan);
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
