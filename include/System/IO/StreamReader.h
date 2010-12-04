/********************************************************
 *	StreamReader.h										*
 *														*
 *	XFX StreamReader definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _STREAMREADER_
#define _STREAMREADER_

#include "../Text/Encoding.h"
#include "TextReader.h"

using namespace System::Text;

namespace System
{
	namespace IO
	{
		class Stream;

		/// <summary>
		/// Implements a System::IO::TextReader that reads characters from a byte stream in a particular encoding.
		/// </summary>
		class StreamReader : public TextReader
		{
		protected:
			void Dispose(bool disposing);

		public:
			static const StreamReader Null;
			Stream BaseStream();
			Encoding CurrentEncoding();
			bool EndOfStream();

			StreamReader(Stream stream);
			StreamReader(Stream stream, bool detectEncodingFromByteOrderMarks);
			StreamReader(Stream stream, Encoding encoding);
			StreamReader(Stream stream, Encoding encoding, bool detectEncodingFromByteOrderMarks);
			StreamReader(Stream stream, Encoding encoding, bool detectEncodingFromByteOrderMarks, int bufferSize);
			StreamReader(char* path);
			StreamReader(char* path, bool detectEncodingFromByteOrderMarks);
			StreamReader(char* path, Encoding encoding);
			StreamReader(char* path, Encoding encoding, bool detectEncodingFromByteOrderMarks);
			StreamReader(char* path, Encoding encoding, bool detectEncodingFromByteOrderMarks, int bufferSize);

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

#endif //_STREAMREADER_
