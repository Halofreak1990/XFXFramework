/*
**********************************
**********************************
**      BROUGHT TO YOU BY:		**
**********************************
**********************************
**								**
**		  [TEAM ASSEMBLY]		**
**								**
**		www.team-assembly.com	**
**								**
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
**	     XKUTILS.H - XBOX Utility Class' Header
********************************************************************************************************
**
**	This is the Class Header, see the .CPP file for more comments and implementation details.
**
********************************************************************************************************

********************************************************************************************************
**	CREDITS:
********************************************************************************************************
**	XBOX-LINUX TEAM:
**  ---------------
**		Wow, you guys are awsome !!  I bow down to your greatness !!  
**		REFERENCE URL:  http://xbox-linux.sourceforge.net
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

*/
#ifndef __XKUTILS_H__
#define __XKUTILS_H__
#if defined (ENABLE_XBOX)
	//This complete file is only supported for XBOX..
extern "C" {
#include <xboxkrnl/types.h>
#include <hal/fileio.h>
}

class XKUtils  
{
public:

	//Enum for Devices on SMBus
	enum SMBUS_DEVICES
	{
		SMBDEV_PIC16L					= 0x20,
		SMBDEV_VIDEO_ENCODER_CONEXANT	= 0x8a,		
		SMBDEV_VIDEO_ENCODER_FOCUS		= 0xd4,	
		SMBDEV_VIDEO_ENCODER_XCALIBUR	= 0xe0,	
		SMBDEV_TEMP_MONITOR				= 0x98,	
		SMBDEV_EEPROM					= 0xA8
	};

	// AV Pack Type definitions
	enum AV_PACK
	{
		AV_PACK_SCART					= 0x00,
		AV_PACK_HDTV					= 0x01,
		AV_PACK_VGA					= 0x02,
		AV_PACK_RFU					= 0x03,
		AV_PACK_SVideo					= 0x04,
		AV_PACK_Undefined				= 0x05,
		AV_PACK_Standard				= 0x06,
		AV_PACK_Missing					= 0x07
	};

	//Commands that can be sent to the PIC
	enum PIC16L_CMD
	{
		PIC16L_CMD_PIC_VERSION			= 0x01,
		PIC16L_CMD_POWER			= 0x02,
		PIC16L_CMD_TRAY				= 0x03,
		PIC16L_CMD_AV_PACK			= 0x04,
		PIC16L_CMD_FAN_MODE			= 0x05,
		PIC16L_CMD_FAN_SPEED			= 0x06,
		PIC16L_CMD_LED_MODE			= 0x07,
		PIC16L_CMD_LED_REGISTER			= 0x08,
		PIC16L_CMD_CPU_TEMPERATURE		= 0x09,
		PIC16L_CMD_BOARD_TEMPERATURE		= 0x0A,
		PIC16L_CMD_EJECT			= 0x0C,
		PIC16L_CMD_READ_FAN_SPEED		= 0x10,
		PIC16L_CMD_INTERRUPT_REASON		= 0x11,
		PIC16L_CMD_RESET_ON_EJECT		= 0x19,
		PIC16L_CMD_SCRATCH_REGISTER		= 0x1B
	};
	
	//Commands that can be sent to PIC fan mode command
	enum
	{
		FAN_MODE_SUBCMD_AUTO			= 0x00,
		FAN_MODE_SUBCMD_MANUAL			= 0x01
	};

	//Sub commands for the PIC Power command
	enum POWER_SUBCMD
	{
		POWER_SUBCMD_RESET				= 0x01,
		POWER_SUBCMD_CYCLE				= 0x40,
		POWER_SUBCMD_POWER_OFF			= 0x80
	
	};
	//Commands that can be sent to the Video Encoder
	enum VIDEO_ENCODER_CMD
	{
		VIDEO_ENCODER_CMD_DETECT		= 0x00
	};

	//Values For Video Encoder
	enum VIDEO_ENCODER_TYPE
	{
		VIDEO_ENCODER_UNKNOWN			= 0,
		VIDEO_ENCODER_CONEXANT			= 1,
		VIDEO_ENCODER_FOCUS				= 2,
		VIDEO_ENCODER_XCALIBUR			= 3
	};

	//Sub Command for the PIC LED command
	enum LED_MODE_SUBCMD
	{
		LED_MODE_SUBCMD_DEFAULT_MODE	= 0x00,
		LED_MODE_SUBCMD_CUSTOM_MODE		= 0x01
	};

	//Sub Command for the PIC LED command
	enum LED_REGISTER_CYCLE
	{
		LED_REGISTER_CYCLE3_GREEN		= 0x01,
		LED_REGISTER_CYCLE2_GREEN		= 0x02,
		LED_REGISTER_CYCLE1_GREEN		= 0x04, 
		LED_REGISTER_CYCLE0_GREEN		= 0x08,

		LED_REGISTER_CYCLE3_RED			= 0x10,
		LED_REGISTER_CYCLE2_RED			= 0x20,
		LED_REGISTER_CYCLE1_RED			= 0x40, 
		LED_REGISTER_CYCLE0_RED			= 0x80,
		
		LED_REGISTER_CYCLE3_ORANGE		= 0x11,
		LED_REGISTER_CYCLE2_ORANGE		= 0x22,
		LED_REGISTER_CYCLE1_ORANGE		= 0x44,
		LED_REGISTER_CYCLE0_ORANGE		= 0x88

	};


	//Sub commands for the PIC EJECT command
	enum EJECT_SUBCMD
	{
		EJECT_SUBCMD_EJECT			= 0x00,
		EJECT_SUBCMD_LOAD			= 0x01
	};	

	//Reason for interrupt
	enum INTERRUPT_REASON_BITVALUE
	{
		INTERRUPT_REASON_BITVALUE_POWER_BUTTON		= 0x01,
		INTERRUPT_REASON_BITVALUE_AV_REMOVED		= 0x10,
		INTERRUPT_REASON_BITVALUE_EJECT_BUTTON		= 0x20
	};

	//subcommands for Reset on Eject PIC command
	enum RESET_ON_EJECT_SUBCMD
	{
		RESET_ON_EJECT_SUBCMD_ENABLE				= 0x00,
		RESET_ON_EJECT_SUBCMD_DISABLE				= 0x01

	};

	//Scratch register values..
	enum SCRATCH_REGISTER_BITVALUE
	{
		SCRATCH_REGISTER_BITVALUE_EJECT_AFTER_BOOT	= 0x01,
		SCRATCH_REGISTER_BITVALUE_DISPLAY_ERROR		= 0x02,
		SCRATCH_REGISTER_BITVALUE_NO_ANIMATION		= 0x04,
		SCRATCH_REGISTER_BITVALUE_RUN_DASHBOARD		= 0x08
	};
	
	// Sub commands for the AMD 1032 temperature sensor
	enum TEMP_MONITOR
	{
		TEMP_MONITOR_HIGH_BYTE					= 0x01,
		TEMP_MONITOR_LOW_BYTE					= 0x10,
	};
	
	//Tray state values
	enum TRAY_STATE
	{
		TRAY_STATE_NOT_READY = 0x00,
		TRAY_STATE_OPEN = 0x10,
		TRAY_STATE_OPENING = 0x20,
		TRAY_STATE_CLOSED_NO_MEDIA = 0x40,
		TRAY_STATE_CLOSED_MEDIA_PRESENT = 0x60
	};
	
	//Xbox versions
	enum XBOX_VERSION
	{
		XBOX_VERSION_1_0 = 0,
		XBOX_VERSION_1_1 = 1,
		XBOX_VERSION_1_2_OR_1_3 = 2,
		XBOX_VERSION_1_4 = 3,
		XBOX_VERSION_1_6 = 4,
		XBOX_VERSION_DEVKIT = 5,
		XBOX_VERSION_DEVKIT_GREEN = 6,
		XBOX_VERSION_UNKNOWN = 7
	};
	
	XKUtils();
	virtual ~XKUtils();

	static void	DVDEjectLoadTray();
	static void	DVDEjectTray();
	static void	DVDLoadTray();
	static void	DVDDisableEjectReset();
	static void	DVDEnableEjectReset();
	static LONG	MountDiskC();
	static LONG	MountDiskD();
	static LONG	MountDiskE();
	static LONG	MountDiskF();
	static void	MountAllDisks();
	static LONG	UnMountDiskC();
	static LONG	UnMountDiskD();
	static LONG	UnMountDiskE();
	static LONG	UnMountDiskF();
	static void	UnMountAllDisks();

	static LONG	MountDevice(LPSTR sSymbolicLinkName, LPSTR sDeviceName);
	static LONG	UnMountDevice(LPSTR sSymbolicLinkName);
	
	static void	WriteEEPROMToXBOX(BYTE *EEPROMDATA, UCHAR STARTPOS, UCHAR ENDPOS);
	static bool	ReadEEPROMFromXBOX(BYTE *EEPROMDATA, UCHAR STARTPOS, UCHAR ENDPOS);

	static void	XBOXRebootToDash();
	static void	XBOXReset();
	static void	XBOXPowerOff();
	static void	XBOXPowerCycle();
	/* Set the LED Status from a bitwise OR of the LED_REGISTER_CYCLE
	values above */
	static void	SetXBOXLEDStatus(UCHAR LEDStatus);
	/* Set the LED Status from a string in the form "ABCD" where ABCD are
	the states in the four phases the LED passes through. The possible
	states are: 'r' (red), 'g' (green), 'o' (orange) or 'x' (off).*/
	static void	SetXBOXLEDStatus(char *s);
	
	static int	GetFanSpeed();
	static void	SetFanSpeed(int speed);
	static void	SetAutomaticFanSpeed();
	
	static int	GetBoardTemp();
	/* Read the CPU temperature from the PIC */
	static int	PICGetCPUTemp();
	/* Read the CPU temperature. */
	static double	GetCPUTemp(int version);
	/* Read the CPU temperature, autodetecting the Xbox version */
	static double	GetCPUTemp();
	
	static AV_PACK	GetAVPack();
	static TRAY_STATE	GetTrayState();
	static VIDEO_ENCODER_TYPE	GetVideoEncoderType();
	/* Reads the PIC Version string to version. At least 4 bytes must be allocated for the version string. */
	static bool	GetPICVersion(char *version);
	static XBOX_VERSION	GetXBOXVersion();

	//static void	GetMODCHIPVersion();

};
#endif
#endif
