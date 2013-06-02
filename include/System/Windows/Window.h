#ifndef _SYSTEM_WINDOWS_WINDOW_
#define _SYSTEM_WINDOWS_WINDOW_

#include <System/Event.h>
#include <System/String.h>
#include <System/ComponentModel/ClosingEventArgs.h>
#include <System/Windows/Size.h>
#include <System/Windows/Enums.h>
#include <System/Windows/FrameworkElement.h>

using namespace System::ComponentModel;

namespace System
{
	namespace Windows
	{
		class Window : public Object
		{
		private:
			static const Size MaxSize;
			uint* renderBuffer;

		public:
			FrameworkElement* Content;
			int Height;
			bool IsActive() const;
			int Left;
			String Title;
			int Top;
			bool TopMost;
			Visibility_t Visibility;
			int Width;
			WindowState_t WindowState;
			WindowStyle_t WindowStyle;

			Event<Object * const, ClosingEventArgs * const> Closing;

			Window();
			~Window();

			void Close();
			static Window* Create(const int left, const int top, const String& title);
			int GetType() const;
			void Hide();
			void Render();
			void Show();
			const String& ToString() const;
		};
	}
}

#endif //_SYSTEM_WINDOWS_WINDOW_
