/********************************************************
 *	StreamWriter.h										*
 *														*
 *	XFX StreamWriter definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_STREAMWRITER_
#define _SYSTEM_IO_STREAMWRITER_

#include "Stream.h" 
#include "TextWriter.h"
#include <System/Types.h>

namespace System
{
	namespace IO
	{
		// Implements a TextWriter for writing characters to a stream in a particular encoding.
		class StreamWriter : public TextWriter, virtual Object
		{
		private:
			bool autoFlush;
			byte* byteBuffer;
			char* charBuffer;
			int charLen;
			int charPos;
			bool closable;
			static const int DefaultBufferSize;
			bool haveWrittenPreamble;
			Stream* stream;

			static Stream* CreateFile(const char* path, const bool append);
			void Init(Stream* stream, const int bufferSize);
			void Flush(bool flushStream);

		protected:
			void Dispose(bool disposing);

		public:
			bool AutoFlush;
			virtual Stream* BaseStream();
			static const StreamWriter Null;

			StreamWriter(const char* path);
			StreamWriter(const char* path, const bool append);
			StreamWriter(const char* path, const bool append, const int bufferSize);
			StreamWriter(Stream* stream);
			StreamWriter(Stream* stream, const int bufferSize);
			virtual ~StreamWriter();

			// Closes the current StreamWriter object and the underlying stream.
			void Close();
			// Clears all buffers for the current writer and causes any buffered data to be written to the underlying stream.
			void Flush();
			// Writes a character to the stream.
			//	value
			//		The character to write to the text stream.
			void Write(const char value);
			// Writes a subarray of characters to the stream.
			//	buffer
			//		A character array containing the data to write.
			//	index
			//		The index into buffer at which to begin writing.
			//	count
			//		The number of characters to read from buffer.
			void Write(const char buffer[], const int index, const int count);
			// Writes a string to the stream.
			//	value
			//		The string to write to the stream. If value is null, nothing is written.
			void Write(const char* value);
		};
	}
}

#endif //_SYSTEM_IO_STREAMWRITER_
