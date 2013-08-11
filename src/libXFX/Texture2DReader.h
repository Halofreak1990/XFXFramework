/*****************************************************************************
 *	Texture2DReader.h														 *
 *																			 *
 *	XFX::Content::Texture2DReader class definition file 					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_CONTENT_TEXTURE2DREADER_
#define _XFX_CONTENT_TEXTURE2DREADER_

#include <Content/ContentTypeReader.h>
#include <Graphics/Texture2D.h>

using namespace XFX::Graphics;

namespace XFX
{
	namespace Content
	{
		class Texture2DReader : public ContentTypeReader<Texture2D>
		{
		protected:
			Texture2D* Read(ContentReader * const input, Texture2D* existingInstance);
		};
	}
}

#endif //_XFX_CONTENT_TEXTURE2DREADER_
