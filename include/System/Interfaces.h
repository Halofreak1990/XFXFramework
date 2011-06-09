/********************************************************
 *	Interfaces.h										*
 *														*
 *	System namespace interfaces definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_INTERFACES_
#define _SYSTEM_INTERFACES_

#include "Object.h"
#include "Types.h"
#include "Threading/WaitHandle.h"

namespace System
{
	/// <summary>
	/// Represents the status of an asynchronous operation. 
	/// </summary>
	interface IAsyncResult
	{
	public:
		virtual Object* AsyncState()=0;
		virtual Threading::WaitHandle* AsyncWaitHandle()=0;
		virtual bool CompletedSynchronously()=0;
		virtual bool IsCompleted()=0;
	};

	/// <summary>
	/// Defines a generalized comparison method that a value type or class implements to create a type-specific
	/// comparison method for ordering instances.
	/// </summary>
	template <class T>
	interface IComparable
	{
	public:
		int CompareTo(T other)=0;
	};

	/// <summary>
	/// Defines a method to release allocated resources.
	/// </summary>
	interface IDisposable
	{
	public:
		virtual void Dispose()=0;
	};

	/// <summary>
	/// Defines a generalized method that a value type or class implements to create
	/// a type-specific method for determining equality of instances.
	/// </summary>
	template<class T>
	interface IEquatable
	{
	public:
		virtual bool Equals(const T other)=0;
	};

	/// <summary>
	/// Provides a mechanism for retrieving an object to control formatting.
	/// </summary>
	interface IFormatProvider
	{
	public:
		virtual Object* GetProvider()=0;
	};

	/// <summary>
	/// Provides a mechanism for retrieving an object to control formatting
	/// </summary>
	interface IServiceProvider
	{
	public:
		virtual Object* GetService(Object* serviceType)=0;
	};
}

#endif //_SYSTEM_INTERFACES_
