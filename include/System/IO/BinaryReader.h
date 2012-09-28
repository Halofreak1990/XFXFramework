#ifndef _SYSTEM_IO_BINARYREADER_
#define _SYSTEM_IO_BINARYREADER_

#include <System/Interfaces.h>
#include "Stream.h"

namespace System
{
	class String;

	namespace IO
	{
		// Reads primitive data types as binary values.
		class BinaryReader : public IDisposable
		{
		private:
			bool m_2BytesPerChar;
			byte* m_buffer;
			char* m_charBuffer;
			byte* m_charBytes;
			char* m_singleChar;
			Stream* m_stream;
			bool m_isMemoryStream;

			//! 128 chars should cover most strings in one grab.
			static const int MaxBufferSize = 128;

			bool m_disposed;

			int InternalReadChars(char buffer[], int index, int count);
			int InternalReadOneChar();

		protected:
			virtual void Dispose(bool disposing);
			virtual void FillBuffer(int numBytes);

		public:
			virtual Stream* BaseStream();

			BinaryReader(Stream* input);
			virtual ~BinaryReader();

			virtual void Close();
			virtual void Dispose();
			virtual int PeekChar();
			virtual int Read();
			virtual int Read(byte buffer[], int index, int count);
			virtual int Read(char buffer[], int index, int count);
			virtual bool ReadBoolean();
			virtual byte ReadByte();
			virtual byte* ReadBytes(int count);
			virtual char ReadChar();
			virtual char* ReadChars(int count);
			virtual double ReadDouble();
			virtual short ReadInt16();
			virtual int ReadInt32();
			virtual long long ReadInt64();
			virtual sbyte ReadSByte();
			virtual float ReadSingle();
			virtual String ReadString();
			virtual ushort ReadUInt16();
			virtual uint ReadUInt32();
			virtual ulong ReadUInt64();
		};
	}
}

#endif //_SYSTEM_IO_BINARYREADER_
