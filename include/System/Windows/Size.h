#ifndef _SYSTEM_WINDOWS_SIZE_
#define _SYSTEM_WINDOWS_SIZE_

#include <System/Object.h>
#include <System/Interfaces.h>

namespace System
{
	namespace Windows
	{
		// Describes the width and height of an object.
		struct Size : IEquatable<Size>, Object
		{
		public:
			// Represents a static empty System::Windows::Size.
			static const Size Empty;
			int Height;
			bool IsEmpty() const;
			int Width;

			Size();
			Size(const int Width, const int Height);
			Size(const Size &obj);

			bool Equals(Object const * const obj) const;
			bool Equals(const Size other) const;
			int GetHashCode() const;
			int GetType() const;
			const String& ToString() const;

			bool operator ==(const Size& right) const;
			bool operator !=(const Size& right) const;
		};
	}
}

#endif //_SYSTEM_WINDOWS_SIZE_
