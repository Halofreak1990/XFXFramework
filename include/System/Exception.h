/********************************************************
 *	Exception.h											*
 *														*
 *	XFX Exception definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_EXCEPTION_
#define _SYSTEM_EXCEPTION_

#include <System/Object.h>

namespace System
{
	// Represents errors that occur during application execution.
	class Exception
	{
	private:
		Exception *_innerException;

	protected:
		char* _message;

	public:
		Exception* InnerException();
		virtual char* Message();
		
		Exception();
		Exception(char* message);
		Exception(char* message, Exception* innerException);
		virtual ~Exception();

		virtual Exception* GetBaseException();
	};

	// The exception that is thrown when a non-fatal application error occurs.
	class ApplicationException : public Exception
	{
	public:
		ApplicationException();
		ApplicationException(char* message);
		ApplicationException(char* message, Exception* innerException);
	};

	// The exception that is thrown for errors in an arithmetic, casting, or conversion operation.
	class ArithmeticException : public Exception
	{
	public:
		ArithmeticException();
		ArithmeticException(char* message);
		ArithmeticException(char* message, Exception* innerException);
	};

	// The exception that is thrown when there is an attempt to divide an integral or decimal value by zero.
	class DivideByZeroException : public ArithmeticException
	{
	public:
		DivideByZeroException();
		DivideByZeroException(char* message);
		DivideByZeroException(char* message, Exception* innerException);
	};

	// Defines the base class for predefined exceptions in the System namespace.
	class SystemException : public Exception
	{
	public:
		SystemException();
		SystemException(char* message);
		SystemException(char* message, Exception* innerException);
	};

	// The exception that is thrown when there is an attempt to read or write protected memory.
	class AccessViolationException : public SystemException
	{
	public:
		AccessViolationException();
		AccessViolationException(char* message);
		AccessViolationException(char* message, Exception* innerException);
	};

	// The exception that is thrown when an attempt is made to access an unloaded application domain.
	class AppDomainUnloadedException : public SystemException
	{
	public:
		AppDomainUnloadedException();
		AppDomainUnloadedException(char* message);
		AppDomainUnloadedException(char* message, Exception* innerException);
	};

	// The exception that is thrown when one of the arguments provided to a method is not valid.
	class ArgumentException : public SystemException
	{
	protected:
		char* _paramName;

	public:
		char* getMessage();
		virtual char* getParamName();

		ArgumentException();
		ArgumentException(char* message);
		ArgumentException(char* message, Exception* innerException);
		ArgumentException(char* message, char* paramName);
		ArgumentException(char* message, char* paramName, Exception* innerException);
	};

	// The exception that is thrown when a null reference is passed to a method that does not accept it as a valid argument.
	class ArgumentNullException : public ArgumentException
	{
	public:
		ArgumentNullException();
		ArgumentNullException(char* paramName);
		ArgumentNullException(char* paramName, char* message);
		ArgumentNullException(char* message, Exception* innerException);
	};

	// The exception that is thrown when the value of an argument is outside the allowable range of values as defined by the invoked method.
	class ArgumentOutOfRangeException : public ArgumentException
	{
	private:
		char* _rangeMessage;
		Object* _actualValue;
		char* getRangeMessage();

	public:
		ArgumentOutOfRangeException();
		ArgumentOutOfRangeException(char* paramName);
		ArgumentOutOfRangeException(char* message, Exception* innerException);
		ArgumentOutOfRangeException(char* paramName, char* message);
		ArgumentOutOfRangeException(char* paramName, Object* actualValue, char* message);

		virtual Object* getActualValue();
	};

	// The exception that is thrown when an attempt is made to access an element of an array with an index that is outside the bounds of the array. This class cannot be inherited.
	class IndexOutOfRangeException : public SystemException
	{
	public:
		IndexOutOfRangeException();
		IndexOutOfRangeException(char* message);
		IndexOutOfRangeException(char* message, Exception* innerException);
	};

	// The exception that is thrown when a method call is invalid for the object's current state.
	class InvalidOperationException : public SystemException
	{
	public:
		InvalidOperationException();
		InvalidOperationException(char* message);
		InvalidOperationException(char* message, Exception* innerException);
	};

	// The exception that is thrown when a requested method or operation is not implemented.
	class NotImplementedException : public SystemException
	{
	public:
		NotImplementedException();
		NotImplementedException(char* message);
		NotImplementedException(char* message, Exception* innerException);
	};

	// The exception that is thrown when an invoked method is not supported, or when there is an attempt to read, seek, or write to a stream that does not support the invoked functionality.
	class NotSupportedException : public SystemException
	{
	public:
		NotSupportedException();
		NotSupportedException(char* message);
		NotSupportedException(char* message, Exception* innerException);
	};

	// The Exception that is thrown when there is not enough memory to continue the execution of a program.
	class OutOfMemoryException : public SystemException
	{
	public:
		OutOfMemoryException();
		OutOfMemoryException(char* message);
		OutOfMemoryException(char* message, Exception* innerException);
	};

	// The exception that is thrown when the operating system denies access because of an I/O error or a specific type of security error.
	class UnauthorizedAccessException : public SystemException
	{
	public:
		UnauthorizedAccessException();
		UnauthorizedAccessException(char* message);
		UnauthorizedAccessException(char* message, Exception* innerException);
	};

	// The exception that is thrown when an operation is performed on a disposed object.
	class ObjectDisposedException : public InvalidOperationException
	{
	private:
		char* _objectName;

	public:
		char* getObjectName();

		ObjectDisposedException(char* objectName);
		ObjectDisposedException(char* message, Exception* innerException);
		ObjectDisposedException(char* objectName, char* message);
	};

	// The exception that is thrown when an arithmetic, casting, or conversion operation in a checked context results in an overflow.
	class OverflowException : public ArithmeticException
	{
	public:
		OverflowException();
		OverflowException(char* message);
		OverflowException(char* message, Exception* innerException);
	};
}

#endif //_SYSTEM_EXCEPTION_
