/********************************************************
 *	StreamReader.h										*
 *														*
 *	XFX StreamReader definition file					*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_STREAMREADER_
#define _SYSTEM_IO_STREAMREADER_

#include "TextReader.h"

namespace System
{
	namespace IO
	{
		class Stream;

		// Implements a System::IO::TextReader that reads characters from a byte stream.
		class StreamReader : public TextReader
		{
		protected:
			void Dispose(bool disposing);

		public:
			static const StreamReader Null;
			Stream* BaseStream();
			bool EndOfStream() const;

			StreamReader(Stream* stream);
			StreamReader(Stream* stream, const int bufferSize);
			StreamReader(const String& path);
			StreamReader(const String& path, const int bufferSize);

			void Close();
			void DiscardBufferedData();
			int Peek() const;
			int Read();
			int Read(char buffer[], const int index, const int count);
			String ReadLine();
			String ReadToEnd();
		};
	}
}

#endif //_SYSTEM_IO_STREAMREADER_
