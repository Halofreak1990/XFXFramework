#include <System/Windows/Size.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		const Size Size::Empty = Size();

		Size::Size()
			: Height(0), Width(0)
		{
		}

		Size::Size(const int width, const int height)
			: Height(height), Width(width)
		{
		}

		Size::Size(const Size &obj)
			: Height(obj.Height), Width(obj.Width)
		{
		}

		bool Size::IsEmpty() const
		{
			return ((Width == 0) && (Height == 0));
		}

		bool Size::Equals(Object const * const obj) const
		{
			return is(obj, this) ? *this == *(Size*)obj : false;
		}

		bool Size::Equals(const Size other) const
		{
			return (*this == other);
		}

		int Size::GetHashCode() const
		{
			return Width ^ Height;
		}

		int Size::GetType() const
		{
			// TODO: implement
		}

		const char* Size::ToString() const
		{
			return String::Format("{Width:%i Height:%i}", Width, Height);
		}

		bool Size::operator==(const Size& right) const
		{
			return ((Width == right.Width) && (Height == right.Height));
		}

		bool Size::operator!=(const Size& right) const
		{
			return ((Width != right.Width) || (Height != right.Height));
		}
	}
}
