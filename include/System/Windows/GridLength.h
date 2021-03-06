/*****************************************************************************
 *	GridLength.h															 *
 *																			 *
 *	System::Windows::GridLength definition file 							 *
 *	Copyright (c) XFX Team. All rights reserved								 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_GRIDLENGTH_
#define _SYSTEM_WINDOWS_GRIDLENGTH_

#include <System/Interfaces.h>

#include <System/Windows/Enums.h>

namespace System
{
	namespace Windows
	{
		/**
		 * Represents the length of elements that explicitly support Star unit types.
		 */
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
			static const Type& GetType();
			const String ToString() const;

			bool operator==(const GridLength& right) const;
			bool operator!=(const GridLength& right) const;
		};
	}
}

#endif //_SYSTEM_WINDOWS_GRIDLENGTH_
