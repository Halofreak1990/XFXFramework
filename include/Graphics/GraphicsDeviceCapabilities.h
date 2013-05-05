/********************************************************
 *	GraphicsDeviceCapabilities.h						*
 *														*
 *	XFX GraphicsDeviceCapabilities definition file		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_GRAPHICSDEVICECAPABILITIES_
#define _XFX_GRAPHICS_GRAPHICSDEVICECAPABILITIES_

#include <System.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		// Represents the capabilities of the hardware.
		class GraphicsDeviceCapabilities : public IDisposable, virtual Object
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
			DeviceType_t getDeviceType();
			DriverCaps DriverCapabilities();

			void Dispose();
			bool Equals(const GraphicsDeviceCapabilities obj) const;
			int GetHashCode() const;
			char* ToString() const;
		
			bool operator!=(const GraphicsDeviceCapabilities other) const;
			bool operator==(const GraphicsDeviceCapabilities other) const;
			
		public:
			// Represents the texture addressing capabilities for Texture structures.
			struct AddressCaps : virtual Object
			{
				bool SupportsBorder();
				bool SupportsClamp();
				bool SupportsIndependentUV();
				bool SupportsMirror();
				bool SupportsMirrorOnce();
				bool SupportsWrap();

				bool Equals(const AddressCaps obj) const;
				int GetHashCode() const;
				char* ToString() const;

				bool operator!=(const AddressCaps other) const;
				bool operator==(const AddressCaps other) const;
			};

			// Represents the supported blend capabilities.
			struct BlendCaps : virtual Object
			{
				int SupportsBlendFactor();
				int SupportsBothInverseSourceAlpha();
				int SupportsBothSourceAlpha();
				int SupportsDestinationAlpha();
				
				bool Equals(const BlendCaps obj) const;
				int GetHashCode() const;
				char* ToString() const;
				
				bool operator!=(const BlendCaps other) const;
				bool operator==(const BlendCaps other) const;
			};

			// Represents comparison capabilities.
			struct CompareCaps : virtual Object
			{
				bool SupportsAlways();
				bool SupportsEqual();
				bool SupportsGreater();
				bool SupportsGreaterEqual();
				bool SupportsLess();
				bool SupportsLessEqual();
				bool SupportsNever();
				bool SupportsNotEqual();

				bool Equals(const CompareCaps obj) const;
				int GetHashCode() const;
				char* ToString() const;

				bool operator!=(const CompareCaps other) const;
				bool operator==(const CompareCaps other) const;
			};

			// Represents hardware support for cursors.
			struct CursorCaps
			{
				bool SupportsColor();
				bool SupportsLowResolution();

				bool Equals(const CursorCaps obj) const;
				int GetHashCode() const;
				char* ToString() const;

				bool operator!=(const CursorCaps other) const;
				bool operator==(const CursorCaps other) const;
			};

			// Represents data types contained in a vertex declaration.
			struct DeclarationTypeCaps : virtual Object
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

				bool Equals(const DeclarationTypeCaps obj) const;
				int GetHashCode() const;
				char* ToString() const;

				bool operator!=(const DeclarationTypeCaps other) const;
				bool operator==(const DeclarationTypeCaps other) const;
			};

			// Represents device-specific capabilities.
			struct DeviceCaps : virtual Object
			{
				bool CanDrawSystemToNonLocal();
				bool CanRenderAfterFlip();
				bool IsDirect3D9Driver();
				bool SupportsDrawPrimitives2();
				bool SupportsDrawPrimitives2Ex();

				bool Equals(const DeviceCaps obj) const;
				int GetHashCode() const;
				char* ToString() const;

				bool operator!=(const DeviceCaps other) const;
				bool operator==(const DeviceCaps other) const;
			};

			// Represents texture filter capabilities.
			struct FilterCaps
			{
				bool Equals(const FilterCaps obj) const;
				int GetHashCode() const;
				char* ToString() const;

				bool operator!=(const FilterCaps other) const;
				bool operator==(const FilterCaps other) const;
			};
		};
	}
}

#endif //_XFX_GRAPHICS_GRAPHICSDEVICECAPABILITIES_
