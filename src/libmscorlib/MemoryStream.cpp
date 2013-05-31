// Copyright (C) XFX Team
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
#include <System/FrameworkResources.h>
#include <System/String.h>
#include <System/IO/MemoryStream.h>

#include <sassert.h>
#include <string.h>

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

		int MemoryStream::getCapacity()
		{
			sassert(_isOpen, FrameworkResources::ObjectDisposed_StreamClosed);

			return (_capacity - _origin);
		}

		void MemoryStream::setCapacity(int value)
		{
			sassert(_isOpen, FrameworkResources::ObjectDisposed_StreamClosed);

			if (value != _capacity)
			{
				sassert(_expandable, FrameworkResources::NotSupported_MemStreamNotExpandable);

				sassert(value >= _length, FrameworkResources::ArgumentOutOfRange_SmallCapacity);

				if (value > 0)
				{
					byte* dst = new byte[value];
					if (_length > 0)
					{
						memcpy(dst, _buffer, _length);
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
			sassert(capacity >= 0, FrameworkResources::ArgumentOutOfRange_NegativeCapacity);

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
			sassert(buffer != null, FrameworkResources::ArgumentNull_Buffer);

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
			sassert(buffer != null, FrameworkResources::ArgumentNull_Buffer);

			_buffer = buffer;
			_length = _capacity = Array::Length(buffer);
			_writable = writable;
			_exposable = false;
			_origin = 0;
			_isOpen = true;
		}

		MemoryStream::MemoryStream(byte buffer[], int index, int count)
		{
			sassert(buffer != null, FrameworkResources::ArgumentNull_Buffer);

			sassert(index >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "index"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(count >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "count"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(!((Array::Length(buffer) - index) < count), FrameworkResources::Argument_InvalidOffLen);

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
			sassert(buffer != null, FrameworkResources::ArgumentNull_Buffer);

			sassert(index >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "index"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(count >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "count"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(!((Array::Length(buffer) - index) < count), FrameworkResources::Argument_InvalidOffLen);

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
			sassert(buffer != null, FrameworkResources::ArgumentNull_Buffer);

			sassert(index >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "index"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(count >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "count"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(!((Array::Length(buffer) - index) < count), FrameworkResources::Argument_InvalidOffLen);

			_buffer = new byte[count];
			Array::Copy(buffer, index, _buffer, 0, count);
			_origin = 0;
			_length = _capacity = count;
			_writable = writable;
			_exposable = publiclyVisible;
			_expandable = false;
			_isOpen = true;
		}

		MemoryStream::~MemoryStream()
		{
			delete[] _buffer;
			_buffer = null;
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
			sassert(value > 0, FrameworkResources::IO_StreamTooLong);

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
			sassert(_exposable, FrameworkResources::UnauthorizedAccess_MemStreamBuffer);

			return _buffer;
		}

		int MemoryStream::Read(byte buffer[], int offset, int count)
		{
			sassert(_isOpen, FrameworkResources::ObjectDisposed_StreamClosed);

			sassert(buffer != null, FrameworkResources::ArgumentNull_Buffer);

			sassert(offset >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "offset"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(count >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "count"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(!((Array::Length(buffer) - offset) < count), FrameworkResources::Argument_InvalidOffLen);

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
				memcpy(&_buffer[_position], &_buffer[offset], num);
			}
			_position += num;
			return num;
		}

		int MemoryStream::ReadByte()
		{
			sassert(_isOpen, FrameworkResources::ObjectDisposed_StreamClosed);

			if (_position >= _length)
			{
				return -1;
			}
			return _buffer[_position++];
		}

		Int64 MemoryStream::Seek(Int64 offset, SeekOrigin_t loc)
		{
			sassert(_isOpen, FrameworkResources::ObjectDisposed_StreamClosed);

			sassert(!(offset > MemStreamMaxLength), FrameworkResources::ArgumentOutOfRange_StreamLength);

			switch (loc)
			{
			case SeekOrigin::Begin:
				sassert(offset >= 0LL, FrameworkResources::IO_SeekBeforeBegin);

				_position = _origin + ((int)offset);
				break;

			case SeekOrigin::Current:
				sassert(!((offset + _position) < _origin), FrameworkResources::IO_SeekBeforeBegin);

				_position += ((int)offset);
				break;

			case SeekOrigin::End:
				sassert(!((_length + offset) < _origin), FrameworkResources::IO_SeekBeforeBegin);
				
				_position = _length + ((int)offset);
				break;

			default:
				sassert(false, FrameworkResources::Argument_InvalidSeekOrigin);
				break;
			}
			return (Int64)_position;
		}

		void MemoryStream::SetLength(Int64 value)
		{
			sassert(_writable, FrameworkResources::NotSupported_UnwritableStream);

			sassert(!((value < 0LL) || (value > MemStreamMaxLength)), FrameworkResources::ArgumentOutOfRange_StreamLength);

			sassert(!(value > (MemStreamMaxLength - _origin)), FrameworkResources::ArgumentOutOfRange_StreamLength);

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
			memcpy(dst, &_buffer[_origin], _length - _origin);
			return dst;
		}

		void MemoryStream::Write(byte buffer[], int offset, int count)
		{
			sassert(_isOpen, FrameworkResources::ObjectDisposed_StreamClosed);

			sassert(_writable, FrameworkResources::NotSupported_UnwritableStream);

			sassert(buffer != null, FrameworkResources::ArgumentNull_Buffer);

			sassert(offset >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "offset"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(count >= 0, String::Format("%s; %s", String::Format(FrameworkResources::Arg_ParamName_Name, "count"), FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

			sassert(!((Array::Length(buffer) - offset) < count), FrameworkResources::Argument_InvalidOffLen);

			int num = _position + count;
				
			sassert(num >= 0, FrameworkResources::IO_StreamTooLong);
			
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
				memcpy(&_buffer[_position], &buffer[offset], count);
			}
			_position = num;
		}

		void MemoryStream::WriteByte(byte value)
		{
			sassert(_isOpen, FrameworkResources::ObjectDisposed_StreamClosed);

			sassert(_writable, FrameworkResources::NotSupported_UnwritableStream);

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
			sassert(_isOpen, FrameworkResources::ObjectDisposed_StreamClosed);

			stream->Write(_buffer, _origin, _length - _origin);
		}
	}
}
