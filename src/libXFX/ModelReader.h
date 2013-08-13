/*****************************************************************************
 *	ModelReader.h															 *
 *																			 *
 *	XFX::Content::ModelReader class definition file 						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_CONTENT_MODELREADER_
#define _XFX_CONTENT_MODELREADER_

#include <Content/ContentTypeReader.h>
#include <Graphics/Model.h>

using namespace XFX::Graphics;

namespace XFX
{
	namespace Content
	{
		class ModelReader : public ContentTypeReader<Model>
		{
		private:
			void ReadBoneReference(ContentReader * const input, uint boneCount);

		public:
			Model* Read(ContentReader * const input, Model* existingInstance);
		};
	}
}

#endif //_XFX_CONTENT_MODELREADER_
