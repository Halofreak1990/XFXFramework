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

#include <System/Net/SocketAddress.h>
#include <System/String.h>
#include <System/Type.h>

namespace System
{
	namespace Net
	{
		const Type SocketAddressTypeInfo("SocketAddress", "System::Net::SocketAddress", TypeCode::Object);

		AddressFamily_t SocketAddress::getFamily()
		{
			return addressFamily;
		}

		int SocketAddress::getSize()
		{
			return bufferSize;
		}

		SocketAddress::SocketAddress(AddressFamily_t family)
			: addressFamily(family)
		{
			// TODO: implement remainder
		}

		SocketAddress::SocketAddress(AddressFamily_t family, int size)
			: addressFamily(family), bufferSize(size)
		{
			// TODO: implement remainder
		}

		const Type& SocketAddress::GetType()
		{
			return SocketAddressTypeInfo;
		}

		const String SocketAddress::ToString()
		{
			// TODO: implement
		}

		byte SocketAddress::operator[](int offset)
		{
			// TODO: implement
		}
	}
}
