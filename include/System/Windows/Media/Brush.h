#pragma once

#include <System/Object.h>

namespace System
{
	namespace Windows
	{
		namespace Media
		{
			// Defines objects used to paint graphical objects. Classes that derive from System::Windows::Media::Brush describe how the area is painted.
			class Brush : public Object
			{
			protected:
				Brush();

			public:
				int Opacity;

				virtual ~Brush();

				static int GetType();
			};
		}
	}
}
