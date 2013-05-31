#pragma once

#include <System/Interfaces.h>

#include <System/Windows/Enums.h>

namespace System
{
	namespace Windows
	{
		// Represents the length of elements that explicitly support Star unit types.
		struct GridLength : IEquatable<GridLength>, Object
		{
		private:
			int value;
			GridUnitType_t gridUnitType;

		public:
			static const GridLength Auto;
			bool IsAbsolute() const;
			bool IsAuto() const;
			GridUnitType_t getGridUnitType() const;
			int getValue() const;
			bool IsStar() const;

			GridLength();
			GridLength(const int pixels);
			GridLength(const int value, const GridUnitType_t unitType);
			GridLength(const GridLength &obj);

			bool Equals(Object const * const obj) const;
			bool Equals(const GridLength other) const;
			int GetHashCode() const;
			int GetType() const;
			const char* ToString() const;

			bool operator==(const GridLength& right) const;
			bool operator!=(const GridLength& right) const;
		};
	}
}
