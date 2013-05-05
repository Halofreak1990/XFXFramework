#pragma once

#include <System/Windows/GridLength.h>
#include <System/Windows/PresentationFrameworkCollection.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			// Defines row-specific properties that apply to System::Windows::Controls::Grid elements.
			class ColumnDefinition
			{
			public:
				ColumnDefinition();

				int getActualWidth() const;
				int MaxWidth;
				int MinWidth;
				GridLength Width;

				bool operator==(const ColumnDefinition& right) const;
				bool operator!=(const ColumnDefinition& right) const;
			};

			// Provides access to an ordered, strongly typed collection of System::Windows::Controls::RowDefinition objects.
			class ColumnDefinitionCollection : public PresentationFrameworkCollection<ColumnDefinition>
			{
			};
		}
	}
}
