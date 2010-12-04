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
	SystemException::SystemException()
	{
		_message = "";
	}
	
	SystemException::SystemException(char* message)
	{
		_message = message;
	}

	SystemException::SystemException(char* message, Exception innerException)
	{
		_message = message;
	}

	AccessViolationException::AccessViolationException()
	{
		_message = "";
	}

	AccessViolationException::AccessViolationException(char* message)
	{
		_message = message;
	}

	AppDomainUnloadedException::AppDomainUnloadedException()
	{
		_message = "";
	}

	AppDomainUnloadedException::AppDomainUnloadedException(char* message)
	{
		_message = message;
	}

	ArgumentException::ArgumentException()
	{
		_message = "";
		_paramName = "";
	}

	ArgumentException::ArgumentException(char* message)
	{
		_message = message;
		_paramName = "";
	}

	ArgumentException::ArgumentException(char* message, char* paramName)
	{
		_message = message;
		_paramName = paramName;
	}

	ArgumentNullException::ArgumentNullException()
	{
		_message = "";
		_paramName = "";
	}

	ArgumentNullException::ArgumentNullException(char* message)
	{
		_message = message;
		_paramName = "";
	}

	ArgumentNullException::ArgumentNullException(char* message, char* paramName)
	{
		_message = message;
		_paramName = paramName;
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException()
	{
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(char* paramName, char* message)
	{
		_message = message;
		_paramName = paramName;
	}

	ArgumentOutOfRangeException::ArgumentOutOfRangeException(char* paramName, void* object, char* message)
	{
		_message = message;
		_paramName = paramName;
	}

	IndexOutOfRangeException::IndexOutOfRangeException()
	{
	}

	IndexOutOfRangeException::IndexOutOfRangeException(char* message)
	{
		_message = message;
	}

	InvalidOperationException::InvalidOperationException()
	{
	}

	InvalidOperationException::InvalidOperationException(char* message)
	{
		_message = message;
	}

	NotImplementedException::NotImplementedException()
	{
	}

	NotImplementedException::NotImplementedException(char* message)
	{
		_message = message;
	}

	NotImplementedException::NotImplementedException(char* message, Exception innerException)
	{
		_message = message;
	}

	NotSupportedException::NotSupportedException()
	{
		_message = "";
	}

	NotSupportedException::NotSupportedException(char* message)
	{
		_message = message;
	}

	NotSupportedException::NotSupportedException(char* message, Exception innerException)
	{
		_message = message;
	}

	ObjectDisposedException::ObjectDisposedException(char* objectName)
	{
		_objectName = objectName;
	}

	ObjectDisposedException::ObjectDisposedException(char* objectName, char* message)
	{
		_objectName = objectName;
		_message = message;
	}

	char* ObjectDisposedException::ObjectName()
	{
		return _objectName;
	}

	UnauthorizedAccessException::UnauthorizedAccessException()
	{
		_message = "";
	}

	UnauthorizedAccessException::UnauthorizedAccessException(char* message)
	{
		_message = message;
	}

	UnauthorizedAccessException::UnauthorizedAccessException(char* message, Exception inner)
	{
		_message = message;
	}
}
