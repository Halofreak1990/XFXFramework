/*****************************************************************************
 *	Model.h 																 *
 *																			 *
 *	XFX::Graphics::Model class definition file  							 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_MODEL_
#define _XFX_GRAPHICS_MODEL_

#include "ModelBoneCollection.h"
#include "ModelMeshCollection.h"

namespace XFX
{
	struct Matrix;

	namespace Content
	{
		class ModelReader;
	}

	namespace Graphics
	{
		/**
		 * Represents a 3D model composed of multiple ModelMesh objects which may be moved independently. 
		 */
		class Model
		{
		private:
			friend class XFX::Content::ModelReader;

			List<ModelBone> bones;
			List<ModelMesh> meshes;
			static Matrix* sharedDrawBoneMatrices;
			static int sharedDrawBoneMatrixCount;

		public:
			/**
			 * Gets a collection of ModelBone objects which describe how each mesh in the Meshes collection for this model relates to its parent mesh.
			 */
			ModelBoneCollection getBones();
			/**
			 * Gets a collection of ModelMesh objects which compose the model. Each ModelMesh in a model may be moved independently and may be composed of multiple materials identified as ModelMeshPart objects.
			 */
			ModelMeshCollection getMeshes();
			/**
			 * Gets the root bone for this model.
			 */
			ModelBone getRoot();
			/**
			 * Gets or sets an object identifying this model.
			 */
			Object* Tag;

			/**
			 * Copies a transform of each bone in a model relative to all parent bones of the bone into a given array.
			 * 
			 * @param destinationBoneTransforms
			 * The array to receive bone transforms.
			 */
			void CopyAbsoluteBoneTransformsTo(Matrix destinationBoneTransforms[]);
			/**
			 * Copies an array of transforms into each bone in the model.
			 * 
			 * @param sourceBoneTransforms
			 * An array containing new bone transforms.
			 */
			void CopyBoneTransformsFrom(Matrix sourceBoneTransforms[]);
			/**
			 * Copies each bone transform relative only to the parent bone of the model to a given array.
			 * 
			 * @param destinationBoneTransforms
			 * The array to receive bone transforms.
			 */
			void CopyBoneTransformsTo(Matrix destinationBoneTransforms[]);
			/**
			 * Renders the model after applying the matrix transformations.
			 *
			 * @param world
			 * A world transformation matrix.
			 *
			 * @param view
			 * A view transformation matrix.
			 *
			 * @param projection
			 * A projection transformation matrix.
			 */
			void Draw(Matrix world, Matrix view, Matrix projection);
		};
	}
}

#endif //_XFX_GRAPHICS_MODEL_
