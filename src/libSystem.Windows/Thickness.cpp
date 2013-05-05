#include <System/Windows/Thickness.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		Thickness::Thickness()
			: Bottom(0), Left(0), Right(0), Top(0)
		{
		}

		Thickness::Thickness(const int uniformLength)
			: Bottom(uniformLength), Left(uniformLength), Right(uniformLength), Top(uniformLength)
		{
		}

		Thickness::Thickness(const int left, const int right, const int top, const int bottom)
			: Bottom(bottom), Left(left), Right(right), Top(top)
		{
		}

		Thickness::Thickness(const Thickness &obj)
			: Bottom(obj.Bottom), Left(obj.Left), Right(obj.Right), Top(obj.Top)
		{
		}

		bool Thickness::Equals(Object const * const obj) const
		{
			return is(obj, this) ? *this == *(Thickness*)obj : false;
		}

		bool Thickness::Equals(const Thickness other) const
		{
			return (*this == other);
		}

		int Thickness::GetHashCode() const
		{
			return (Left + Right + Top + Bottom);
		}

		int Thickness::GetType() const
		{
			// TODO: implement
		}

		const char* Thickness::ToString() const
		{
			return String::Format("{Left:%i Right:%i Top:%i Bottom:%i}", Left, Right, Top, Bottom);
		}

		bool Thickness::operator==(const Thickness& right) const
		{
			return ((Left == right.Left) && (Right == right.Right) &&
					(Top == right.Top) && (Bottom == right.Bottom));
		}

		bool Thickness::operator!=(const Thickness& right) const
		{
			return ((Left != right.Left) || (Right != right.Right) ||
					(Top != right.Top) || (Bottom != right.Bottom));
		}
	}
}
