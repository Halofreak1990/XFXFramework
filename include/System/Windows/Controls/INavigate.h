#pragma once

#include <System/Uri.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			// Defines a method for internal navigation in an application.
			class INavigate
			{
			public:
				bool Navigate(const Uri& source) =0;
			};
		}
	}
}
