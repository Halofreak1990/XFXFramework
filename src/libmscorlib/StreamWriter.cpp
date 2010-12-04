#include <System/Array.h>
#include <System/IO/StreamWriter.h>

namespace System
{
	namespace IO
	{
		void StreamWriter::Close()
		{
			Dispose(true);
		}

		void StreamWriter::Dispose(bool disposing)
		{
			if(!closable)
			{
				Flush(true, true);
			}
		}

		void StreamWriter::Flush()
		{
			Flush(true, true);
		}

		void StreamWriter::Flush(bool flushStream, bool flushEncoder)
		{
			if (((charPos != 0) || flushStream) || flushEncoder)
			{
				if (!haveWrittenPreamble)
				{
					haveWrittenPreamble = true;
					byte* preamble = encoding.GetPreamble();
					if (Array::Length(preamble) > 0)
					{
						stream.Write(preamble, 0, Array::Length(preamble));
					}
				}
				int count = encoder.GetBytes(charBuffer, 0, charPos, &byteBuffer, 0, flushEncoder);
				charPos = 0;
				if (count > 0)
				{
					stream.Write(&byteBuffer, 0, count);
				}
				if(flushStream)
				{
					stream.Flush();
				}
			}
		}

		void StreamWriter::Write(char value)
		{
			if(charPos == charLen)
			{
				Flush(false, false);
			}
		}
	}
}
