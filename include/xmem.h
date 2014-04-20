/*****************************************************************************
 *	xmem.h  																 *
 *																			 *
 *	Defines lightweight pointer wrapper classes for use on the XBOX.		 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _XMEM_
#define _XMEM_

#include <sassert.h>

/**
 *
 *
 * Differences from C++ auto_ptr: exception-less and supports array notation.
 */
template <typename T>
struct auto_ptr
{
private:
	T* ptr;

public:
	auto_ptr(T * const p = 0) : ptr(p) { }
	~auto_ptr() { delete ptr; }

	T& operator *() { return *ptr; }
	T* operator->() { return ptr; }

	T& operator[](int index) { return ptr[index]; }

	auto_ptr<T>& operator=(auto_ptr<T>& rhs)
	{
		if (this != &rhs)
		{
			delete ptr;
			ptr = rhs.ptr;
			rhs.ptr = NULL;
		}

		return *this;
	}
};

/**
 * Represents a garbage-collected, reference-counted pointer.
 *
 * @typeparam T
 * The type of the underlying pointer.
 */
template <typename T>
class gc_ptr
{
private:
	template <typename U>
	class CountedPtr
	{
	private:
		CountedPtr(U* pT) : Count(0), my_pT(pT) { ASSERT(pT != 0); }
		~CountedPtr() { sassert(Count == 0, "ERROR: called ~CountedPtr() while still holding at least one reference."); delete my_pT; }

		unsigned GetRef()  { return ++Count; }
		unsigned FreeRef() { sassert(Count != 0, "ERROR: called FreeRef() while not holding any reference."); return --Count; }

		U* const my_pT;
		unsigned Count;
	};

	CountedPtr<T>* ptr;

public:
	gc_ptr() : ptr(0) { }
	gc_ptr(T * const p) : ptr(new CountedPtr<T>(p))
	{
		ptr->GetRef();
	}
	gc_ptr(const gc_ptr<T> &obj)
		: ptr(obj.ptr)
	{
		if (!IsNull())
		{
			ptr->GetRef();
		}
	}

	~gc_ptr() { UnBind(); }

	bool IsNull() const { return ptr == 0; }

	void Null() { UnBind(); }

	void UnBind()
	{
		if (!IsNull() && ptr->FreeRef() == 0)
		{
			delete ptr;
		}

		ptr = 0;
	}

	T& operator *() { return *ptr->my_pT; }
	T* operator->() { return ptr->my_pT; }

	T& operator[](int index) { return ptr->my_pT[index]; }

	bool operator==(const gc_ptr<T>& rhs) const { return (ptr->my_pT == rhs->ptr->my_pT); }

	bool operator!=(const gc_ptr<T>& rhs) const { return (ptr->my_pT != rhs->ptr->my_pT); }

	gc_ptr<T>& operator=(gc_ptr<T>& rhs)
	{
		if (!rhs.IsNull())
		{
			rhs.ptr->GetRef();
		}

		UnBind();
		ptr = rhs.ptr;
		return *this;
	}
};

#endif //_XMEM_
