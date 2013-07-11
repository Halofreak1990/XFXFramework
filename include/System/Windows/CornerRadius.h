#ifndef _SYSTEM_WINDOWS_CORNERRADIUS_
#define _SYSTEM_WINDOWS_CORNERRADIUS_

#include <System/Interfaces.h>

namespace System
{
	namespace Windows
	{
		// Describes the characteristics of a rounded corner, such as can be applied to a System::Windows::Controls::Border.
		struct CornerRadius : IEquatable<CornerRadius>, Object
		{
		public:
			int BottomLeft;
			int BottomRight;
			int TopLeft;
			int TopRight;

			CornerRadius();
			CornerRadius(const int uniformValue);
			CornerRadius(const int bottomLeft, const int bottomRight, const int topLeft, const int topRight);
			CornerRadius(const CornerRadius &obj);

			bool Equals(Object const * const obj) const;
			bool Equals(const CornerRadius other) const;
			int GetHashCode() const;
			static int GetType();
			const String& ToString() const;

			bool operator==(const CornerRadius& right) const;
			bool operator!=(const CornerRadius& right) const;
		};
	}
}

#endif //_SYSTEM_WINDOWS_CORNERRADIUS_
