/********************************************************
 *	TextWriter.h										*
 *														*
 *	XFX TextWriter definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_TEXTWRITER_
#define _SYSTEM_IO_TEXTWRITER_

#include <System/Interfaces.h>

namespace System
{
	namespace IO
	{
		// Represents a writer that can write a sequential series of characters. This class is abstract.
		class TextWriter : public IDisposable
		{
		private:
			IFormatProvider* InternalFormatProvider;
			static const char* InitialNewLine;

		protected:
			char CoreNewLine[];

			TextWriter();
			TextWriter(const IFormatProvider* provider);
			TextWriter(const TextWriter &obj);

			virtual void Dispose(bool disposing);

		public:
			virtual IFormatProvider* getFormatProvider();
			char* NewLine;
			static const TextWriter Null;

			virtual void Close();
			void Dispose();
			virtual void Flush();
			virtual void Write(bool value);
			virtual void Write(char value);
			virtual void Write(char buffer[]);
			virtual void Write(char buffer[], int index, int count);
			virtual void Write(double value);
			virtual void Write(float value);
			virtual void Write(int value);
			virtual void Write(long long value);
			virtual void Write(const char* value);
			virtual void Write(uint value);
			virtual void Write(ulong value);
			virtual void WriteLine();
			virtual void WriteLine(bool value);
			virtual void WriteLine(char value);
			virtual void WriteLine(char buffer[]);
			virtual void WriteLine(char buffer[], int index, int count);
			virtual void WriteLine(double value);
			virtual void WriteLine(float value);
			virtual void WriteLine(int value);
			virtual void WriteLine(long long value);
			virtual void WriteLine(const char* value);
			virtual void WriteLine(uint value);
			virtual void WriteLine(ulong value);
		};
	}
}

#endif //_SYSTEM_IO_TEXTWRITER_
