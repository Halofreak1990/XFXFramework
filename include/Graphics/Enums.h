/********************************************************
 *	Enums.h												*
 *														*
 *	XFX::Graphics enumeration definition file			*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_ENUMS_
#define _XFX_GRAPHICS_ENUMS_

namespace XFX
{
	namespace Graphics
	{
		// Defines color blending factors.
		struct Blend
		{
			enum type
			{
				// Each component of the color is multiplied by (1, 1, 1, 1).
				One = 0,
				// Each component of the color is multiplied by (0, 0, 0, 0).
				Zero = 1,
				// Each component of the color is multiplied by the source color. This can be represented as (Rs, Gs, Bs, As), where R, G, B, and A respectively stand for the red, green, blue, and alpha source values.
				SourceColor = 2,
				// Each component of the color is multiplied by the inverse of the source color. This can be represented as (1 ? Rs, 1 ? Gs, 1 ? Bs, 1 ? As) where R, G, B, and A respectively stand for the red, green, blue, and alpha destination values.
				InversourceColor = 3,
				// Each component of the color is multiplied by the alpha value of the source. This can be represented as (As, As, As, As), where As is the alpha source value.
				SourceAlpha = 4,
				// Each component of the color is multiplied by the inverse of the alpha value of the source. This can be represented as (1 ? As, 1 ? As, 1 ? As, 1 ? As), where As is the alpha destination value.
				InverseSourceAlpha = 5,
				// Each component color is multiplied by the destination color. This can be represented as (Rd, Gd, Bd, Ad), where R, G, B, and A respectively stand for red, green, blue, and alpha destination values.
				DestinationColor = 6,
				// Each component of the color is multiplied by the inverse of the destination color. This can be represented as (1 ? Rd, 1 ? Gd, 1 ? Bd, 1 ? Ad), where Rd, Gd, Bd, and Ad respectively stand for the red, green, blue, and alpha destination values.
				InverseDestinationColor = 7,
				// Each component of the color is multiplied by the alpha value of the destination. This can be represented as (Ad, Ad, Ad, Ad), where Ad is the destination alpha value.
				DestinationAlpha = 8,
				// Each component of the color is multiplied by the inverse of the alpha value of the destination. This can be represented as (1 ? Ad, 1 ? Ad, 1 ? Ad, 1 ? Ad), where Ad is the alpha destination value.
				InverseDestinationAlpha = 9,
				// Each component of the color is multiplied by a constant set in BlendFactor.
				BlendFactor = 10,
				// Each component of the color is multiplied by the inverse of a constant set in BlendFactor.
				InverseBlendFactor = 11,
				// Each component of the color is multiplied by either the alpha of the source color, or the inverse of the alpha of the source color, whichever is greater. This can be represented as (f, f, f, 1), where f = min(A, 1 ? Ad).
				SourceAlphaSaturation = 12
			};
		};

		// Defines how to combine a source color with the destination color already on the render target for color blending.
		struct BlendFunction
		{
			enum type
			{
				// The result is the destination added to the source. Result = (Source Color * Source Blend) + (Destination Color * Destination Blend)
				Add,
				// The result is the destination subtracted from the source. Result = (Source Color * Source Blend) ? (Destination Color * Destination Blend)
         		Subtract,
				// The result is the source subtracted from the destination. Result = (Destination Color * Destination Blend) ? (Source Color * Source Blend)
         		ReverseSubtract,
				// The result is the minimum of the source and destination. Result = min( (Source Color * Source Blend), (Destination Color * Destination Blend) )
         		Min,
				// The result is the maximum of the source and destination. Result = max( (Source Color * Source Blend), (Destination Color * Destination Blend) )
         		Max
			};
		};

		// Specifies Special Usage of the buffer contents.
		struct BufferUsage
		{
			enum type
			{
				None = 0,
				Points = 0x40,
				WriteOnly = 8
			};
		};

		// Specifies the buffer to use when calling GraphicsDevice.Clear.
		struct ClearOptions
		{
			enum type
			{
				Depth = 2,
				Stencil = 4,
				Target = 1
			};
		};

		// Defines the color channels that can be chosen for a per-channel write to a render target color buffer.
		struct ColorWriteChannels
		{
			enum type
			{
				All = 15,
				Alpha = 8,
				Blue = 4,
				Green = 2,
				None = 0,
				Red = 1
			};
		};

		// Defines comparison functions that can be chosen for alpha, stencil, or depth-buffer tests.
		struct CompareFunction
		{
			enum type
     		{
        		Never = 1,
         		Less = 2,
         		Equal = 3,
         		LessEqual = 4,
         		Greater = 5,
         		NotEqual = 6,
         		GreaterEqual = 7,
         		Always = 8
     		};
		};

		// Defines the faces of a cube map in the TextureCube class type.
		struct CubeMapFace
		{
			enum type
			{
				NegativeX = 1,
				NegativeY = 3,
				NegativeZ = 5,
				PositiveX = 0,
				PositiveY = 2,
				PositiveZ = 4
			};
		};

		// Defines winding orders that may be used to identify back faces for culling.
		struct CullMode
		{
			enum type
			{
				None,
				CullClockwiseFace,
				CullCounterClockwiseFace
			};
		};

		// Defines the format of data in a depth buffer.
		struct DepthFormat
		{
			enum type
			{
				None,
				Depth16,
				Depth24,
				Depth24Stencil8,
			};
		};

		// Defines classes that can be used for effect parameters or shader constants.
		struct EffectParameterClass
		{
			enum type
			{
				Scalar,
				Vector,
				Matrix,
				Object,
				Struct,
			};
		};

		// Defines types that can be used for effect parameters or shader constants.
		struct EffectParameterType
		{
			enum type
			{
				// Parameter is a void pointer.
				Void,
				// Parameter is a Boolean. Any nonzero value passed in will be mapped to 1 (TRUE) before being written into the constant table; otherwise, the value will be set to 0 in the constant table.
				Bool,
				// Parameter is an integer. Any floating-point values passed in will be rounded off (to zero decimal places) before being written into the constant table.
				Int32,
				// Parameter is a floating-point number.
				Single,
				// Parameter is a string.
				String,
				// Parameter is a texture.
				Texture,
				// Parameter is a 1D texture.
				Texture1D,
				// Parameter is a 2D texture.
				Texture2D,
				// Parameter is a 3D texture.
				Texture3D,
				// Parameter is a cube texture.
				TextureCube
			};
		};

		// Describes options for filling the vertices and lines that define a primitive.
		struct FillMode
		{
			enum type
			{
				Point = 1,
				Solid = 3,
				WireFrame = 2
			};
		};

		// Describes the status of the device.
		struct GraphicsDeviceStatus
		{
			enum type
			{
				Lost = 1,
				Normal = 0,
				NotReset = 2
			};
		};

		// Defines supported image file formats that may be used for textures.
		struct ImageFileFormat
		{
			enum type
			{
				Bmp = 0,
				Dds = 4,
				Dib = 6,
				Hdr = 7,
				Jpg = 1,
				Pfm = 8,
				Png = 3,
				Ppm = 5,
				Tga = 2
			};
		};

		// Defines the size of an element of an index buffer.
		struct IndexElementSize
		{
			enum type
			{
				SixteenBits,
				ThirtyTwoBits
			};
		};

		// Defines flags that describe the relationship between the adapter refresh rate and the rate at which GraphicsDevice.Present operations are completed.
		struct PresentInterval
		{
			enum type
			{
				Default = 0,
				Immediate = 0x80000000,
				One = 1,
				Two = 2
			};
		};

		// Defines how data in a vertex stream is interpreted during a draw call.
		struct PrimitiveType
		{
			enum type
			{
				LineList = 2,
				LineStrip = 4,
				PointList = 1,
				TriangleList = 5,
				TriangleStrip = 6
			};
		};

		// Determines how render target data is used once a new render target is set.
		struct RenderTargetUsage
		{
			enum type
			{
				DiscardContents,
				PlatformContents,
				PreserveContents
			};
		};

		// Describes whether existing buffer data will be overwritten or discarded during a SetData operation.
		struct SetDataOptions
		{
			enum type
			{
				Discard = 8192,
				None = 0,
				NoOverwrite = 4096
			};
		};

		// Defines the data type of a shader register.
		struct ShaderRegisterSet
		{
			enum type
			{
				Boolean = 0,	//Boolean value.
				Float = 2,		//4D floating-point number.
				Int4 = 1,		//4D integer number.
				Sampler = 3		//The register contains 4D sampler data.
			};
		};

		// Defines sprite rotation options.
		struct SpriteEffects
		{
			enum type
			{
				FlipHorizontally = 1,	//Rotate 180 degrees about the Y axis before rendering.
				FlipVertically = 0x100,	//Rotate 180 degrees about the X axis before rendering.
				None = 0				//No rotations specified.
			};
		};

		// Defines sprite sort-rendering options.
		struct SpriteSortMode
		{
			enum type
			{
				BackToFront = 3,
				Deferred = 1,
				FrontToBack = 4,
				Immediate = 0,
				Texture = 2
			};
		};

		// Defines stencil buffer operations.
		struct StencilOperation
		{
			enum type
			{
				Decrement = 8,
				DecrementSaturation = 5,
				Increment = 7,
				IncrementSaturation = 4,
				Invert = 6,
				Keep = 1,
				Replace = 3,
				Zero = 2
			};
		};

		// Defines various types of surface formats.
		struct SurfaceFormat
		{
			enum type
			{
				Alpha8 = 15,
				Bgr565 = 9,
				Bgra4444 = 12,
				Bgra5551 = 10,
				Color = 1,
				Dxt1 = 28,
				Dxt2 = 29,
				Dxt3 = 30,
				Dxt4 = 31,
				Dxt5 = 32,
				HalfSingle = 25,
				HalfVector2 = 26,
				HalfVector4 = 27,
				HdrBlendable = 19,
				NormalizedByte2 = 18,
				NormalizedByte4 = 19,
				Rg32 = 7,
				Rgba1010102 = 6,
				Rgba64 = 8,
				Single = 22,
				Vector2 = 23,
				Vector4 = 24,
			};
		};

		// Defines constants that describe supported texture-addressing modes.
		struct TextureAddressMode
		{
			enum type
			{
				Clamp = 3,
				Mirror = 2,
				Wrap = 1
			};
		};

		// Defines how a texture will be filtered as it is minified for each mipmap level.
		struct TextureFilter
		{
			enum type
			{
				// Use linear filtering.
				Linear,
				// Use point filtering.
				Point,
				// Use anisotropic filtering.
				Anisotropic,
				// Use linear filtering to shrink or expand, and point filtering between mipmap levels (mip).
				LinearMipPoint,
				// Use point filtering to shrink (minify) or expand (magnify), and linear filtering between mipmap levels.
				PointMipLinear,
				// Use linear filtering to shrink, point filtering to expand, and linear filtering between mipmap levels.
				MinLinearMagPointMipLinear,
				// Use linear filtering to shrink, point filtering to expand, and point filtering between mipmap levels.
				MinLinearMagPointMipPoint,
				// Use point filtering to shrink, linear filtering to expand, and linear filtering between mipmap levels.
				MinPointMagLinearMipLinear,
				// Use point filtering to shrink, linear filtering to expand, and point filtering between mipmap levels.
				MinPointMagLinearMipPoint
			};
		};
		
		// Defines vertex element formats.
		struct VertexElementFormat
		{
			enum type
			{
				Byte4,
				Color,
				HalfVector2,
				HalfVector4,
				NormalizedShort2,
				NormalizedShort4,
				Short2,
				Short4,
				Single,
				Vector2,
				Vector3,
				Vector4
			};
		};
		
		// Defines usage for vertex elements.
		struct VertexElementUsage
		{
			enum type
			{
				Binormal,
				BlendIndices,
				BlendWeight,
				Color,
				Depth,
				Fog,
				Normal,
				PointSize,
				Position,
				Sample,
				Tangent,
				TessellateFactor,
				TextureCoordinate
			};
		};
		
		// Lots of typedefs, but there was no other way to make these typesafe enum hacks look good.

		typedef Blend::type					Blend_t;
		typedef BlendFunction::type			BlendFunction_t;
		typedef BufferUsage::type			BufferUsage_t;
		typedef ClearOptions::type			ClearOptions_t;
		typedef ColorWriteChannels::type	ColorWriteChannels_t;
		typedef CompareFunction::type		CompareFunction_t;
		typedef CubeMapFace::type			CubeMapFace_t;
		typedef CullMode::type				CullMode_t;
		typedef DepthFormat::type			DepthFormat_t;
		typedef EffectParameterClass::type	EffectParameterClass_t;
		typedef EffectParameterType::type	EffectParameterType_t;
		typedef FillMode::type				FillMode_t;
		typedef GraphicsDeviceStatus::type	GraphicsDeviceStatus_t;
		typedef ImageFileFormat::type		ImageFileFormat_t;
		typedef IndexElementSize::type		IndexElementSize_t;
		typedef PresentInterval::type		PresentInterval_t;
		typedef PrimitiveType::type			PrimitiveType_t;
		typedef RenderTargetUsage::type		RenderTargetUsage_t;
		typedef SetDataOptions::type		SetDataOptions_t;
		typedef ShaderRegisterSet::type		ShaderRegisterSet_t;
		typedef SpriteEffects::type			SpriteEffects_t;
		typedef SpriteSortMode::type		SpriteSortMode_t;
		typedef StencilOperation::type		StencilOperation_t;
		typedef SurfaceFormat::type			SurfaceFormat_t;
		typedef TextureAddressMode::type	TextureAddressMode_t;
		typedef TextureFilter::type			TextureFilter_t;
		typedef VertexElementFormat::type	VertexElementFormat_t;		// Defines vertex element formats.
		typedef VertexElementUsage::type	VertexElementUsage_t;		// Defines usage for vertex elements.
	}
}

#endif //_XFX_GRAPHICS_ENUMS_
