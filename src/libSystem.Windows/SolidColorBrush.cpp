#include <System/Windows/Media/SolidColorBrush.h>

namespace System
{
	namespace Windows
	{
		namespace Media
		{
			SolidColorBrush::SolidColorBrush()
				: Color(Color::Transparent)
			{
			}

			SolidColorBrush::SolidColorBrush(const System::Windows::Media::Color color)
				: Color(color)
			{
			}

			int SolidColorBrush::GetType() const
			{
				// TODO: implement
			}
		}
	}
}
