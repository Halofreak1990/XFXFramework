#ifndef _XFX_GRAPHICS_ENUMS_LEGACY_
#define _XFX_GRAPHICS_ENUMS_LEGACY_

namespace XFX
{
	namespace Graphics
	{
		struct SurfaceFormat_Legacy
		{
			enum type
			{
				Unknown = -1,
				Color = 1,
				Bgr32 = 2,
				Bgra1010102 = 3,
				Rgba32 = 4,
				Rgb32 = 5,
				Rgba1010102 = 6,
				Rg32 = 7,
				Rgba64 = 8,
				Bgr565 = 9,
				Bgra5551 = 10,
				Bgr555 = 11,
				Bgra4444 = 12,
				Bgr444 = 13,
				Bgra2338 = 14,
				Alpha8 = 15,
				Bgr233 = 16,
				Bgr24 = 17,
				NormalizedByte2 = 18,
				NormalizedByte4 = 19,
				NormalizedShort2 = 20,
				NormalizedShort4 = 21,
				Single = 22,
				Vector2 = 23,
				Vector4 = 24,
				HalfSingle = 25,
				HalfVector2 = 26,
				HalfVector4 = 27,
				Dxt1 = 28,
				Dxt2 = 29,
				Dxt3 = 30,
				Dxt4 = 31,
				Dxt5 = 32,
				Luminance8 = 33,
				Luminance16 = 34,
				LuminanceAlpha8 = 35,
				LuminanceAlpha16 = 36,
				Palette8 = 37,
				PaletteAlpha16 = 38,
				NormalizedLuminance16 = 39,
				NormalizedLuminance32 = 40,
				NormalizedAlpha1010102 = 41,
				NormalizedByte2Computed = 42,
				VideoYuYv = 43,
				VideoUyVy = 44,
				VideoGrGb = 45,
				VideoRgBg = 46,
				Multi2Bgra32 = 47,
				Depth24Stencil8 = 48,
				Depth24Stencil8Single = 49,
				Depth24Stencil4 = 50,
				Depth24 = 51,
				Depth32 = 52,
				Depth16 = 54,
				Depth15Stencil1 = 56,
			};
		};

		typedef SurfaceFormat_Legacy::type	SurfaceFormat_Legacy_t;
	}
}

#endif //_XFX_GRAPHICS_ENUMS_LEGACY_