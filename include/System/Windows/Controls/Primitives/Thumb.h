/*****************************************************************************
 *	Thumb.h 																 *
 *																			 *
 *	System::Windows::Controls::Primitives::Thumb definition file			 *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_THUMB_
#define _SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_THUMB_

#include <System/Windows/Controls/Control.h>
#include <System/Windows/Controls/Enums.h>
#include <System/Windows/Controls/Primitives/DragCompletedEventArgs.h>
#include <System/Windows/Controls/Primitives/DragDeltaEventArgs.h>
#include <System/Windows/Controls/Primitives/DragStartedEventArgs.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				/**
				 * Represents a control that can be dragged by the user.
				 */
				class Thumb : public Control
				{
				protected:
					void OnGotFocus(RoutedEventArgs * const e);
					void OnLostFocus(RoutedEventArgs * const e);
					void OnMouseEnter(MouseEventArgs * const e);
					void OnMouseLeave(MouseEventArgs * const e);
					void OnMouseMove(MouseEventArgs * const e);

				public:
					ClickMode_t ClickMode;

					Thumb();

					void CancelDrag();
					static const Type& GetType();

					bool operator ==(const Thumb& right) const;
					bool operator !=(const Thumb& right) const;

					DragCompletedEventHandler DragCompleted;
				};
			}
		}
	}
}

#endif //_SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_THUMB_
