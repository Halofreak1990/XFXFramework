/********************************************************
 *	Exception.h											*
 *														*
 *	XFX Exception definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_EXCEPTION_
#define _SYSTEM_EXCEPTION_

namespace System
{
	/// <summary>
	/// Represents errors that occur during application execution.
	/// </summary>
	class Exception
	{
	private:
		Exception *_innerException;

	protected:
		char* _message;

	public:
		Exception InnerException();
		virtual char* Message();
		
		Exception();
		Exception(char* message);
		virtual ~Exception();

		virtual Exception GetBaseException();
	};

	/// <summary>
	/// The exception that is thrown when a non-fatal application error occurs.
	/// </summary>
	class ApplicationException : public Exception
	{
	public:
		ApplicationException();
		ApplicationException(char* message);
		~ApplicationException();
	};

	/// <summary>
	/// The exception that is thrown for errors in an arithmetic, casting, or conversion operation.
	/// </summary>
	class ArithmeticException : public Exception
	{
	public:
		ArithmeticException();
		ArithmeticException(char* message);
		~ArithmeticException();
	};

	/// <summary>
	/// The exception that is thrown when there is an attempt to divide an integral or decimal value by zero.
	/// </summary>
	class DivideByZeroException : public ArithmeticException
	{
	public:
		DivideByZeroException();
		DivideByZeroException(char* message);
		~DivideByZeroException();
	};

	/// <summary>
	/// Defines the base class for predefined exceptions in the System namespace.
	/// </summary>
	class SystemException : public Exception
	{
	public:
		SystemException();
		SystemException(char* message);
		SystemException(char* message, Exception innerException);
	};

	/// <summary>
	/// The exception that is thrown when there is an attempt to read or write protected memory.
	/// </summary>
	class AccessViolationException : public SystemException
	{
	public:
		AccessViolationException();
		AccessViolationException(char* message);
		AccessViolationException(char* message, Exception innerException);
	};

	/// <summary>
	/// The exception that is thrown when an attempt is made to access an unloaded application domain.
	/// </summary>
	class AppDomainUnloadedException : public SystemException
	{
	public:
		AppDomainUnloadedException();
		AppDomainUnloadedException(char* message);
	};

	/// <summary>
	/// The exception that is thrown when one of the arguments provided to a method is not valid.
	/// </summary>
	class ArgumentException : public SystemException
	{
	protected:
		char* _paramName;

	public:
		char* Message();
		virtual char* ParamName();

		ArgumentException();
		ArgumentException(char* message);
		ArgumentException(char* message, char* paramName);
	};

	/// <summary>
	/// The exception that is thrown when a null reference is passed to a method that does not accept it as a
	/// valid argument.
	/// </summary>
	class ArgumentNullException : public ArgumentException
	{
	public:
		ArgumentNullException();
		ArgumentNullException(char* paramName);
		ArgumentNullException(char* paramName, char* message);
	};

	/// <summary>
	/// The exception that is thrown when the value of an argument is outside the allowable range of values as
	/// defined by the invoked method.
	/// </summary>
	class ArgumentOutOfRangeException : public ArgumentException
	{
	public:
		ArgumentOutOfRangeException();
		ArgumentOutOfRangeException(char* paramName);
		ArgumentOutOfRangeException(char* paramName, void* object, char* message);
		ArgumentOutOfRangeException(char* paramName, char* message);

		virtual void *ActualValue();
		char* Message();
	};

	/// <summary>
	/// The base exception type for all COM interop exceptions and structured exception handling (SEH) exceptions.
	/// </summary>
	class ExternalException : public SystemException
	{
	public:
		ExternalException();
		ExternalException(char* message);
		ExternalException(char* message, Exception inner);
	};

	/// <summary>
	/// The exception that is thrown when an attempt is made to access an element of an array with an index that is
	/// outside the bounds of the array. This class cannot be inherited.
	/// </summary>
	class IndexOutOfRangeException : public SystemException
	{
	public:
		IndexOutOfRangeException();
		IndexOutOfRangeException(char* message);
	};

	/// <summary>
	/// The exception that is thrown when a method call is invalid for the object's current state.
	/// </summary>
	class InvalidOperationException : public SystemException
	{
	public:
		InvalidOperationException();
		InvalidOperationException(char* message);
		InvalidOperationException(char* message, Exception inner);
	};

	/// <summary>
	/// The exception that is thrown when a requested method or operation is not implemented.
	/// </summary>
	class NotImplementedException : public SystemException
	{
	public:
		NotImplementedException();
		NotImplementedException(char* message);
		NotImplementedException(char* message, Exception innerException);
	};

	/// <summary>
	/// The exception that is thrown when an invoked method is not supported, or when there is an attempt to read,
	/// seek, or write to a stream that does not support the invoked functionality.
	/// </summary>
	class NotSupportedException : public SystemException
	{
	public:
		NotSupportedException();
		NotSupportedException(char* message);
		NotSupportedException(char* message, Exception innerException);
	};

	/// <summary>
	/// The exception that is thrown when the operating system denies access because of an I/O error or a specific
	/// type of security error.
	/// </summary>
	class UnauthorizedAccessException : public SystemException
	{
	public:
		UnauthorizedAccessException();
		UnauthorizedAccessException(char* message);
		UnauthorizedAccessException(char* message, Exception inner);
	};

	/// <summary>
	/// The exception that is thrown when an operation is performed on a disposed object.
	/// </summary>
	class ObjectDisposedException : public InvalidOperationException
	{
	private:
		char* _objectName;

	public:
		char* ObjectName();

		ObjectDisposedException(char* objectName);
		ObjectDisposedException(char* objectName, char* message);
	};

	/// <summary>
	/// The exception that is thrown when an arithmetic, casting, or conversion operation in a checked context results in an overflow.
	/// </summary>
	class OverflowException : public ArithmeticException
	{
	public:
		OverflowException();
		OverflowException(char* message);
		OverflowException(char* message, Exception innerException);
	};
}

#endif //_SYSTEM_EXCEPTION_
