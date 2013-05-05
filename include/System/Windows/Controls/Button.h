#pragma once

#include <System/Windows/Controls/Primitives/ButtonBase.h>

using namespace System::Windows::Controls::Primitives;

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			// Represents a button control.
			class Button : public ButtonBase
			{
			protected:
				void OnClick();

			public:
				Button();
				~Button();

				int GetType() const;

				bool operator ==(const Button& right) const;
				bool operator !=(const Button& right) const;
			};
		}
	}
}
