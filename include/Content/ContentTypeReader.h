#ifndef _XFX_CONTENT_CONTENTTYPEREADER_
#define _XFX_CONTENT_CONTENTTYPEREADER_

#include <System/Object.h>

using namespace System;

namespace XFX
{
	namespace Content
	{
		class ContentReader;

		template <typename T>
		class ContentTypeReader
		{
		protected:
			// Creates a new instance of ContentTypeReader.
			ContentTypeReader();

			// Reads an object from the current stream.
			Object* Read(ContentReader * const input, Object * const existingInstance);

			// Reads a strongly typed object from the current stream.
			T* Read(ContentReader * const input, T* existingInstance) =0;
		};
	}
}

#endif //_XFX_CONTENT_CONTENTTYPEREADER_
