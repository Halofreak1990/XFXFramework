#include <System/Windows/Window.h>
#include "memutil.h"

namespace System
{
	namespace Windows
	{
		const Size Window::MaxSize = Size(640, 480);

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

		int Window::GetType() const
		{
			// TODO: implement
		}

		void Window::Hide()
		{
			Visibility = Visibility::Collapsed;
		}

		void Window::Render()
		{
			// if we aren't visible, don't bother to render
			if (Visibility == Visibility::Visible)
			{
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
		}

		void Window::Show()
		{
			Visibility = Visibility::Visible;
		}

		const char* Window::ToString() const
		{
			return Title.ToString();
		}
	}
}
