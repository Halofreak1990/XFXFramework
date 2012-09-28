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

#include <System/DateTime.h>
#include <System/Globalization/Calendar.h>

namespace System
{
	namespace Globalization
	{
		DateTime Calendar::AddDays(DateTime time, int days)
		{
			DateTime result(time);
			result.AddDays((double)days);
			return result;
		}

		DateTime Calendar::AddHours(DateTime time, int hours)
		{
			DateTime result(time);
			result.AddHours((double)hours);
			return result;
		}

		DateTime Calendar::AddMilliseconds(DateTime time, double milliseconds)
		{
			DateTime result(time);
			result.AddMilliseconds(milliseconds);
			return result;
		}

		DateTime Calendar::AddMinutes(DateTime time, int minutes)
		{
			DateTime result(time);
			result.AddMinutes(minutes);
			return result;
		}

		DateTime Calendar::AddMonths(DateTime time, int months)
		{
			DateTime result(time);
			result.AddMonths(months);
			return result;
		}

		int Calendar::GetType() const
		{
			//! TODO: implement
		}
	}
}
