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

#include <System/Windows/Window.h>
#include <System/Type.h>

#include "memutil.h"

namespace System
{
	namespace Windows
	{
		const Size Window::MaxSize = Size(640, 480);

		const Type WindowTypeInfo("Window", "System::Windows::Window", TypeCode::Object);

		Window::Window()
			: renderBuffer(new uint[MaxSize.Width * MaxSize.Height]),
			Height(MaxSize.Height / 2),
			Visibility(Visibility::Collapsed),
			Width(MaxSize.Width / 2),
			WindowState(WindowState::Normal)
		{
		}

		Window::~Window()
		{
			delete[] renderBuffer;
			delete Content;
		}

		void Window::Close()
		{
			ClosingEventArgs* clea = new ClosingEventArgs();
			clea->IsCancelable = true;
			Closing(this, clea);
			
			// signal the compositor to kill the window

			delete clea;
		}

		Window* Window::Create(const int left, const int top, const String& title)
		{
			Window* wnd = new Window();
			wnd->Left = left;
			wnd->Title = title;
			wnd->Top = top;
			wnd->TopMost = true;
			return wnd;
		}

		const Type& Window::GetType()
		{
			return WindowTypeInfo;
		}

		void Window::Hide()
		{
			Visibility = Visibility::Collapsed;
		}

		void Window::Render()
		{
			// if we aren't visible, don't bother to render
			if (Visibility != Visibility::Visible)
			{
				return;
			}

			// clear the window buffer
			memsetd(renderBuffer, 0, MaxSize.Width * MaxSize.Height);

			// render the window
			if (this->WindowStyle == WindowStyle::SingleBorderWindow)
			{
			}
			else if (this->WindowStyle == WindowStyle::BorderlessRoundCornersWindow)
			{
			}

			// Sort the children back-to-front
				
			// Layout all children

			// Render all children

			// Signal the Compositor that this window is ready to be rendered.
		}

		void Window::Show()
		{
			Visibility = Visibility::Visible;
		}

		const String Window::ToString() const
		{
			return Title;
		}
	}
}
