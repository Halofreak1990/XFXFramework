#ifndef _XFX_NET_PACKETWRITER_
#define _XFX_NET_PACKETWRITER_

#include <System/IO/BinaryWriter.h>

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
		/// <summary>
		/// Provides common functionality for efficiently formatting outgoing network packets.
		/// </summary>
		class PacketWriter : public BinaryWriter
		{
		public:
			int Length();
			int Position();
			void Position(int newValue);

			PacketWriter();
			PacketWriter(int capacity);

			void Write(Matrix value);
			void Write(Quaternion value);
			void Write(Vector2 value);
			void Write(Vector3 value);
			void Write(Vector4 value);
		};
	}
}

#endif //_XFX_NET_PACKETWRITER_
