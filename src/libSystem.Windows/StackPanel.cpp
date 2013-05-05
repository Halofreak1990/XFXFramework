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

#include <System/Math.h>
#include <System/Windows/Size.h>
#include <System/Windows/Controls/StackPanel.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			StackPanel::StackPanel()
				: Orientation(Orientation::Vertical)
			{
			}

			Size StackPanel::ArrangeOverride(const Size arrangeSize)
			{
				int horSize = 0;
				int vertSize = 0;

				if (this->Orientation == Orientation::Vertical)
				{
					for (int i = 0; i < Children.Count(); i++)
					{
						horSize = Math::Max(Children[i]->getRenderSize().Width, horSize);
						vertSize += Children[i]->getRenderSize().Height;
					}
				}
				else
				{
					for (int i = 0; i < Children.Count(); i++)
					{
						horSize += Children[i]->getRenderSize().Width;
						vertSize = Math::Max(Children[i]->getRenderSize().Height, vertSize);
					}
				}
				return Size(vertSize, horSize);
			}

			Size StackPanel::MeasureOverride(const Size constraint)
			{
				for (int i = 0; i < Children.Count(); i++)
				{
					Children[i]->Measure(constraint);
				}
			}
		}
	}
}
