/********************************************************
 *	StreamReader.h										*
 *														*
 *	XFX StreamReader definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
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
			bool EndOfStream();

			StreamReader(Stream* stream);
			StreamReader(Stream* stream, int bufferSize);
			StreamReader(const char* path);
			StreamReader(const char* path, int bufferSize);

			void Close();
			void DiscardBufferedData();
			int Peek();
			int Read();
			int Read(char buffer[], int index, int count);
			char* ReadLine();
			char* ReadToEnd();
		};
	}
}

#endif //_SYSTEM_IO_STREAMREADER_
