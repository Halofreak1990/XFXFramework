/********************************************************
 *	StreamWriter.h										*
 *														*
 *	XFX StreamWriter definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_STREAMWRITER_
#define _SYSTEM_IO_STREAMWRITER_

#include "../Text/Encoding.h"
#include "../Text/Encoder.h"
#include "Stream.h" 
#include "TextWriter.h"
#include "../Types.h"

using namespace System::Text;

namespace System
{
	class String;

	namespace IO
	{
		/// <summary>
		/// Implements a TextWriter for writing characters to a stream in a particular encoding.
		/// </summary>
		class StreamWriter : public TextWriter
		{
		private:
			byte byteBuffer;
			char charBuffer[];
			int charLen;
			int charPos;
			bool closable;
			Encoder encoder;
			Encoding encoding;
			bool haveWrittenPreamble;
			Stream stream;

			void Flush(bool flushStream, bool flushEncoder);

		protected:
			void Dispose(bool disposing);

		public:
			bool AutoFlush;
			virtual Stream BaseStream();
			Encoding Encoding_();
			static const StreamWriter Null;

			StreamWriter(const char* path);
			StreamWriter(const char* path, bool append);
			StreamWriter(const char* path, bool append, Encoding encoding);
			StreamWriter(const char* path, bool append, Encoding encoding, int bufferSize);
			StreamWriter(Stream stream);
			StreamWriter(Stream stream, Encoding encoding);
			StreamWriter(Stream stream, Encoding encoding, int bufferSize);

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
