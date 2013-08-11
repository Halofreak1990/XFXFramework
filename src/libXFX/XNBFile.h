#ifndef _XNBFILE_
#define _XNBFILE_

#include <System/Types.h>

using namespace System;

namespace XFX
{
	namespace Content
	{
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
