/*****************************************************************************
 *	EffectParameterCollection.h 											 *
 *																			 *
 *	XFX::Graphics::EffectParameterCollection definition file				 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_EFFECTPARAMETERCOLLECTION_
#define _XFX_GRAPHICS_EFFECTPARAMETERCOLLECTION_

#include <Graphics/EffectParameter.h>
#include <System/Collections/Generic/Interfaces.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	namespace Graphics
	{
		/**
		 * Manipulates a collection of EffectParameter objects.
		 */
		class EffectParameterCollection : public IEnumerable<EffectParameter *>, public Object
		{
		public:
			/**
			 * Gets the number of EffectParameter objects in this EffectParameterCollection.
			 */
			int Count() const;

			/**
			 * Gets an enumerator that can iterate through EffectParameterCollection.
			 */
			IEnumerator<EffectParameter *>* GetEnumerator();
			/**
			 * Gets an effect parameter from its semantic usage.
			 *
			 * @param semantic
			 * The semantic meaning, or usage, of the parameter.
			 */
			EffectParameter * const GetParameterBySemantic(const String& semantic);
			/**
			 * 
			 */
			int GetType() const;

			/**
			 * Gets a specific EffectParameter object by using an index value.
			 *
			 * @param index
			 * Index of the EffectParameter to get.
			 */
			EffectParameter * const operator[](const int index) const;
			/**
			 * Gets a specific EffectParameter by name.
			 *
			 * @param name
			 * The name of the EffectParameter to retrieve.
			 */
			EffectParameter * const operator[](const String& name) const;
		};
	}
}

#endif //_XFX_GRAPHICS_EFFECTPARAMETERCOLLECTION_
