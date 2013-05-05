#include <System/Interfaces.h>

namespace System
{
	class String;

	// Represents a signed 8-bit integer.
	struct SByte : IComparable<SByte>, IEquatable<SByte>, Object
	{
	private:
		sbyte value;

	public:
		static const sbyte MaxValue;
		static const sbyte MinValue;

		SByte();
		SByte(const SByte &obj);
		SByte(const sbyte &obj);

		int CompareTo(const SByte other) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const SByte other) const;
		int GetHashCode() const;
		int GetType() const;
		const char* ToString() const;
		static const char* ToString(const sbyte value);
		static bool TryParse(const String& str, out sbyte* value);

		operator sbyte() const;
		bool operator==(const SByte& right) const;
		bool operator==(const sbyte& right) const;
		bool operator!=(const SByte& right) const;
		bool operator!=(const sbyte& right) const;
	};
}
