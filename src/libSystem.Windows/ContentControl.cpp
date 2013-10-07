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

#include <System/Windows/Controls/ContentControl.h>
#include <System/Type.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			const DependencyProperty<Object *> ContentControl::ContentProperty = DependencyProperty<Object *>::Register("Content", ContentControl::GetType());
			const DependencyProperty<String> ContentControl::ContentStringFormatProperty = DependencyProperty<String>::Register("ContentStringFormat", ContentControl::GetType());
			const Type ContentControlTypeInfo("ContentControl", "System::Windows::Controls::ContentControl", TypeCode::Object);

			bool ContentControl::HasContent() const
			{
				return Content != NULL;
			}

			ContentControl::ContentControl()
			{
				// TODO: implement
			}

			void ContentControl::AddChild(Object * const value)
			{
				// TODO: implement
			}

			void ContentControl::AddText(const String& text)
			{
				// TODO: implement
			}

			const Type& ContentControl::GetType()
			{
				return ContentControlTypeInfo;
			}

			void ContentControl::OnContentChanged(Object * const newContent, Object * const oldContent)
			{
				// TODO: implement
			}
		}
	}
}
