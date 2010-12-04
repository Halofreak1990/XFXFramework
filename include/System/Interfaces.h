#ifndef _SYSTEM_INTERFACES_
#define _SYSTEM_INTERFACES_

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
		virtual void *ASyncState();
		virtual Threading::WaitHandle AsyncWaitHandle();
		virtual bool CompletedSynchronously();
		virtual bool IsCompleted();
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
		virtual void *GetProvider()=0;
	};

	/// <summary>
	/// Provides a mechanism for retrieving an object to control formatting
	/// </summary>
	interface IServiceProvider
	{
	public:
		virtual void* GetService(void* serviceType)=0;
	};
}

#endif //_SYSTEM_INTERFACES_
