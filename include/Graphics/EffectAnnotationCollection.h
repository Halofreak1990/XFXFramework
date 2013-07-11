/*****************************************************************************
 *	EffectAnnotationCollection.h											 *
 *																			 *
 *	XFX::Graphics::EffectAnnotationCollection definition file				 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_EFFECTANNOTATIONCOLLECTION_
#define _XFX_GRAPHICS_EFFECTANNOTATIONCOLLECTION_

#include <Graphics/EffectAnnotation.h>
#include <System/Collections/Generic/Interfaces.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	namespace Graphics
	{
		/**
		 * Manipulates a collection of EffectAnnotation objects.
		 */
		class EffectAnnotationCollection : public IEnumerable<EffectAnnotation>, public Object
		{
		public:
			/**
			 * Gets the number of EffectAnnotation objects in this EffectAnnotationCollection.
			 */
			int Count() const;

			/**
			 * Gets an enumerator that can iterate through the EffectAnnotationCollection.
			 */
			IEnumerator<EffectAnnotation>* GetEnumerator();

			/**
			 *
			 */
			int GetType() const;

			/**
			 * Gets a specific EffectAnnotation object by using an index value.
			 *
			 * @param index
			 * Index of the EffectAnnotation to get.
			 */
			const EffectAnnotation operator[](const int index) const;
			/**
			 * Gets a specific EffectAnnotation object by using a name.
			 *
			 * @param name
			 * Name of the EffectAnnotation to get.
			 */
			const EffectAnnotation operator[](const String& name) const;
		};
	}
}

#endif //_XFX_GRAPHICS_EFFECTANNOTATIONCOLLECTION_
