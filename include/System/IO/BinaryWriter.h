#ifndef _SYSTEM_IO_BINARYWRITER_
#define _SYSTEM_IO_BINARYWRITER_

#include <System/Types.h>
#include <System/Interfaces.h>
#include <System/Text/Encoding.h>
#include "Stream.h"

using namespace System::Text;

namespace System
{
	namespace IO
	{
		// Writes primitive types in binary to a stream and supports writing strings in a specific encoding.
		class BinaryWriter : public IDisposable, virtual Object
		{
		private:
			byte* _buffer;
			Encoder _encoder;
			Encoding _encoding;
			byte* _largeByteBuffer;
			int _maxChars;
			char* _tmpOneCharBuffer;
			static const int LargeByteBufferSize;

		protected:
			Stream* OutStream;
			BinaryWriter();

			virtual void Dispose(bool disposing);
			void Write7BiteEncodedInt(int value);

		public:
			static const BinaryWriter Null;
			virtual Stream* BaseStream();
			
			BinaryWriter(Stream* output);
			BinaryWriter(Stream* output, Encoding encoding);

			virtual void Close();
			void Dispose();
			virtual void Flush();
			virtual Int64 Seek(int offset, SeekOrigin_t origin);
			virtual void Write(bool value);
			virtual void Write(byte value);
			virtual void Write(byte* value);
			virtual void Write(sbyte value);
			virtual void Write(char ch);
			virtual void Write(double value);
			virtual void Write(short value);
			virtual void Write(int value);
			virtual void Write(Int64 value);
			virtual void Write(float value);
			virtual void Write(char* value);
			virtual void Write(ushort value);
			virtual void Write(uint value);
			virtual void Write(ulong value);
			virtual void Write(byte* buffer, int index, int count);
			virtual void Write(char chars[], int index, int count);
		};
	}
}

#endif //_SYSTEM_IO_BINARYWRITER_
