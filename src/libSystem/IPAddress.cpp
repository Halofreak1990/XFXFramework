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

#include <System/Net/IPAddress.h>

namespace System
{
	namespace Net
	{
		const IPAddress IPAddress::Loopback(0x7F000001);

		int IPAddress::HostToNetworkOrder(int host)
		{
#if ENABLE_XBOX
			return (((host & 0xFF) << 24) | ((host >> 8) & 0xFF) << 16 | ((host >> 16) & 0xFF) << 8 | (host >> 24) & 0xFF);
#else
#endif
		}

		long long IPAddress::HostToNetworkOrder(long long host)
		{
#if ENABLE_XBOX
			return (((host & 0xFF) << 56) | ((host >> 8) & 0xFF) << 48 |
					((host >> 16) & 0xFF) << 40 | ((host >> 24) & 0xFF) << 32 |
					((host >> 32) & 0xFF) << 24 | ((host >> 40) & 0xFF) << 16 |
					((host >> 48) & 0xFF) << 8 | (host >> 56) & 0xFF);
#else
#endif
		}

		short IPAddress::HostToNetworkOrder(short host)
		{
#if ENABLE_XBOX
			return (((host & 0xFF) << 8) | ((host >> 8) & 0xFF));
#else
#endif
		}
	}
}
