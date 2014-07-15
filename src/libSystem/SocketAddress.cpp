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

#include <System/Int32.h>
#include <System/Net/SocketAddress.h>
#include <System/String.h>
#include <System/Type.h>

#include <sassert.h>

namespace System
{
	namespace Net
	{
		const Type SocketAddressTypeInfo("SocketAddress", "System::Net::SocketAddress", TypeCode::Object);

		AddressFamily_t SocketAddress::getFamily()
		{
			return (AddressFamily_t)(data[0] + (data[1] << 8));
		}

		int SocketAddress::getSize()
		{
			return data.Length;
		}

		SocketAddress::SocketAddress(AddressFamily_t family)
			: data(32)
		{
			data[0] = (byte)family;
			data[1] = (byte)((int)family >> 8);
		}

		SocketAddress::SocketAddress(AddressFamily_t family, int size)
			: data(size)
		{
			sassert(size >= 2, "size is too small");

			data[0] = (byte)family;
			data[1] = (byte)((int)family >> 8);
		}

		bool SocketAddress::Equals(Object const * const obj) const
		{
			SocketAddress* sa = as<SocketAddress *>(obj);

			if (sa != NULL && sa->data.Length == data.Length)
			{
				for (int i = 0; i < data.Length; i++)
				{
					if (data[i] != sa->data[i])
					{
						return false;
					}
				}

				return true;
			}

			return false;
		}

		int SocketAddress::GetHashCode() const
		{
			int code = 0;

			for (int i = 0; i < data.Length; i++)
			{
				code += data[i] + i;
			}

			return code;
		}

		const Type& SocketAddress::GetType()
		{
			return SocketAddressTypeInfo;
		}

		const String SocketAddress::ToString()
		{
			String af;

			switch ((AddressFamily_t)data[0])
			{
			case AddressFamily::InterNetwork:
				af = "InterNetwork";
				break;
			case AddressFamily::InterNetworkV6:
				af = "InterNetworkV6";
				break;
			case AddressFamily::Unknown:
				af = "Unknown";
				break;
			case AddressFamily::Unspecified:
				af = "Unspecified";
				break;
			}

			int size = data.Length;
			String ret = af + ":" + Int32::ToString(size) + ":{";

			for (int i = 2; i < size; i++)
			{
				int val = (int)data[i];
				ret = ret + val;

				if (i < size - 1)
				{
					ret = ret + ",";
				}
			}

			ret = ret + "}";

			return(ret);
		}

		const byte& SocketAddress::operator[](const int index) const
		{
			return data[index];
		}

		byte& SocketAddress::operator[](const int index)
		{
			return data[index];
		}
	}
}
