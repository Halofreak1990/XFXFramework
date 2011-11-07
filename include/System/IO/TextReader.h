#ifndef _SYSTEM_IO_TEXTREADER_
#define _SYSTEM_IO_TEXTREADER_

#include "../Interfaces.h"

namespace System
{
	namespace IO
	{
		/// <summary>
		/// Represents a reader that can read a sequential series of characters.
		/// </summary>
		class TextReader : public IDisposable, virtual Object
		{
		protected:
			void Dispose(bool disposing);

			TextReader();

		public:
			static const TextReader Null;

			virtual void Close();
			void Dispose();
			virtual int Peek();
			virtual int Read();
			virtual int Read(char buffer[], int index, int count);
			virtual int ReadBlock(char buffer[], int index, int count);
			virtual char* ReadLine();
			virtual char* ReadToEnd();
		};
	}
}

#endif //_SYSTEM_IO_TEXTREADER_
