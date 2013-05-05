#pragma once

#include <System/Windows/Media/Color.h>

using namespace System::Windows::Media;

namespace System
{
	namespace Windows
	{
		// Contains system colors, system brushes, and system resource keys that correspond to system display elements.
		class SystemColors
		{
		private:
			SystemColors();

		public:
			static const Color ControlColor;
			static const Color ControlDarkColor;
			static const Color ControlDarkDarkColor;
			static const Color ControlLightColor;
			static const Color ControlLightLightColor;
			static const Color ControlTextColor;
			static const Color DeskTopColor;
			static const Color GrayTextColor;
			static const Color HighlightColor;
			static const Color HighlightTextColor;
			static const Color InactiveBorderColor;
			static const Color InactiveCaptionColor;
			static const Color InactiveCaptionTextColor;
			static const Color InfoColor;
			static const Color InfoTextColor;
			static const Color MenuColor;
			static const Color MenuTextColor;
			static const Color ScrollBarColor;
			static const Color WindowColor;
			static const Color WindowFrameColor;
			static const Color WindowTextColor;
		};
	}
}
