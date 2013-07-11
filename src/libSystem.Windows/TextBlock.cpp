#include <System/Windows/Controls/TextBlock.h>
#include <System/Windows/Media/SolidColorBrush.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			TextBlock::TextBlock()
				: Foreground(new SolidColorBrush(Color::White)), Padding(0), Text(String::Empty)
			{
			}

			TextBlock::~TextBlock()
			{
				delete Foreground;
			}

			const String TextBlock::ToString() const
			{
				return Text;
			}
		}
	}
}
