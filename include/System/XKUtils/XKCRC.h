/*
**********************************
**********************************
**      BROUGHT TO YOU BY:  **
**********************************
**********************************
**        **
**    [TEAM ASSEMBLY]  **
**        **
**  www.team-assembly.com **
**        **
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

********************************************************************************************************
**      XKCRC.H - General CRC Class' Header
********************************************************************************************************
**
** This is the Class Header, see the .CPP file for more comments and implementation details.
**
********************************************************************************************************

UPDATE LOG:
--------------------------------------------------------------------------------------------------------
Date: 07/05/2006
By: friedgold
Reason: OpenXDK Version
--------------------------------------------------------------------------------------------------------
Date: 02/18/2003
By: UNDEAD [team-assembly]
Reason: Prepared 0.2 for Public Release
--------------------------------------------------------------------------------------------------------
Date: 01/06/2003
By: UNDEAD [team-assembly]
Reason: Prepared for Public Release
--------------------------------------------------------------------------------------------------------

*/

#ifndef __XKCRC_H__
#define __XKCRC_H__

#if defined (_WINDOWS)
 #include <afxwin.h>         // MFC core and standard components
#elif defined (ENABLE_XBOX)
extern "C" {
#include <xboxkrnl/types.h>
#include <hal/fileio.h>
}
#else
 #error ERRR: Have to Define _WINDOWS or ENABLE_XBOX !!
#endif


class XKCRC
{
public:
  XKCRC(void);
  virtual ~XKCRC(void);

  static void QuickCRC(UCHAR* CRCVAL, UCHAR* inData, DWORD dataLen);

};
#endif
