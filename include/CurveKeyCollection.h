/*****************************************************************************
 *	CurveKeyCollection.h													 *
 *																			 *
 *	XFX::CurveKeyCollection class declaration file  						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_CURVEKEYCOLLECTION_
#define _XFX_CURVEKEYCOLLECTION_

#include "CurveKey.h"
#include <System/Collections/Generic/List.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	/**
	 * Contains the CurveKeys making up a Curve.
	 */
	class CurveKeyCollection : public ICollection<CurveKey>
	{
	private:
		bool isReadOnly;
		List<CurveKey> innerList;

	public:
		int Count() const;
		bool IsReadOnly() const;

		CurveKeyCollection();

		void Add(const CurveKey& item);
		void Clear();
		CurveKeyCollection Clone() const;
		bool Contains(const CurveKey& item) const;
		void CopyTo(CurveKey array[], int arrayIndex) const;
		static const Type& GetType();
		int IndexOf(const CurveKey& item) const;
		bool Remove(const CurveKey& item);
		void RemoveAt(int index);

		CurveKey& operator [](int index) const;
		void set(int index, const CurveKey& value); // function to set, because custom action is needed
	};
}

#endif //_XFX_CURVEKEYCOLLECTION_
