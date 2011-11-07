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
#include <System/IO/MemoryStream.h>

#if DEBUG
#include <stdio.h>
#endif

namespace System
{
	namespace IO
	{
		const int MemoryStream::MemStreamMaxLength = 0x7fffffff;

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
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "MemoryStream", "Stream is closed.");
#endif
				return -1;
			}
			return (_capacity - _origin);
		}

		void MemoryStream::Capacity(int value)
		{
			if (!_isOpen)
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "MemoryStream", "Stream is closed.");
#endif
				return;
			}
			if (value != _capacity)
			{
				if (!_expandable)
				{
#if DEBUG
					printf("NOT_SUPPORTED in function %s, at line %i in file %s\n", __FUNCTION__, __LINE__, __FILE__);
#endif
					return;
				}
				if (value < _length)
				{
#if DEBUG
					printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "value");
#endif
					return;
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
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "capacity", "Negative capacity is not allowed.");
#endif
				return;
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
			if (!buffer)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "buffer", "Buffer was NULL.");
#endif
				return;
			}
			_buffer = buffer;
			_length = _capacity = Array::Length(buffer);
			_expandable = false;
			_writable = true;
			_exposable = false;
			_origin = 0;
			_isOpen = true;
		}

		MemoryStream::MemoryStream(byte buffer[], bool writable)
		{
			if (!buffer)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "buffer", "Buffer was NULL.");
#endif
				return;
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
			if (!buffer)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "buffer", "Buffer was NULL.");
#endif
				return;
			}
			if (index < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "index", "Non-negative number required.");
#endif
				return;
			}
			if (count < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "count", "Non-negative number required.");
#endif
				return;
			}
			if ((Array::Length(buffer) - index) < count)
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__,"Invalid offset or length.");
#endif
				return;
			}
			_buffer = new byte[count];
			Array::Copy(buffer, index, _buffer, 0, count);
			_origin = 0;
			_length = _capacity = count;
			_writable = true;
			_exposable = false;
			_expandable = false;
			_isOpen = true;
		}

		MemoryStream::MemoryStream(byte buffer[], int index, int count, bool writable)
		{
			if (buffer == null)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "buffer", "Buffer was NULL.");
#endif
				return;
			}
			if (index < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "index", "Non-negative number required.");
#endif
				return;
			}
			if (count < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "count", "Non-negative number required.");
#endif
				return;
			}
			if ((Array::Length(buffer) - index) < count)
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Invalid offset or length.");
#endif
				return;
			}
			_buffer = new byte[count];
			Array::Copy(buffer, index, _buffer, 0, count);
			_origin = 0;
			_length = _capacity = count;
			_writable = writable;
			_exposable = false;
			_expandable = true;
			_isOpen = true;
		}

		MemoryStream::MemoryStream(byte buffer[], int index, int count, bool writable, bool publiclyVisible)
		{
			if (buffer == null)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "buffer", "Buffer was NULL.");
#endif
				return;
			}
			if (index < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "index", "Non-negative number required.");
#endif
				return;
			}
			if (count < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "count", "Non-negative number required.");
#endif
				return;
			}
			if ((Array::Length(buffer) - index) < count)
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Invalid offset or length.");
#endif
				return;
			}
			_buffer = new byte[count];
			Array::Copy(buffer, index, _buffer, 0, count);
			_origin = 0;
			_length = _capacity = count;
			_writable = writable;
			_exposable = publiclyVisible;
			_expandable = false;
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
#if DEBUG
				printf("IO in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Stream too long.");
#endif
				return false;
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
#if DEBUG
				printf("UNAUTHORIZED_ACCESS in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Unauthorized access to this MemoryStream buffer.");
#endif
				return null;
			}
			return _buffer;
		}

		int MemoryStream::Read(byte buffer[], int offset, int count)
		{
			if (!_isOpen)
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "MemoryStream", "Stream is closed.");
#endif
				return -1;
			}
			if (!_buffer)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "buffer", "Buffer was null.");
#endif
				return -1;
			}
			if (offset < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "offset", "Non-negative number required.");
#endif
				return -1;
			}
			if (count < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "count", "Non-negative number required.");
#endif
				return -1;
			}
			if ((Array::Length(buffer) - offset) < count)
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Invalid offset or length.");
#endif
				return -1;
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
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "MemoryStream", "Stream is closed.");
#endif
				return -1;
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
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "MemoryStream", "Stream is closed.");
#endif
				return -1;
			}
			if (offset > MemStreamMaxLength)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "offset", "offset is greater than the maximum length of this Stream.");
#endif
				return -1;
			}
			switch (loc)
			{
			case SeekOrigin::Begin:
				if (offset < 0LL)
				{
#if DEBUG
					printf("IO in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Attempting to seek before the start of the Stream.");
#endif
					return -1;
				}
				_position = _origin + ((int)offset);
				break;

			case SeekOrigin::Current:
				if ((offset + _position) < _origin)
				{
#if DEBUG
					printf("IO in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Attempting to seek before the start of the Stream.");
#endif
					return -1;
				}
				_position += ((int)offset);
				break;

			case SeekOrigin::End:
				if ((_length + offset) < _origin)
				{
#if DEBUG
					printf("IO in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Attempting to seek before the start of the Stream.");
#endif
					return -1;
				}
				_position = _length + ((int)offset);
				break;

			default:
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Invalid SeekOrigin.");
#endif
				return -1;
			}
			return (Int64)_position;
		}

		void MemoryStream::SetLength(Int64 value)
		{
			if (!_writable)
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "This Stream does not support writing.");
#endif
				return;
			}
			if (value > MemStreamMaxLength)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "value", "offset is greater than the maximum length of this Stream.");
#endif
				return;
			}
			if ((value < 0LL) || (value > (MemStreamMaxLength - _origin)))
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "value", "offset is greater than the maximum length of this Stream.");
#endif
				return;
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
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "MemoryStream", "Stream is closed.");
#endif
				return;
			}
			if (!_writable)
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "This Stream does not support writing.");
#endif
				return;
			}
			if (!buffer)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "buffer", "Buffer was null.");
#endif
				return;
			}
			if (offset < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "offset", "Non-negative number required.");
#endif
			}
			if (count < 0)
			{
#if DEBUG
				printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "count", "Non-negative number required.");
#endif
			}
			if ((Array::Length(buffer) - offset) < count)
			{
#if DEBUG
				printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Invalid offset or length.");
#endif
				return;
			}
			int num = _position + count;
			if (num < 0)
			{
#if DEBUG
				printf("IO in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Stream too long");
#endif
				return;
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
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "MemoryStream", "Stream is closed.");
#endif
				return;
			}
			if (!_writable)
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "This Stream does not support writing.");
#endif
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

		void MemoryStream::WriteTo(Stream* stream)
		{
			if (!_isOpen)
			{
#if DEBUG
				printf("OBJECT_DISPOSED in function %s, at line %i in file %s, object %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "MemoryStream", "Stream is closed.");
#endif
				return;
			}
			stream->Write(_buffer, _origin, _length - _origin);
		}
	}
}
