/*****************************************************************************
 *	Grid.h  																 *
 *																			 *
 *	System::Windows::Controls::Grid definition file  						 *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_CONTROLS_GRID_
#define _SYSTEM_WINDOWS_CONTROLS_GRID_

#include <System/Windows/Controls/Panel.h>
#include <System/Windows/Controls/ColumnDefinition.h>
#include <System/Windows/Controls/RowDefinition.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			/**
			 * Defines a flexible grid area that consists of columns and rows.
			 */
			class Grid : public Panel
			{
			protected:
				Size ArrangeOverride(const Size arrangeSize);
				Size MeasureOverride(const Size constraint);

			public:
				static const DependencyProperty<int> ColumnProperty;
				static const DependencyProperty<int> ColumnSpanProperty;
				static const DependencyProperty<int> RowProperty;
				static const DependencyProperty<int> RowSpanProperty;

				ColumnDefinitionCollection ColumnDefinitions;
				RowDefinitionCollection RowDefinitions;
				bool ShowGridLines;

				Grid();
				~Grid();

				int GetColumn(FrameworkElement const * const element);
				int GetColumnSpan(FrameworkElement const * const element);
				int GetRow(FrameworkElement const * const element);
				int GetRowSpan(FrameworkElement const * const element);
				static const Type& GetType();
				static void SetColumn(FrameworkElement * const element, const int column);
				static void SetColumnSpan(FrameworkElement * const element, const int columnSpan);
				static void SetRow(FrameworkElement * const element, const int row);
				static void SetRowSpan(FrameworkElement * const element, const int rowSpan);

				bool operator==(const Grid& right) const;
				bool operator!=(const Grid& right) const;
			};
		}
	}
}

#endif //_SYSTEM_WINDOWS_CONTROLS_GRID_
