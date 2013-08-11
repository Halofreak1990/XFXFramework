#ifndef _SYSTEM_FRAMEWORKRESOURCES_
#define _SYSTEM_FRAMEWORKRESOURCES_

namespace System
{
	class FrameworkResources
	{
	private:
		FrameworkResources();

	public:
		static const char* Arg_ParamName_Name;
		static const char* Argument_InvalidOffLen;
		static const char* Argument_InvalidSeekOrigin;
		static const char* ArgumentNull_Buffer;
		static const char* ArgumentNull_FileName;
		static const char* ArgumentNull_Generic;
		static const char* ArgumentNull_Path;
		static const char* ArgumentOutOfRange_Index;
		static const char* ArgumentOutOfRange_NeedNonNegNum;
		static const char* ArgumentOutOfRange_NeedPosNum;
		static const char* ArgumentOutOfRange_NegativeCapacity;
		static const char* ArgumentOutOfRange_SmallCapacity;
		static const char* ArgumentOutOfRange_StreamLength;
		static const char* IO_SeekBeforeBegin;
		static const char* IO_StreamTooLong;
		static const char* ObjectDisposed_FileClosed;
		static const char* ObjectDisposed_StreamClosed;
		static const char* NotSupported_MemStreamNotExpandable;
		static const char* NotSupported_UnreadableStream;
		static const char* NotSupported_UnseekableStream;
		static const char* NotSupported_UnwritableStream;
		static const char* UnauthorizedAccess_MemStreamBuffer;
	};
}

#endif //_SYSTEM_FRAMEWORKRESOURCES_
