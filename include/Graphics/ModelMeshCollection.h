/*****************************************************************************
 *	ModelMeshCollection.h													 *
 *																			 *
 *	XFX::Graphics::ModelMeshCollection class definition file				 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_MODELMESHCOLLECTION_
#define _XFX_GRAPHICS_MODELMESHCOLLECTION_

#include "ModelMesh.h"
#include <System/Collections/ObjectModel/ReadOnlyCollection.h>

using namespace System::Collections::ObjectModel;

namespace XFX
{
	namespace Graphics
	{
		/**
		 * Represents a collection of ModelMesh objects.
		 */
		class ModelMeshCollection : public ReadOnlyCollection<ModelMesh>
		{
		private:
			friend class Model;

			ModelMeshCollection(IList<ModelMesh>* list);

		public:
			/**
			 * Finds a mesh with a given name if it exists in the collection.
			 *
			 * @param boneName
			 * The name of the mesh to find.
			 *
			 * @param value
			 * [OutAttribute] The bone named boneName, if found.
			 */
			bool TryGetValue(const String& meshName, out ModelMesh * value);

			/**
			 * Retrieves a ModelMesh from the collection, given the name of the mesh.
			 *
			 * @param name
			 * The name of the bone to retrieve.
			 */
			ModelMesh& operator[](const String& name) const;
		};
	}
}

#endif //_XFX_GRAPHICS_MODELMESHCOLLECTION_
