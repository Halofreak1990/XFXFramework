/*****************************************************************************
 *	XNBFile.h																 *
 *																			 *
 *	XNA Binary Resource file header definition  							 *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _XNBFILE_
#define _XNBFILE_

#include <System/Types.h>

using namespace System;

namespace XFX
{
	namespace Content
	{
		/**
		 * Represents the header of an *.xnb file
		 */
		struct XNBFile
		{
			byte FormatID1;
			byte FormatID2;
			byte FormatID3;
			byte TargetPlatform;
			byte XNBVersion;
			byte FlagBits;
			uint CompressedSize;
			uint UncompressedSize;
		};
	}
}

#endif //_XNBFILE_
