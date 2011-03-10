/********************************************************
 *	StreamWriter.h										*
 *														*
 *	XFX StreamWriter definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_STREAMWRITER_
#define _SYSTEM_IO_STREAMWRITER_

#include <System/Text/Encoding.h>
#include <System/Text/Encoder.h>
#include "Stream.h" 
#include "TextWriter.h"
#include <System/Types.h>

using namespace System::Text;

namespace System
{
	namespace IO
	{
		/// <summary>
		/// Implements a TextWriter for writing characters to a stream in a particular encoding.
		/// </summary>
		class StreamWriter : public TextWriter
		{
		private:
			static Encoding _UTF8NoBOM;
			bool autoFlush;
			byte* byteBuffer;
			char* charBuffer;
			int charLen;
			int charPos;
			bool closable;
			static const int DefaultBufferSize;
			Encoder encoder;
			Encoding encoding;
			bool haveWrittenPreamble;
			Stream* stream;

			static Stream* CreateFile(char* path, bool append);
			void Init(Stream* stream, Encoding encoding, int bufferSize);
			void Flush(bool flushStream, bool flushEncoder);

		protected:
			void Dispose(bool disposing);

		public:
			bool AutoFlush;
			virtual Stream BaseStream();
			Encoding Encoding_();
			static const StreamWriter Null;

			StreamWriter(Stream* stream);
			StreamWriter(char* path);
			StreamWriter(Stream* stream, Encoding encoding);
			StreamWriter(char* path, bool append);
			StreamWriter(Stream* stream, Encoding encoding, int bufferSize);
			StreamWriter(char* path, bool append, Encoding encoding);
			StreamWriter(char* path, bool append, Encoding encoding, int bufferSize);
			virtual ~StreamWriter();

			void Close();
			void Flush();
			void Write(char value);
			void Write(char buffer[]);
			void Write(char buffer[], int index, int count);
			void Write(const char* value);
		};
	}
}

#endif //_SYSTEM_IO_STREAMWRITER_
