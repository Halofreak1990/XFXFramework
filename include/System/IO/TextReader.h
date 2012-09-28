#ifndef _SYSTEM_IO_TEXTREADER_
#define _SYSTEM_IO_TEXTREADER_

#include "../Interfaces.h"
#include "../String.h"

namespace System
{
	namespace IO
	{
		// Represents a reader that can read a sequential series of characters.
		class TextReader : public IDisposable
		{
		protected:
			void Dispose(bool disposing);

			TextReader();

		public:
			static const TextReader Null;

			virtual void Close();
			void Dispose();
			virtual int Peek() const;
			virtual int Read();
			virtual int Read(char buffer[], const int index, const int count);
			virtual int ReadBlock(char buffer[], const int index, const int count);
			virtual String ReadLine();
			virtual String ReadToEnd();
		};
	}
}

#endif //_SYSTEM_IO_TEXTREADER_
