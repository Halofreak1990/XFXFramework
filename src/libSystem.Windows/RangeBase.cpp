// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
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

#include <System/Windows/Controls/Primitives/RangeBase.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				const Type RangeBaseTypeInfo("RangeBase", "System::Windows::Controls::Primitives::RangeBase", TypeCode::Object);

				int RangeBase::getMaximum() const
				{
					return maximum;
				}

				void RangeBase::setMaximum(const int value)
				{
					if (maximum != value)
					{
						OnMaximumChanged(maximum, value);
						maximum = value;
					}
				}

				int RangeBase::getMinimum() const
				{
					return minimum;
				}

				void RangeBase::setMinimum(const int value)
				{
					if (minimum != value)
					{
						OnMinimumChanged(minimum, value);
						minimum = value;
					}
				}

				int RangeBase::getValue() const
				{
					return value;
				}

				void RangeBase::setValue(const int value)
				{
					if (this->value != value)
					{
						OnValueChanged(this->value, value);
						this->value = value;
					}
				}

				RangeBase::RangeBase()
				{
					// TODO: implement
				}

				const Type& RangeBase::GetType()
				{
					return RangeBaseTypeInfo;
				}

				void RangeBase::OnValueChanged(int oldValue, int newValue)
				{
					ValueChanged(this, new RoutedPropertyChangedEventArgs<int>(oldValue, newValue));
				}

				const String RangeBase::ToString() const
				{
					return String::Format("{RangeBase Minimum:%i Maximum:%i Value:%i}", minimum, maximum, value);
				}
			}
		}
	}
}
