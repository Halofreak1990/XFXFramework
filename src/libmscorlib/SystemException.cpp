// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/Exception.h>

namespace System
{
	//
	// SystemException
	//
	SystemException::SystemException()
		Exception()
	{
	}
	
	SystemException::SystemException(char* message)
		: Exception(message)
	{
	}

	SystemException::SystemException(char* message, Exception* innerException)
		: Exception(message, innerException)
	{
	}
	//
	// AccessViolationException
	//
	AccessViolationException::AccessViolationException()
		: SystemException()
	{
	}

	AccessViolationException::AccessViolationException(char* message)
		: SystemException(message)
	{
	}

	AccessViolationException::AccessViolationException(char* message, Exception* innerException)
		: SystemException(message, innerException)
	{
	}
	//
	// AppDomainUnloadedException
	//
	AppDomainUnloadedException::AppDomainUnloadedException()
		: SystemException()
	{
	}

	AppDomainUnloadedException::AppDomainUnloadedException(char* message)
		: SystemException(message)
	{
	}

	AppDomainUnloadedException::AppDomainUnloadedException(char* message, Exception* innerException)
		: SystemException(message, innerException)
	{
	}
	//
	// ArgumentException
	//
	ArgumentException::ArgumentException()
		: SystemException()
	{
		_paramName = "";
	}

	ArgumentException::ArgumentException(char* message)
		: SystemException(message);
	{
		_paramName = "";
	}

	ArgumentException::ArgumentException(char* message, char* paramName)
		: SystemException(message)
	{
		_paramName = paramName;
	}

	ArgumentException::ArgumentException(char* message, char* paramName, Exception* innerException)
		: SystemException(message, innerException)
	{
		_paramName = paramName;
	}
	//
	// ArgumentNullException
	//
	ArgumentNullException::ArgumentNullException()
		: ArgumentException()
	{
	}

	ArgumentNullException::ArgumentNullException(char* paramName)
		: ArgumentException(paramName)
	{
	}

	ArgumentNullException::ArgumentNullException(char* paramName, char* message)
		: ArgumentException(message, paramName)
	{
	}

	ArgumentNullException::ArgumentNullException(char* message, Exception* innerException)
		: ArgumentException(message, innerException)
	{
	}
	//
	// ArgumentOutOfRangeException
	//
	ArgumentOutOfRangeException::ArgumentOutOfRangeException()
		: ArgumentException(RangeMessage())
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(char* paramName)
		: ArgumentException(RangeMessage(), paramName)
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(char* message, Exception* innerException)
		: ArgumentException(message, innerException)
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(char* paramName, char* message)
		: ArgumentException(message, paramName)
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(char* paramName, Object* actualValue, char* message)
		: ArgumentException(message, paramName)
	{
		_actualValue = actualValue;
	}

	Object* ArgumentOutOfRangeException::ActualValue()
	{
		return _actualValue;
	}

	char* ArgumentOutOfRangeException::RangeMessage()
	{
		if (_rangeMessage == null)
		{
			return "";
		}
		return _rangeMessage;
	}

	IndexOutOfRangeException::IndexOutOfRangeException()
		: SystemException()
	{
	}

	IndexOutOfRangeException::IndexOutOfRangeException(char* message)
		: SystemException(message)
	{
	}

	IndexOutOfRangeException::IndexOutOfRangeException(char* message, Exception* innerException)
		: SystemException(message, innerException)
	{
	}

	InvalidOperationException::InvalidOperationException()
		: SystemException()
	{
	}

	InvalidOperationException::InvalidOperationException(char* message)
		: SystemException(message)
	{
	}

	InvalidOperationException::InvalidOperationException(char* message, Exception* innerException)
		: SystemException(message, innerException)
	{
	}

	NotImplementedException::NotImplementedException()
		: SystemException()
	{
	}

	NotImplementedException::NotImplementedException(char* message)
		: SystemException(message)
	{
	}

	NotImplementedException::NotImplementedException(char* message, Exception* innerException)
		: SystemException(message, innerException)
	{
	}

	NotSupportedException::NotSupportedException()
		: SystemException()
	{
	}

	NotSupportedException::NotSupportedException(char* message)
		: SystemException(message)
	{
	}

	NotSupportedException::NotSupportedException(char* message, Exception* innerException)
		: SystemException(message, innerException)
	{
	}

	OutOfMemoryException::OutOfMemoryException()
		: SystemException("Out of Memory");
	{
	}

	OutOfMemoryException::OutOfMemoryException(char* message)
		: SystemException(message);
	{
	}

	OutOfMemoryException::OutOfMemoryException(char* message, Exception innerException)
		: SystemException(message, innerException);
	{
	}

	ObjectDisposedException::ObjectDisposedException()
		: InvalidOperationException()
	{
	}

	ObjectDisposedException::ObjectDisposedException(char* objectName)
	{
		_objectName = objectName;
		_message = "";
	}

	ObjectDisposedException::ObjectDisposedException(char* message, Exception* innerException)
		: InvalidOperationException(message, innerException)
	{
	}

	ObjectDisposedException::ObjectDisposedException(char* objectName, char* message)
		: InvalidOperationException(message)
	{
		_objectName = objectName;
	}

	char* ObjectDisposedException::ObjectName()
	{
		if (_objectName == null)
			return "";
		return _objectName;
	}

	UnauthorizedAccessException::UnauthorizedAccessException()
		: SystemException()
	{
	}

	UnauthorizedAccessException::UnauthorizedAccessException(char* message)
		: SystemException(message)
	{
	}

	UnauthorizedAccessException::UnauthorizedAccessException(char* message, Exception* inner)
		: SystemException(message, inner)
	{
	}
}
