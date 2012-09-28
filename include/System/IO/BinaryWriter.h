#ifndef _SYSTEM_IO_BINARYWRITER_
#define _SYSTEM_IO_BINARYWRITER_

#include <System/Interfaces.h>
#include "Stream.h"

namespace System
{
	namespace IO
	{
		// Writes primitive types in binary to a stream and supports writing strings in a specific encoding.
		class BinaryWriter : public IDisposable
		{
		private:
			byte* _buffer;
			byte* _largeByteBuffer;
			int _maxChars;
			char* _tmpOneCharBuffer;
			static const int LargeByteBufferSize;

		protected:
			Stream* OutStream;
			BinaryWriter();

			virtual void Dispose(bool disposing);
			void Write7BitEncodedInt(int value);

		public:
			static const BinaryWriter Null;
			virtual Stream* BaseStream();
			
			BinaryWriter(Stream* output);

			virtual void Close();
			void Dispose();
			virtual void Flush();
			virtual long long Seek(const int offset, const SeekOrigin_t origin);
			virtual void Write(const bool value);
			virtual void Write(const byte value);
			virtual void Write(byte* value);
			virtual void Write(const sbyte value);
			virtual void Write(const char ch);
			virtual void Write(const double value);
			virtual void Write(const short value);
			virtual void Write(const int value);
			virtual void Write(const long long value);
			virtual void Write(const float value);
			virtual void Write(const String value);
			virtual void Write(const ushort value);
			virtual void Write(const uint value);
			virtual void Write(const ulong value);
			virtual void Write(byte* buffer, const int index, const int count);
			virtual void Write(char chars[], const int index, const int count);
		};
	}
}

#endif //_SYSTEM_IO_BINARYWRITER_
