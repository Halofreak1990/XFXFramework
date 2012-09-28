/********************************************************
 *	ContentReader.h										*
 *														*
 *	XFX ContentReader class definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_CONTENT_CONTENTREADER_
#define _XFX_CONTENT_CONTENTREADER_

#include <System/IO/BinaryReader.h>
#include <Content/ContentManager.h>
#include <Graphics/GraphicsDevice.h>

using namespace System;
using namespace System::IO;
using namespace XFX::Graphics;

namespace XFX
{
	struct Matrix;
	struct Quaternion;
	struct Vector2;
	struct Vector3;
	struct Vector4;

	namespace Content
	{
		template <typename T>
		class ContentTypeReader;

		// A worker object that implements most of ContentManager.Load. A new ContentReader is constructed for each asset loaded.
		class ContentReader : public BinaryReader, public Object
		{
		private:
			ContentManager* contentManager;
			GraphicsDevice* _graphicsDevice;
			String _assetName;
			static const short XnbVersion;

			static Stream* PrepareStream(Stream * const stream, const String& assetName);

		public:
			String getAssetName() const;
			ContentManager* getContentManager() const;

			ContentReader(ContentManager * const manager, Stream * const stream, GraphicsDevice * const graphicsDevice);
			ContentReader(ContentManager * const manager, Stream * const input, const String& assetName);
			~ContentReader();

			template <class T>
			T ReadExternalReference();
			Matrix ReadMatrix();
			template <class T>
			T ReadObject();
			template <class T>
			T ReadObject(T existingInstance);
			template <class T>
			T ReadObject(ContentTypeReader<T>* typeReader);
			template <class T>
			T ReadObject(ContentTypeReader<T>* typeReader, T existingInstance);
			Quaternion ReadQuaternion();
			template <class T>
			T ReadRawObject();
			template <class T>
			T ReadRawObject(ContentTypeReader<T>* typeReader);
			template <class T>
			T ReadRawObject(T existingInstance);
			template <class T>
			T ReadRawObject(ContentTypeReader<T>* typeReader, T existingInstance);
			Vector2 ReadVector2();
			Vector3 ReadVector3();
			Vector4 ReadVector4();
		};
	}
}

#endif //_XFX_CONTENT_CONTENTREADER_
