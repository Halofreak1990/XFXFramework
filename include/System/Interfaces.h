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
	// Represents the status of an asynchronous operation. 
	interface IAsyncResult
	{
	public:
		virtual Object* AsyncState()=0;
		virtual Threading::WaitHandle* AsyncWaitHandle()=0;
		virtual bool CompletedSynchronously()=0;
		virtual bool IsCompleted()=0;
	};

	// Defines a generalized comparison method that a value type or class implements to create a type-specific comparison method for ordering instances.
	template <class T>
	interface IComparable
	{
	public:
		virtual int CompareTo(const T other) const =0;
	};

	// Defines a method to release allocated resources.
	interface IDisposable
	{
	public:
		virtual void Dispose()=0;
	};

	// Defines a generalized method that a value type or class implements to create a type-specific method for determining equality of instances.
	template<class T>
	interface IEquatable
	{
	public:
		virtual bool Equals(const T other) const =0;
	};

	// Provides a mechanism for retrieving an object to control formatting.
	interface IFormatProvider
	{
	public:
		virtual Object* GetProvider()=0;
	};

	interface IServiceProvider
	{
	public:
		virtual Object* GetService(const char* serviceType)=0;
	};
}

#endif //_SYSTEM_INTERFACES_
