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

#include "ModelReader.h"

#include <Content/ContentReader.h>

#include <System/Diagnostics/Debug.h>

using namespace System::Diagnostics;

namespace XFX
{
	namespace Content
	{
		Model* ModelReader::Read(ContentReader * const reader, Model* existingInstance)
		{
			Model* model = NULL;

			if (existingInstance == NULL)
			{
				
			}
			else
			{
				model = existingInstance;

				// TODO: clean up the old model data
			}

			uint boneCount = reader->ReadUInt32();

			for (uint i = 0; i < boneCount; i++)
			{
				ModelBone bone;

				bone.Transform = reader->ReadMatrix();

				model->bones.Add(bone);
			}

			for (uint i = 0; i < boneCount; i++)
			{
				ReadBoneReference(reader, boneCount);

				// Read the child bone references.
				uint childCount = reader->ReadUInt32();

				if (childCount)
				{
					for (uint j = 0; j < childCount; j++)
					{
						ReadBoneReference(reader, boneCount);
					}
				}
			}

			// Read the mesh data.
			uint meshCount = reader->ReadUInt32();

			for (uint i = 0; i < meshCount; i++)
			{

			}
		}

		void ModelReader::ReadBoneReference(ContentReader * const reader, uint boneCount)
		{
			uint boneId;

			// Read the bone ID, which may be encoded as either an 8 or 32 bit value.
			if (boneCount < 255)
			{
				boneId = reader->ReadByte();
			}
			else
			{
				boneId = reader->ReadUInt32();
			}
		}
	}
}
