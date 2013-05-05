#ifndef _XFX_NET_PACKETREADER_
#define _XFX_NET_PACKETREADER_

#include <System/IO/BinaryReader.h>

using namespace System::IO;

namespace XFX
{
	struct Matrix;
	struct Quaternion;
	struct Vector2;
	struct Vector3;
	struct Vector4;

	namespace Net
	{
		// Provides common functionality for efficiently reading incoming network packets.
		class PacketReader : public BinaryReader, public virtual Object
		{
		public:
			int Length();
			int Position();
			void Position(int newValue);

			PacketReader();
			PacketReader(int capacity);

			Matrix ReadMatrix();
			Quaternion ReadQuaternion();
			Vector2 ReadVector2();
			Vector3 ReadVector3();
			Vector4 ReadVEctor4();
		};
	}
}

#endif //_XFX_NET_PACKETREADER_
