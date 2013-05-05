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
			class RowDefinition
			{
			public:
				RowDefinition();

				int getActualHeight() const;
				int MaxHeight;
				int MinHeight;
				GridLength Height;

				bool operator ==(const RowDefinition& right) const;
				bool operator !=(const RowDefinition& right) const;
			};

			// Provides access to an ordered, strongly typed collection of System::Windows::Controls::RowDefinition objects.
			class RowDefinitionCollection : PresentationFrameworkCollection<RowDefinition>
			{
			};
		}
	}
}
