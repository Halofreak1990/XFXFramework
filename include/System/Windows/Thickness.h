/*****************************************************************************
 *	Thickness.h 															 *
 *																			 *
 *	System::Windows::Thickness definition file  							 *
 *	Copyright (c) XFX Team. All rights reserved								 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_THICKNESS_
#define _SYSTEM_WINDOWS_THICKNESS_

#include <System/Interfaces.h>

namespace System
{
	namespace Windows
	{
		/**
		 * Describes the thickness of a frame around a rectangle.
		 * Four int values describe the System::Windows::Thickness::Left,
		 * System::Windows::Thickness.Top, System::Windows::Thickness.Right,
		 * and System::Windows::Thickness.Bottom sides of the rectangle, respectively.
		 */
		struct Thickness : IEquatable<Thickness>, Object
		{
		public:
			int Bottom;
			int Left;
			int Right;
			int Top;

			Thickness();
			/**
			 * Initializes a System::Windows::Thickness structure that has the specified uniform length on each side.
			 */
			Thickness(const int uniformLength);
			/**
			 * Initializes a System::Windows::Thickness structure that has specific lengths (supplied as an int) applied to each side of the rectangle.
			 */
			Thickness(const int left, const int right, const int top, const int bottom);
			Thickness(const Thickness &obj);

			/**
			 * Compares this System::Windows::Thickness structure to the specified System::Object for equality.
			 */
			bool Equals(Object const * const obj) const;
			/**
			 * Compares this System::Windows::Thickness structure to another System::Windows::Thickness structure for equality.
			 */
			bool Equals(const Thickness other) const;
			/**
			 * Returns the hash code of the structure.
			 */
			int GetHashCode() const;
			/**
			 * Returns the TypeCode for this object as an integer.
			 */
			static const Type& GetType();
			/**
			 * Returns the string representation of the System::Windows::Thickness structure.
			 */
			const String ToString() const;

			/**
			 * Determines whether two System::Windows::Thickness objects are equal.
			 *
			 * @param right
			 * The System::Windows::Thickness on the right side of the equality operator
			 *
			 * @return
			 * true if the System::Windows::Thickness instances are equal; otherwise, false.
			 */
			bool operator ==(const Thickness& right) const;
			/**
			 * Determines whether two System::Windows::Thickness objects are not equal.
			 *
			 * @param right
			 * The System::Windows::Thickness on the right side of the inequality operator
			 *
			 * @return
			 * true if the System::Windows::Thickness instances are not equal; otherwise, false.
			 */
			bool operator !=(const Thickness& right) const;
		};
	}
}

#endif
