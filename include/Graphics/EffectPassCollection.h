/*****************************************************************************
 *	EffectPassCollection.h													 *
 *																			 *
 *	XFX::Graphics::EffectPassCollection definition file 					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_EFFECTPASSCOLLECTION_
#define _XFX_GRAPHICS_EFFECTPASSCOLLECTION_

#include <Graphics/EffectPass.h>
#include <System/Collections/Generic/Interfaces.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	namespace Graphics
	{
		/**
		 * Manipulates a collection of EffectPass objects.
		 */
		class EffectPassCollection : public IEnumerable<EffectPass *>, public Object
		{
		public:
			/**
			 * Gets the number of objects in the collection.
			 */
			int Count() const;

			/**
			 * Gets an enumerator that can iterate through the EffectPassCollection.
			 */
			IEnumerator<EffectPass *>* GetEnumerator();
			int GetType() const;

			/**
			 * Gets a specific element in the collection by using an index value.
			 *
			 * @param index
			 * Index of the EffectPass to get.
			 */
			EffectPass * const operator[](const int index) const;
			/**
			 * Gets a specific element in the collection by using a name.
			 *
			 * @param name
			 * Name of the EffectPass to get.
			 */
			EffectPass * const operator[](const String& name) const;
		};
	}
}

#endif //_XFX_GRAPHICS_EFFECTPASSCOLLECTION_
