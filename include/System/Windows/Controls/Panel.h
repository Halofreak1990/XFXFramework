/*****************************************************************************
 *	Panel.h 																 *
 *																			 *
 *	XFX System::Windows::Controls::Panel class definition file  			 *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_CONTROLS_PANEL_
#define _SYSTEM_WINDOWS_CONTROLS_PANEL_

#include <System/Windows/FrameworkElement.h>
#include <System/Windows/Controls/UIElementCollection.h>
#include <System/Windows/Media/Brush.h>

using namespace System::Windows::Media;

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			/**
			 * Provides a base class for all System::Windows::Controls::Panel elements. Use System::Windows::Controls::Panel elements to position and arrange child objects in applications.
			 */
			class Panel : public FrameworkElement
			{
			protected:
				Panel();

			public:
				Brush* Background;
				UIElementCollection Children;
				bool IsItemsHost() const;

				virtual ~Panel();

				static const Type& GetType();

				bool operator==(const Panel& right) const;
				bool operator!=(const Panel& right) const;
			};
		}
	}
}

#endif //_SYSTEM_WINDOWS_CONTROLS_PANEL_
