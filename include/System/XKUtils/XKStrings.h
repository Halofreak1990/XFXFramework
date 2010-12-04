/*
******************************************************************************************************
* This is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
******************************************************************************************************

EEPROM string helper functions
*/

#ifndef __XKSTRINGS_H__
#define __XKSTRINGS_H__

extern "C" {
#include <xboxkrnl/types.h>
#include <hal/fileio.h>
}
#include "XKUtils.h"
#include "XKEEPROM.h"

class XKStrings
{
	public:
		static const char *AVPackToString(XKUtils::AV_PACK av);
		static const char *TrayStateToString(XKUtils::TRAY_STATE state);
		static const char *XBOXVersionToString(XKUtils::XBOX_VERSION version);
		static const char *EEPROMXBOXVersionToString(XKEEPROM::XBOX_VERSION version);
		static const char *DVDZoneToString(XKEEPROM::DVD_ZONE zone);
		static const char *XBERegionToString(XKEEPROM::XBE_REGION region);
		static const char *VideoStandardToString(XKEEPROM::VIDEO_STANDARD std);
		static const char *VideoEncoderToString(XKUtils::VIDEO_ENCODER_TYPE encoder);
		static const char *LanguageToString(XKEEPROM::LANGUAGE lang);
};

#endif
