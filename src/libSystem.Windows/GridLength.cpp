#include <System/Windows/GridLength.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		const GridLength GridLength::Auto(0, GridUnitType::Auto);

		GridUnitType_t GridLength::getGridUnitType() const
		{
			return gridUnitType;
		}

		int GridLength::getValue() const
		{
			return value;
		}

		bool GridLength::IsAbsolute() const
		{
			return gridUnitType == GridUnitType::Pixel;
		}

		bool GridLength::IsAuto() const
		{
			return gridUnitType == GridUnitType::Auto;
		}

		bool GridLength::IsStar() const
		{
			return gridUnitType == GridUnitType::Star;
		}

		GridLength::GridLength()
			: value(0), gridUnitType(GridUnitType::Auto)
		{
		}

		GridLength::GridLength(const int pixels)
			: value(pixels), gridUnitType(GridUnitType::Pixel)
		{
		}

		GridLength::GridLength(const int value, const GridUnitType_t unitType)
			: value(value), gridUnitType(unitType)
		{
		}

		GridLength::GridLength(const GridLength &obj)
			: value(obj.value), gridUnitType(obj.gridUnitType)
		{
		}

		bool GridLength::Equals(const System::Object *obj) const
		{
			return is(obj, this) ? this->Equals(*(GridLength*)obj) : false;
		}

		bool GridLength::Equals(const GridLength other) const
		{
			return (*this == other);
		}

		int GridLength::GetHashCode() const
		{
			return value + gridUnitType;
		}

		int GridLength::GetType() const
		{
		}

		const char* GridLength::ToString() const
		{
			if (gridUnitType == GridUnitType::Auto)
				return "Auto";
			if (gridUnitType == GridUnitType::Star)
				return "*";
			return String::Format("%i", value);
		}

		bool GridLength::operator ==(const GridLength& right) const
		{
			if (gridUnitType == right.gridUnitType)
			{
				return (value == right.value);
			}
			return false;
		}

		bool GridLength::operator !=(const GridLength& right) const
		{
			return ((gridUnitType != right.gridUnitType) || (value != right.value));
		}
	}
}
