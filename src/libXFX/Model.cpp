// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <Graphics/Model.h>

namespace XFX
{
	namespace Graphics
	{
		ModelBoneCollection Model::getBones()
		{
			return ModelBoneCollection(&bones);
		}

		ModelMeshCollection Model::getMeshes()
		{
			return ModelMeshCollection(&meshes);
		}

		ModelBone Model::getRoot()
		{
			// TODO: implement
		}

		void Model::CopyAbsoluteBoneTransformsTo(Matrix destinationBoneTransforms[])
		{
			sassert(destinationBoneTransforms != null, FrameworkResources::ArgumentNull_Generic);

			int count = bones.Count;
			for (int index1 = 0; index1 < count; ++index1)
			{
				ModelBone modelBone = bones[index1];
				if (modelBone.getParent() == null)
				{
					destinationBoneTransforms[index1] = modelBone.Transform;
				}
				else
				{
					int index2 = modelBone.getParent()->getIndex();
					Matrix::Multiply(modelBone.Transform, destinationBoneTransforms[index2], out destinationBoneTransforms[index1]);
				}
			}

		}

		void Model::CopyBoneTransformsFrom(Matrix sourceBoneTransforms[])
		{
			sassert(sourceBoneTransforms != null, FrameworkResources::ArgumentNull_Generic);

			// TODO: implement
		}

		void Model::CopyBoneTransformsTo(Matrix destinationBoneTransforms[])
		{
			sassert(destinationBoneTransforms != null, FrameworkResources::ArgumentNull_Generic);

			// TODO: implement
		}

		void Model::Draw(Matrix world, Matrix view, Matrix projection)
		{
			int boneCount = bones.Count;

			if (sharedDrawBoneMatrices == null || sharedDrawBoneMatrixCount < boneCount)
			{
				if (sharedDrawBoneMatrices != null)
				{
					delete sharedDrawBoneMatrices;
				}

				sharedDrawBoneMatrices = new Matrix[boneCount];
				sharedDrawBoneMatrixCount = boneCount;
			}

			// Look up combined bone matrices for the entire model.
			CopyAbsoluteBoneTransformsTo(sharedDrawBoneMatrices);

			for (int i = 0; i < meshes.Count(); i++)
			{
				// TODO: implement

				meshes[i].Draw();
			}
		}
	}
}
