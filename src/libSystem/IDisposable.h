/********************************************************
 *	IDisposable.h										*
 *														*
 *	XFX IDisposable interface definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _IDISPOSABLE_
#define _IDISPOSABLE_

namespace System
{
	interface IDisposable
	{
		public:
			void Dispose();
	};
}

#endif //_IDISPOSABLE_
