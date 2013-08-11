/*****************************************************************************
 *	ModelBoneCollection.h													 *
 *																			 *
 *	XFX::Graphics::ModelBoneCollection class definition file				 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_MODELBONECOLLECTION_
#define _XFX_GRAPHICS_MODELBONECOLLECTION_

#include "ModelBone.h"
#include <System/Collections/ObjectModel/ReadOnlyCollection.h>

using namespace System::Collections::ObjectModel;

namespace XFX
{
	namespace Graphics
	{
		/**
		 * Represents a set of bones associated with a model.
		 */
		class ModelBoneCollection : public ReadOnlyCollection<ModelBone>
		{
		private:
			friend class Model;

			ModelBoneCollection(IList<ModelBone> * const list);

		public:
			/**
			 * Finds a bone with a given name if it exists in the collection.
			 *
			 * @param boneName
			 * The name of the bone to find.
			 *
			 * @param value
			 * [OutAttribute] The bone named boneName, if found.
			 */
			bool TryGetValue(const String& boneName, out ModelBone * value);

			/**
			 * Retrieves a ModelBone from the collection, given the name of the bone.
			 *
			 * @param name
			 * The name of the bone to retrieve.
			 */
			ModelBone& operator[](const String& name) const;
		};
	}
}

#endif //_XFX_GRAPHICS_MODELBONECOLLECTION_
