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

#include <System/Types.h>
#include <System/Exception.h>

namespace System
{
	char* Exception::Message()
	{
		return _message;
	}

	Exception::Exception()
	{
		_message = "";
		_innerException = null;
	}

	Exception::Exception(char* message)
	{
		_message = message;
		_innerException = null;
	}

	Exception::Exception(char* message, Exception* innerException)
	{
		_message = message;
		_innerException = innerException;
	}

	Exception::~Exception()
	{
		_innerException = null;
		delete[] _message;
	}

	Exception* Exception::GetBaseException()
	{
		Exception *innerException = _innerException;
		Exception *exception2 = this;
		while(innerException != null)
		{
			exception2 = innerException;
			innerException = innerException->_innerException;
		}
		return innerException;
	}

	Exception* Exception::InnerException()
	{
		return _innerException;
	}
	//
	// ApplicationException
	//
	ApplicationException::ApplicationException()
		: Exception()
	{
	}
	
	ApplicationException::ApplicationException(char* message)
		: Exception(message)
	{
	}

	ApplicationException::ApplicationException(char* message, Exception* innerException)
		: Exception(message, innerException)
	{
	}
	//
	// ArithmeticException
	//
	ArithmeticException::ArithmeticException()
		: Exception()
	{
	}

	ArithmeticException::ArithmeticException(char* message)
		: Exception(message)
	{
	}

	ArithmeticException::ArithmeticException(char* message, Exception* innerException)
		: Exception(message, innerException)
	{
	}
	//
	// DivideByZeroException
	//
	DivideByZeroException::DivideByZeroException()
		: ArithmeticException()
	{
	}

	DivideByZeroException::DivideByZeroException(char* message)
		: ArithmeticException(message)
	{
	}

	DivideByZeroException::DivideByZeroException(char* message, Exception* innerException)
		: ArithmeticException(message, innerException)
	{
	}

	OverflowException::OverflowException()
		: ArithmeticException()
	{
	}

	OverflowException::OverflowException(char* message)
		: ArithmeticException(message)
	{
	}

	OverflowException::OverflowException(char* message, Exception* innerException)
		: ArithmeticException(message, innerException)
	{
	}
}
