#ifndef _TEXTREADER_
#define _TEXTREADER_

namespace System
{
	class String;

	namespace IO
	{
		/// <summary>
		/// Represents a reader that can read a sequential series of characters.
		/// </summary>
		class TextReader
		{
		protected:
			void Dispose(bool disposing);

			TextReader();

		public:
			static const TextReader Null;

			void Close();
			void Dispose();
			int Peek();
			int Read();
			int Read(char buffer[], int index, int count);
			int ReadBlock(char buffer[], int index, int count);
			String ReadLine();
			String ReadToEnd();
			TextReader Synchronized(TextReader &reader);
		};
	}
}

#endif //_TEXTREADER_
