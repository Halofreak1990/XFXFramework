/*****************************************************************************
 *	ModelMesh.h 															 *
 *																			 *
 *	XFX::Graphics::ModelMesh class definition file  						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_MODELMESH_
#define _XFX_GRAPHICS_MODELMESH_

#include "ModelBone.h"
#include "ModelEffectCollection.h"
#include "ModelMeshPartCollection.h"
#include <System/String.h>

using namespace System;

namespace XFX
{
	struct BoundingSphere;

	namespace Graphics
	{
		/**
		 * Represents a mesh that is part of a model.
		 */
		class ModelMesh
		{
		public:
			/**
			 * Gets the BoundingSphere that contains this mesh.
			 */
			BoundingSphere getBoundingSphere() const;
			/**
			 * Gets a collection of effects associated with this mesh.
			 */
			ModelEffectCollection getEffects() const;
			/**
			 * Gets the ModelMeshPart objects that make up this mesh. Each part of a mesh is composed of a set of primitives that share the same material.
			 */
			ModelMeshPartCollection getMeshParts() const;
			/**
			 * Gets the name of this mesh.
			 */
			const String& getName() const;
			/**
			 * Gets the parent bone for this mesh. The parent bone of a mesh contains a transformation matrix that describes how the mesh is located relative to any parent meshes in a model.
			 */
			ModelBone getParentBone() const;
			/**
			 * Gets or sets an object identifying this mesh.
			 */
			Object* Tag;

			/**
			 * Draws all of the ModelMeshPartObjects in this mesh, using their current Effect settings.
			 */
			void Draw();
		};
	}
}

#endif //_XFX_GRAPHICS_MODELMESH_
