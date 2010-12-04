/********************************************************
 *	GraphicsDeviceCapabilities.h						*
 *														*
 *	XFX GraphicsDeviceCapabilities definition file		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _GRAPHICSDEVICECAPABILITIES_
#define _GRAPHICSDEVICECAPABILITIES_

#include <System.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Represents the capabilities of the hardware.
		/// </summary>
		class GraphicsDeviceCapabilities : IDisposable
		{
		protected:
			void Dispose(bool disposing);

		public:
			struct BlendCaps;
			struct CompareCaps;
			struct CursorCaps;
			struct DeclarationTypeCaps;
			struct DeviceCaps;
			struct DriverCaps;
			struct FilterCaps;
		
			int AdapterOrdinalInGroup();
			CompareCaps AlphaCompareCapabilities();
			FilterCaps CubeTextureFilterCapabilities();
			CursorCaps CursorCapabilities();
			DeclarationTypeCaps DeclarationTypeCapabilities();
			CompareCaps DepthBufferCompareCapabilities();
			BlendCaps DestinationBlendCapabilities();
			DeviceCaps DeviceCapabilities();
			DeviceType_t DeviceType_();
			DriverCaps DriverCapabilities();

			void Dispose();
		
			int operator!=(GraphicsDeviceCapabilities other);
			int operator==(GraphicsDeviceCapabilities other);
			
		public:
			/// <summary>
			/// Represents the texture addressing capabilities for Texture structures.
			/// </summary>
			struct AddressCaps
			{
				bool SupportsBorder();
				bool SupportsClamp();
				bool SupportsIndependentUV();
				bool SupportsMirror();
				bool SupportsMirrorOnce();
				bool SupportsWrap();

				bool Equals(AddressCaps obj);
				int GetHashCode();
				char* ToString();

				bool operator!=(AddressCaps other);
				bool operator==(AddressCaps other);
			};
			/// <summary>
			/// Represents the supported blend capabilities.
			/// </summary>
			struct BlendCaps
			{
				int SupportsBlendFactor();
				int SupportsBothInverseSourceAlpha();
				int SupportsBothSourceAlpha();
				int SupportsDestinationAlpha();
				
				bool Equals(BlendCaps obj);
				int GetHashCode();
				char* ToString();
				
				int operator!=(BlendCaps other);
				int operator==(BlendCaps other);
			};
			/// <summary>
			/// Represents comparison capabilities.
			/// </summary>
			struct CompareCaps
			{
				bool SupportsAlways();
				bool SupportsEqual();
				bool SupportsGreater();
				bool SupportsGreaterEqual();
				bool SupportsLess();
				bool SupportsLessEqual();
				bool SupportsNever();
				bool SupportsNotEqual();

				bool Equals(CompareCaps obj);
				int GetHashCode();
				char* ToString();

				bool operator!=(CompareCaps other);
				bool operator==(CompareCaps other);
			};
			/// <summary>
			/// Represents hardware support for cursors.
			/// </summary>
			struct CursorCaps
			{
				bool SupportsColor();
				bool SupportsLowResolution();

				bool Equals(CursorCaps obj);
				int GetHashCode();
				char* ToString();

				bool operator!=(CursorCaps other);
				bool operator==(CursorCaps other);
			};
			/// <summary>
			/// Represents data types contained in a vertex declaration.
			/// </summary>
			struct DeclarationTypeCaps
			{
				bool SupportsByte4();
				bool SupportsHalfVector2();
				bool SupportsHalfVector4();
				bool SupportsNormalized101010();
				bool SupportsNormalizedShort2();
				bool SupportsNormalizedShort4();
				bool SupportsRg32();
				bool SupportsRgba32();
				bool SupportsRgba64();
				bool SupportsUInt101010();

				bool Equals(DeclarationTypeCaps obj);
				int GetHashCode();
				char* ToString();

				bool operator!=(DeclarationTypeCaps other);
				bool operator==(DeclarationTypeCaps other);
			};
			/// <summary>
			/// Represents device-specific capabilities.
			/// </summary>
			struct DeviceCaps
			{
				bool CanDrawSystemToNonLocal();
				bool CanRenderAfterFlip();
				bool IsDirect3D9Driver();
				bool SupportsDrawPrimitives2();
				bool SupportsDrawPrimitives2Ex();

				bool Equals(DeviceCaps obj);
				int GetHashCode();
				char* ToString();

				bool operator!=(DeviceCaps other);
				bool operator==(DeviceCaps other);
			};
			/// <summary>
			/// Represents texture filter capabilities.
			/// </summary>
			struct FilterCaps
			{
				bool Equals(FilterCaps obj);
				int GetHashCode();
				char* ToString();

				bool operator!=(FilterCaps other);
				bool operator==(FilterCaps other);
			};
		};
	}
}

#endif //_GRAPHICSDEVICECAPABILITIES_
