/*****************************************************************************
 *	CultureInfo.h															 *
 *																			 *
 *	XFX System::Globalization::CultureInfo class definition file.			 *
 *	Copyright (c) XFX Team. All Rights Reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_GLOBALIZATION_CULTUREINFO_
#define _SYSTEM_GLOBALIZATION_CULTUREINFO_

#include <System/Interfaces.h>

namespace System
{
	class String;

	namespace Globalization
	{
		/**
		 * Provides information about a specific culture (called a "locale" for unmanaged code development). The information includes the names for the culture, the writing system, the calendar used, and formatting for dates and sort strings.
		 */
		class CultureInfo : public IFormatProvider, public Object
		{
		public:
			static CultureInfo * const InvariantCulture;

			CultureInfo(int culture);
			CultureInfo(int culture, bool useUserOverride);
			CultureInfo(const String& name);
			CultureInfo(const String& name, bool useUserOverride);

			void ClearCacheData();
			bool Equals(Object const * const obj) const;
		};
	}
}

#endif //_SYSTEM_GLOBALIZATION_CULTUREINFO_
