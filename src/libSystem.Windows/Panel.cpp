#include <System/Windows/Controls/Panel.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			Panel::Panel()
				: Background(null)
			{
			}

			Panel::~Panel()
			{
				delete Background;

				for (int i = 0; i < Children.Count(); i++)
				{
					Children[i]->~UIElement();
				}
			}

			int Panel::GetType() const
			{
			}

			bool Panel::operator ==(const Panel& right) const
			{
				return Object::ReferenceEquals(*this, right);
			}

			bool Panel::operator !=(const Panel& right) const
			{
				return !Object::ReferenceEquals(*this, right);
			}
		}
	}
}
