// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/Array.h>
#include <System/Buffer.h>
#include <System/Exception.h>
#include <System/IO/IOException.h>
#include <System/IO/MemoryStream.h>

namespace System
{
	namespace IO
	{
#if ENABLE_XBOX // The XBOX Limits us to 64MB; we do not take XDKs into account
		const int MemoryStream::MemStreamMaxLength = 0x40000000;
#else
		const int MemoryStream::MemStreamMaxLength = 0x7fffffff;
#endif

		bool MemoryStream::CanRead()
		{
			return _isOpen;
		}

		bool MemoryStream::CanSeek()
		{
			return _isOpen;
		}

		bool MemoryStream::CanWrite()
		{
			return _writable;
		}

		int MemoryStream::Capacity()
		{
			if (!_isOpen)
			{
				throw ObjectDisposedException(null, "Stream is closed.");
			}
			return (_capacity - _origin);
		}

		void MemoryStream::Capacity(int value)
		{
			if (!_isOpen)
			{
				throw ObjectDisposedException(null, "Stream is closed.");
			}
			if (value != _capacity)
			{
				if (!_expandable)
				{
					throw NotSupportedException("");
				}
				if (value < _length)
				{
					throw ArgumentOutOfRangeException("value");
				}
				if (value > 0)
				{
					byte* dst = new byte[value];
					if (_length > 0)
					{
						Buffer::BlockCopy(_buffer, 0, dst, 0, _length);
					}
					_buffer = dst;
				}
				else
				{
					_buffer = null;
				}
				_capacity = value;
			}
		}

		MemoryStream::MemoryStream()
		{
			_buffer = new byte[0];
			_capacity = 0;
			_expandable = true;
			_writable = true;
			_exposable = true;
			_origin = 0;
			_isOpen = true;
		}

		MemoryStream::MemoryStream(int capacity)
		{
			if (capacity < 0)
			{
				throw ArgumentOutOfRangeException("capacity", "Negative capacity is not allowed.");
			}
			_buffer = new byte[capacity];
			_capacity = capacity;
			_expandable = true;
			_writable = true;
			_exposable = true;
			_origin = 0;
			_isOpen = true;
		}

		MemoryStream::MemoryStream(byte buffer[])
		{
			if (buffer == null)
			{
				throw ArgumentNullException("buffer", "Buffer was NULL.");
			}
			_buffer = buffer;
			_length = _capacity = Array::Length(buffer);
			_writable = true;
			_exposable = false;
			_origin = 0;
			_isOpen = true;
		}

		MemoryStream::MemoryStream(byte buffer[], bool writable)
		{
			if (buffer == null)
			{
				throw ArgumentNullException("buffer", "Buffer was NULL.");
			}
			_buffer = buffer;
			_length = _capacity = Array::Length(buffer);
			_writable = writable;
			_exposable = false;
			_origin = 0;
			_isOpen = true;
		}

		MemoryStream::MemoryStream(byte buffer[], int index, int count)
		{
			if (buffer == null)
			{
				throw ArgumentNullException("buffer", "Buffer was NULL.");
			}
			if (index < 0)
			{
				throw ArgumentOutOfRangeException("index", "Non-negative number required.");
			}
			if (count < 0)
			{
				throw ArgumentOutOfRangeException("count", "Non-negative number required.");
			}
			if ((Array::Length(buffer) - index) < count)
			{
				throw ArgumentException("Invalid offset or length.");
			}
			_buffer = buffer;
			_origin = _position = index;
			_length = _capacity = index + count;
			_writable = true;
			_exposable = false;
			_expandable = true;
			_isOpen = true;
		}

		MemoryStream::MemoryStream(byte buffer[], int index, int count, bool writable)
		{
			if (buffer == null)
			{
				throw ArgumentNullException("buffer", "Buffer was NULL.");
			}
			if (index < 0)
			{
				throw ArgumentOutOfRangeException("index", "Non-negative number required.");
			}
			if (count < 0)
			{
				throw ArgumentOutOfRangeException("count", "Non-negative number required.");
			}
			if ((Array::Length(buffer) - index) < count)
			{
				throw ArgumentException("Invalid offset or length.");
			}
			_buffer = buffer;
			_origin = _position = index;
			_length = _capacity = index + count;
			_writable = writable;
			_exposable = false;
			_expandable = true;
			_isOpen = true;
		}

		MemoryStream::MemoryStream(byte buffer[], int index, int count, bool writable, bool publiclyVisible)
		{
			if (buffer == null)
			{
				throw ArgumentNullException("buffer", "Buffer was NULL.");
			}
			if (index < 0)
			{
				throw ArgumentOutOfRangeException("index", "Non-negative number required.");
			}
			if (count < 0)
			{
				throw ArgumentOutOfRangeException("count", "Non-negative number required.");
			}
			if ((Array::Length(buffer) - index) < count)
			{
				throw ArgumentException("Invalid offset or length.");
			}
			_buffer = buffer;
			_origin = _position = index;
			_length = _capacity = index + count;
			_writable = writable;
			_exposable = publiclyVisible;
			_expandable = true;
			_isOpen = true;
		}

		void MemoryStream::Dispose(bool disposing)
		{
			if (disposing)
			{
				_isOpen = false;
				_writable = false;
				_expandable = false;
			}
			Stream::Dispose(disposing);
		}

		bool MemoryStream::EnsureCapacity(int value)
		{
			if (value < 0)
			{
				throw IOException("Stream too long.");
			}
			if (value <= _capacity)
			{
				return false;
			}
			int num = value;
			if (num < 0x100)
			{
				num = 0x100;
			}
			if (num < (_capacity * 2))
			{
				num = _capacity * 2;
			}
			_capacity = num;
			return true;
		}

		void MemoryStream::Flush()
		{
		}

		byte* MemoryStream::GetBuffer()
		{
			if (!_exposable)
			{
				throw UnauthorizedAccessException("Unauthorized access to this MemoryStream buffer.");
			}
			return _buffer;
		}

		int MemoryStream::Read(byte buffer[], int offset, int count)
		{
			if (!_isOpen)
			{
				throw ObjectDisposedException(null, "Stream is closed.");
			}
			if (_buffer == null)
			{
				throw ArgumentNullException("buffer", "Buffer was null.");
			}
			if (offset < 0)
			{
				throw ArgumentOutOfRangeException("offset", "Non-negative number required.");
			}
			if (count < 0)
			{
				throw ArgumentOutOfRangeException("count", "Non-negative number required.");
			}
			if ((Array::Length(buffer) - offset) < count)
			{
				throw ArgumentException("Invalid offset or length.");
			}
			int num = _length - _position;
			if (num > count)
			{
				num = count;
			}
			if (num <= 0)
			{
				return 0;
			}
			if (num <= 8)
			{
				int num2 = num;
				while (--num2 >= 0)
				{
					buffer[offset + num2] = _buffer[_position + num2];
				}
			}
			else
			{
				Buffer::BlockCopy(_buffer, _position, buffer, offset, num);
			}
			_position += num;
			return num;
		}

		int MemoryStream::ReadByte()
		{
			if (!_isOpen)
			{
				throw ObjectDisposedException(null, "Stream is closed.");
			}
			if (_position >= _length)
			{
				return -1;
			}
			return _buffer[_position++];
		}

		Int64 MemoryStream::Seek(Int64 offset, SeekOrigin_t loc)
		{
			if (!_isOpen)
			{
				throw ObjectDisposedException(null, "Stream is closed.");
			}
			if (offset > MemStreamMaxLength)
			{
				throw ArgumentOutOfRangeException("offset", "offset is greater than the maximum length of this Stream.");
			}
			switch (loc)
			{
			case SeekOrigin::Begin:
				if (offset < 0LL)
				{
					throw IOException("Attempting to seek before the start of the Stream.");
				}
				_position = _origin + ((int)offset);
				break;

			case SeekOrigin::Current:
				if ((offset + _position) < _origin)
				{
					throw IOException("Attempting to seek before the start of the Stream.");
				}
				_position += ((int)offset);
				break;

			case SeekOrigin::End:
				if ((_length + offset) < _origin)
				{
					throw IOException("Attempting to seek before the start of the Stream.");
				}
				_position = _length + ((int)offset);
				break;

			default:
				throw ArgumentException("Invalid SeekOrigin.");
			}
			return (Int64)_position;
		}

		void MemoryStream::SetLength(Int64 value)
		{
			if (!_writable)
			{
				throw NotSupportedException("This Stream does not support writing.");
			}
			if (value > MemStreamMaxLength)
			{
				throw ArgumentOutOfRangeException("value", "offset is greater than the maximum length of this Stream.");
			}
			if ((value < 0LL) || (value > (MemStreamMaxLength - _origin)))
			{
				throw ArgumentOutOfRangeException("value", "offset is greater than the maximum length of this Stream.");
			}
			int num = _origin + ((int)value);
			if (!EnsureCapacity(num) && (num > _length))
			{
				Array::Clear(_buffer, _length, num - _length);
			}
			_length = num;
			if (_position > num)
			{
				_position = num;
			}
		}

		byte* MemoryStream::ToArray()
		{
			byte* dst = new byte[_length - _origin];
			Buffer::BlockCopy(_buffer, _origin, dst, 0, _length - _origin);
			return dst;
		}

		void MemoryStream::Write(byte buffer[], int offset, int count)
		{
			if (!_isOpen)
			{
				throw ObjectDisposedException(null, "Stream is closed.");
			}
			if (!_writable)
			{
				throw NotSupportedException("This Stream does not support writing.");
			}
			if (_buffer == null)
			{
				throw ArgumentNullException("buffer", "Buffer was null.");
			}
			if (offset < 0)
			{
				throw ArgumentOutOfRangeException("offset", "Non-negative number required.");
			}
			if (count < 0)
			{
				throw ArgumentOutOfRangeException("count", "Non-negative number required.");
			}
			if ((Array::Length(buffer) - offset) < count)
			{
				throw ArgumentException("Invalid offset or length.");
			}
			int num = _position + count;
			if (num < 0)
			{
				throw IOException("Stream too long");
			}
			if (num > _length)
			{
				bool flag = _position > _length;
				if ((num > _capacity) && EnsureCapacity(num))
				{
					flag = false;
				}
				if (flag)
				{
					Array::Clear(_buffer, _length, num - _length);
				}
				_length = num;
			}
			if (count <= 8)
			{
				int num2 = count;
				while (--num2 >= 0)
				{
					_buffer[_position + num2] = buffer[offset + num2];
				}
			}
			else
			{
				Buffer::BlockCopy(buffer, offset, _buffer, _position, count);
			}
			_position = num;
		}

		void MemoryStream::WriteByte(byte value)
		{
			if (!_isOpen)
			{
				throw ObjectDisposedException(null, "Stream is closed.");
			}
			if (!_writable)
			{
				throw NotSupportedException("This Stream does not support writing.");
			}
			if (_position >= _length)
			{
				int num = _position + 1;
				bool flag = _position > _length;
				if ((num >= _capacity) && EnsureCapacity(num))
				{
					flag = false;
				}
				if (flag)
				{
					Array::Clear(_buffer, _length, _position - _length);
				}
				_length = num;
			}
			_buffer[_position++] = value;
		}

		void MemoryStream::WriteTo(Stream stream)
		{
			if (!_isOpen)
			{
				throw ObjectDisposedException(null, "Stream is closed.");
			}
			stream.Write(_buffer, _origin, _length - _origin);
		}
	}
}
