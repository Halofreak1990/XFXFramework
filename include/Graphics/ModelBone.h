/*****************************************************************************
 *	ModelBone.h 															 *
 *																			 *
 *	XFX::Graphics::ModelBone class definition file  						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_MODELBONE_
#define _XFX_GRAPHICS_MODELBONE_

#include <System/Collections/Generic/List.h>
#include <Matrix.h>
#include <System/String.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	namespace Graphics
	{
		class ModelBoneCollection;

		/**
		 * Represents bone data for a model.
		 */
		class ModelBone
		{
		private:
			friend class XFX::Content::ModelReader;

			List<ModelBone> children;
			String name;

		public:
			/**
			 * Gets a collection of bones that are children of this bone.
			 */
			ModelBoneCollection getChildren() const;
			/**
			 * Gets the index of this bone in the Bones collection.
			 */
			int getIndex() const;
			/**
			 * Gets the name of this bone.
			 */
			const String getName() const;
			/**
			 * Gets the paremt of this bone.
			 */
			ModelBone* getParent() const;
			/**
			 * Gets or sets the matrix used to transform this bone relative to its parent bone.
			 */
			Matrix Transform;
		};
	}
}

#endif //_XFX_GRAPHICS_MODELBONE_
