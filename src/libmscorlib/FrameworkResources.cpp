
#include <System/FrameworkResources.h>

namespace System
{
	const char* FrameworkResources::Arg_ParamName_Name					= "Parameter name: %s";
	const char* FrameworkResources::Argument_InvalidOffLen				= "Offset and length were out of bounds for the array or count is greater than the number of elements from index to the end of the source collection";
	const char* FrameworkResources::Argument_InvalidSeekOrigin			= "Invalid SeekOrigin.";
	const char* FrameworkResources::ArgumentNull_Buffer					= "Buffer cannot be null.";
	const char* FrameworkResources::ArgumentNull_FileName				= "File name cannot be null.";
	const char* FrameworkResources::ArgumentNull_Generic				= "Value cannot be null.";
	const char* FrameworkResources::ArgumentNull_Path					= "Path cannot be null.";
	const char* FrameworkResources::ArgumentOutOfRange_NeedNonNegNum	= "Non-negative number required.";
	const char* FrameworkResources::ArgumentOutOfRange_NeedPosNum		= "Positive number required.";
	const char* FrameworkResources::ArgumentOutOfRange_NegativeCapacity	= "Capacity must be positive.";
	const char* FrameworkResources::ArgumentOutOfRange_SmallCapacity	= "capacity was less than the current size.";
	const char* FrameworkResources::ArgumentOutOfRange_StreamLength		= "Stream length must be non-negative and less than 2^31 - 1 - origin.";
	const char* FrameworkResources::IO_SeekBeforeBegin					= "Attempting to seek before the start of the Stream.";
	const char* FrameworkResources::IO_StreamTooLong					= "Stream was too long.";
	const char* FrameworkResources::ObjectDisposed_FileClosed			= "Cannot access a closed file.";
	const char* FrameworkResources::ObjectDisposed_StreamClosed			= "Cannot access a closed Stream.";
	const char* FrameworkResources::NotSupported_MemStreamNotExpandable	= "MemoryStream is not expandable.";
	const char* FrameworkResources::NotSupported_UnreadableStream		= "Stream does not support reading.";
	const char* FrameworkResources::NotSupported_UnseekableStream		= "Stream does not support seeking.";
	const char* FrameworkResources::NotSupported_UnwritableStream		= "Stream does not support writing.";
	const char* FrameworkResources::UnauthorizedAccess_MemStreamBuffer	= "MemoryStream's internal buffer cannot be accessed.";
}
