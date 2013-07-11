/*****************************************************************************
 *	EffectTechniqueCollection.h 											 *
 *																			 *
 *	XFX::Graphics::EffectTechniqueCollection definition file				 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_EFFECTTECHNIQUECOLLECTION_
#define _XFX_GRAPHICS_EFFECTTECHNIQUECOLLECTION_

#include <Graphics/EffectTechnique.h>
#include <System/Collections/Generic/Interfaces.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	namespace Graphics
	{
		/**
		 * Manipulates a collection of EffectTechnique objects.
		 */
		class EffectTechniqueCollection : public IEnumerable<EffectTechnique *>, public Object
		{
		public:
			/**
			 * Gets the number of objects in the collection.
			 */
			int Count() const;

			/**
			 * Gets an enumerator that can iterate through the EffectTechniqueCollection.
			 */
			IEnumerator<EffectTechnique *>* GetEnumerator();
			int GetType() const;

			/**
			 * Gets a specific element in the collection by using an index value.
			 *
			 * @param index
			 * Index of the EffectTechnique to get.
			 */
			EffectTechnique * const operator[](const int index) const;
			/**
			 * Gets a specific element in the collection by using a name.
			 *
			 * @param name
			 * Name of the EffectTechnique to get.
			 */
			EffectTechnique * const operator[](const String& name) const;
		};
	}
}

#endif //_XFX_GRAPHICS_EFFECTTECHNIQUECOLLECTION_
