#ifndef _SYSTEM_EVENT_
#define _SYSTEM_EVENT_

#include <System/Collections/Generic/List.h>
#include "EventArgs.h"

using namespace System::Collections::Generic;

namespace System
{
	template <typename Arg1, typename Arg2>
	class Event
	{
	private:
		class Base
		{
		public:
			virtual void operator()(Arg1, Arg2) = 0;
			virtual ~Base() {}
		};

	private:
		List<Base*> mPtrs;

		// Can't allow copying unless we modify the class to make a deep
		// copy of each of the pointers it holds. Base class would need 
		// a virtual Clone() method to allow polymorphic copying.
		Event(const Event&);
		Event& operator=(const Event&);

	public:
		template <typename Class>
		class T : public Base
		{
			typedef void (Class::*Func)(Arg1, Arg2);

		private:
			Class*	mThis;
			Func	mFunc;

		public:
			T(Class* aThis, Func aFunc) : mThis(aThis), mFunc(aFunc) {}

			virtual void operator()(Arg1 arg1, Arg2 arg2)
			{
				(mThis->*mFunc)(arg1, arg2);
			}
		};

	public:
		class S : public Base
		{
			typedef void (*Func)(Arg1, Arg2);

		private:
			Func mFunc;

		public:
			S(Func aFunc) : mFunc(aFunc) {}

			virtual void operator()(Arg1 arg1, Arg2 arg2)
			{
				mFunc(arg1, arg2);
			}
		};

	public:
		Event() {}

		Event& operator+=(Base* aPtr)
		{
			mPtrs.Add(aPtr);
			return *this;
		}

		Event& operator-=(Base* aPtr)
		{
			mPtrs.Remove(aPtr);
			return *this;
		}

		void operator()(Arg1 arg1, Arg2 arg2)
		{
			for (int i = 0; i < mPtrs.Count(); i++)
			{
				if (mPtrs[i] != null)
					(*(mPtrs[i]))(arg1, arg2);
			}
		}
	};

	typedef Event<Object*, EventArgs*>	EventHandler;
}

#endif
