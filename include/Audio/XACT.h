/********************************************************
 *	XACT.h												*
 *														*
 *	XFramework XACT specification file					*
 *	Copyright © XFX Team. All Rights Reserved		*
 ********************************************************/
#ifndef XFRAMEWORK_XACT_H
#define XFRAMEWORK_XACT_H

//The header in an XACT Settings (XGS) file
struct XGSHeader
{
	char magic[4]; //XGSF
}

//The header in a Sound Bank (XSB) file
struct XSBHeader
{
	char magic[4]; //SDBK
}

//The header in a Wave Bank (XWB) file
struct XWBHeader
{
	char magic[4];
}

#endif
