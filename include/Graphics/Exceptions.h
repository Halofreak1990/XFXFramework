/********************************************************
 *	Exceptions.h										*
 *														*
 *	XFX::Graphics Exceptions definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_EXCEPTIONS_
#define _XFX_GRAPHICS_EXCEPTIONS_

#include <System/Runtime/InteropServices/ExternalException.h>

using namespace System;
using namespace System::Runtime::InteropServices;

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// The exception that is thrown if the compilation of an effect fails.
		/// </summary>
		class CompilationFailedException : public ExternalException
		{
		public:
			CompilationFailedException();
			CompilationFailedException(char* message);
			CompilationFailedException(char* message, Exception* inner);
		};

		/// <summary>
		/// The exception that is thrown when the device has been lost but cannot be reset at this time. Therefore,
		/// rendering is not possible.
		/// </summary>
		class DeviceLostException : public ExternalException
		{
		public:
			DeviceLostException();
			DeviceLostException(char* message);
			DeviceLostException(char* message, Exception* inner);
		};

		/// <summary>
		/// The exception that is thrown when the device has been lost but can be reset at this time.
		/// </summary>
		class DeviceNotResetException : public ExternalException
		{
		public:
			DeviceNotResetException();
			DeviceNotResetException(char* message);
			DeviceNotResetException(char* message, Exception* inner);
		};

		/// <summary>
		/// The exception that is thrown when the graphics device does not support the requested capabilities.
		/// </summary>
		class DeviceNotSupportedException : public ExternalException
		{
		public:
			DeviceNotSupportedException();
			DeviceNotSupportedException(char* message);
			DeviceNotSupportedException(char* message, Exception* inner);
		};

		/// <summary>
		/// The error that is thrown when the device is still drawing.
		/// </summary>
		class DeviceStillDrawingException : public ExternalException
		{
		public:
			DeviceStillDrawingException();
			DeviceStillDrawingException(char* message);
			DeviceStillDrawingException(char* message, Exception* inner);
		};

		/// <summary>
		/// The exception that is thrown when an internal driver error occurs. Applications should destroy and recreate the
		/// device when receiving this error.
		/// </summary>
		class DriverInternalErrorException : public ExternalException
		{
		public:
			DriverInternalErrorException();
			DriverInternalErrorException(char* message);
			DriverInternalErrorException(char* message, Exception* inner);
		};

		/// <summary>
		/// The exception that is thrown when Direct3D does not have enough display memory to perform the operation.
		/// </summary>
		class OutOfVideoMemoryException : public ExternalException
		{
		public:
			OutOfVideoMemoryException();
			OutOfVideoMemoryException(char* message);
			OutOfVideoMemoryException(char* message, Exception* inner);
		};
	}
}

#endif //_XFX_GRAPHICS_EXCEPTIONS_
