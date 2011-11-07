#ifndef _SYSTEM_IO_MEMORYSTREAM_
#define _SYSTEM_IO_MEMORYSTREAM_

#include "../Types.h"
#include "Stream.h"

namespace System
{
	namespace IO
	{
		// Creates a stream whose backing store is memory.
		class MemoryStream : public Stream, virtual Object
		{
		private:
			byte* _buffer;
			int _capacity;
			bool _expandable;
			bool _exposable;
			bool _isOpen;
			int _length;
			int _origin;
			int _position;
			bool _writable;
			static const int MemStreamMaxLength;

			bool EnsureCapacity(int value);

		protected:
			void Dispose(bool disposing);

		public:
			bool CanRead();
			bool CanSeek();
			bool CanWrite();
			virtual int Capacity();
			virtual void Capacity(int value);
			Int64 Length();
			Int64 Position;

			MemoryStream();
			MemoryStream(int capacity);
			MemoryStream(byte buffer[]);
			MemoryStream(byte buffer[], bool writable);
			MemoryStream(byte buffer[], int index, int count);
			MemoryStream(byte buffer[], int index, int count, bool writable);
			MemoryStream(byte buffer[], int index, int count, bool writable, bool publiclyVisible);
			void Flush();
			virtual byte* GetBuffer();
			int Read(byte buffer[], int offset, int count);
			int ReadByte();
			Int64 Seek(Int64 offset, SeekOrigin_t loc);
			void SetLength(Int64 value);
			virtual byte* ToArray();
			void Write(byte buffer[], int offset, int count);
			void WriteByte(byte value);
			virtual void WriteTo(Stream* stream);
		};
	}
}

#endif //_SYSTEM_IO_MEMORYSTREAM_
