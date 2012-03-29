/********************************************************
 *	Enums.h												*
 *														*
 *	XFX::Graphics enumeration definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
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
				Zero = 1,
				One = 2,
				SourceColor = 3,
				InversourceColor = 4,
				SourceAlpha = 5,
				InverseSourceAlpha = 6,
				Destinationalpha = 7,
				InverseDestinationAlpha = 8,
				DestinationColor = 9,
				InverseDestinationColor = 10,
				SourceAlphaSaturation = 11,
				BothSourceAlpha = 12,
				BothInverseSourceAlpha = 13,
				BlendFactor = 14,
				InverseBlendFactor = 15
			};
		};

		// Defines how to combine a source color with the destination color already on the render target for color blending.
		struct BlendFunction
		{
			enum type
			{
				Add = 1,
         		Subtract = 2,
         		ReverseSubtract = 3,
         		Min = 4,
         		Max = 5
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

		// Identifies an include file as a local or system resource.
		struct CompilerIncludeHandlerType
		{
			enum type
			{
				Local,
				System
			};
		};

		// Defines optimization options that may be chosen for shader and effect code compilation.
		struct CompilerOptions
		{
			enum type
			{
				AvoidFlowControl,
				Debug,
				ForcePixelShaderSoftwareNoOptimizations,
				ForceVertexShaderSoftwareNoOptimizations,
				None,
				NoPreShader,
				NotCloneable,
				PackMatrixColumnMajor,
				PackMatrixRowMajor,
				PartialPrecision,
				PreferFlowControl,
				SkipOptimization,
				SkipValidation
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
				None = 1,
				CullClockwiseFace = 2,
				CullCounterClockwiseFace = 3
			};
		};

		// Defines the format of data in a depth buffer.
		struct DepthFormat
		{
			enum type
			{
				Depth15Stencil1 = 56,
				Depth16 = 54,
				Depth24 = 51,
				Depth24Stencil8 = 48,
				Depth24Stencil8Single = 49,
				Depth24Stencil4 = 50,
				Depth32 = 52,			
				Unknown = -1
			};
		};

		// Specifies the type of device driver.
		struct DeviceType
		{
			enum type
			{
				Hardware = 1,
				NullReference = 4,
				Reference = 2
			};
		};

		// Defines classes that can be used for effect parameters or shader constants.
		struct EffectParameterClass
		{
			enum type
			{
				MatrixColumns,
				MatrixRows,
				Object,
				Scalar,
				Struct,
				Vector
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

		// Defines modes describing how to filter an image or mipmap when it is minified or magnified to fit a set of vertices.
		struct FilterOptions
		{
			enum type
			{
				Box = 5,
				Dither = 524288,
				DitherDiffusion = 1048576,
				Linear = 3,
				Mirror = 458752,
				MirrorU = 65536,
				MirrorV = 131072,
				MirrorW = 262144,
				None = 1,
				Point = 2,
				Srgb = 6291456,
				SrgbIn = 2097152,
				SrgbOut = 4194304,
				Triangle = 4
			};
		};

		// Defines constants that describe the fog mode.
		struct FogMode
		{
			enum type
			{
				Exponent = 1,
				ExponentSquared = 2,
				Linear = 3,
				None = 0
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

		// Defines the levels of full-scene multisampling that the game machine can apply.
		struct MultiSampleType
		{
			enum type
			{
				SixteenSamples = 16,
				FifteenSamples = 15,
				FourteenSamples = 14,
				ThirteenSamples = 13,
				TwelveSamples = 12,
				ElevenSamples = 11,
				TenSamples = 10,
				NineSamples = 9,
				EightSamples = 8,
				SevenSamples = 7,
				SixSamples = 6,
				FiveSamples = 5,
				FourSamples = 4,
				ThreeSamples = 3,
				TwoSamples = 2,
				NonMaskable = 1,
				None = 0
			};
		};

		// Defines flags that describe the relationship between the adapter refresh rate and the rate at which GraphicsDevice.Present operations are completed.
		struct PresentInterval
		{
			enum type
			{
				Default = 0,
				Four = 8,
				Immediate = 0x80000000,
				One = 1,
				Three = 4,
				Two = 2
			};
		};

		// Defines flags that control the behavior of the back buffer and depth buffer.
		struct PresentOptions
		{
			enum type
			{
				DeviceClip = 4,
				DiscardDepthStencil = 2,
				None = 0,
				Video = 16
			};
		};

		// Defines how data in a vertex stream is interpreted during a draw call.
		struct PrimitiveType
		{
			enum type
			{
				LineList = 2,
				LineStrip = 3,
				PointList = 1,
				TriangleFan = 6,
				TriangleList = 4,
				TriangleStrip = 5
			};
		};

		// Defines options for querying device resource formats.
		struct QueryUsages
		{
			enum type
			{
				Filter = 131072,
				None = 0,
				PostPixelShaderRendering = 524288,
				SrgbRead = 65536,
				SrgbWrite = 262144,
				VertexTexture = 1048576,
				WrapAndMip = 2097152
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

		// Defines resource types.
		struct ResourceType
		{
			enum type
			{
				DepthStencilBuffer = 1,
				IndexBuffer = 7,
				RenderTarget = 8,
				Texture2D = 3,
				Texture3D = 4,
				Texture3DVolume = 2,
				TextureCube = 5,
				VertexBuffer = 6
			};
		};

		// Defines options for saving the graphics device state before and after an effect technique is applied.
		struct SaveStateMode
		{
			enum type
			{
				None,
				SaveState
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

		// Defines vertex and pixel shader versions.
		struct ShaderProfile
		{
			enum type
			{
				PS_1_1,
				PS_1_2,
				PS_1_3,
				VS_1_1,
				XPS_1_1, //Denotes XBOX specific shader configuration
				XVS_1_1  //Denotes XBOX specific shader configuration
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

		// The following flags are used to specify sprite blending rendering options to the flags parameter in SpriteBatch.Begin:
		struct SpriteBlendMode
		{
			enum type
			{
				Additive = 2,	//Enable Additive blending.
				AlphaBlend = 1,	//Enable Alpha blending.
				None = 0		//No blending specified.
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
				Bgr233 = 16,
				Bgr24 = 17,
				Bgr32 = 2,
				Bgr444 = 13,
				Bgr555 = 11,
				Bgr565 = 9,
				Bgra1010102 = 3,
				Bgra2338 = 14,
				Bgra4444 = 12,
				Bgra5551 = 10,
				Color = 1,
				Depth15Stencil1 = 56,
				Depth16 = 54,
				Depth24 = 51,
				Depth24Stencil4 = 50,
				Depth24Stencil8 = 48,
				Depth24Stencil8Single = 49,
				Depth32 = 52,
				Dxt1 = 28,
				Dxt2 = 29,
				Dxt3 = 30,
				Dxt4 = 31,
				Dxt5 = 32,
				HalfSingle = 25,
				HalfVector2 = 26,
				HalfVector4 = 27,
				Luminance16 = 34,
				Luminance8 = 33,
				LuminanceAlpha16 = 36,
				LuminanceAlpha8 = 35,
				Multi2Bgra32 = 47,
				NormalizedAlpha1010102 = 41,
				NormalizedByte2 = 18,
				NormalizedByte2Computed = 42,
				NormalizedByte4 = 19,
				NormalizedLuminance16 = 39,
				NormalizedLuminance32 = 40,
				NormalizedShort2 = 20,
				Normalizedshort4 = 21,
				Palette8 = 37,
				PaletteAlpha16 = 38,
				Rg32 = 7,
				Rgb32 = 5,
				Rgba1010102 = 6,
				Rgba32 = 4,
				Rgba64 = 8,
				Single = 22,
				Unknown = -1,
				Vector2 = 23,
				Vector4 = 24,
				VideoGrGb = 45,
				VideoRgBg = 46,
				VideoUyVy = 44,
				VideoYuYv = 43
			};
		};

		// Defines how the device front buffer and back buffer are to be swapped when GraphicsDevice.Present is called.
		struct SwapEffect
		{
			enum type
			{
				Copy = 3,
				Default = 1,
				Discard = 1,
				Flip = 2
			};
		};

		// Defines constants that describe supported texture-addressing modes.
		struct TextureAddressMode
		{
			enum type
			{
				Border = 4,
				Clamp = 3,
				Mirror = 2,
				MirrorOnce = 5,
				Wrap = 1
			};
		};

		// Defines how a texture will be filtered as it is minified for each mipmap level.
		struct TextureFilter
		{
			enum type
			{
				Anisotropic = 3,
				GaussianQuad = 7,
				Linear = 2,
				None = 0,
				Point = 1,
				PyramidalQuad = 6
			};
		};

		// Specifies special usage of the texture data.
		struct TextureUsage
		{
			enum type
			{
				AutoGenerateMipMap,
				Linear,
				None,
				Tiled
			};
		};
		
		// Defines supported wrap coordinates.
		struct TextureWrapCoordinates
		{
			enum type
			{
				None = 0,
				One = 2,
				Three = 8,
				Two = 4,
				Zero = 1
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
				Normalized101010,
				NormalizedShort2,
				NormalizedShort4,
				Rg32,
				Rgba32,
				Rgba64,
				Short2,
				Short4,
				Single,
				UInt101010,
				Unused,
				Vector2,
				Vector3,
				Vector4
			};
		};
		
		// Defines the tessellator processing method for a vertex element.
		struct VertexElementMethod
		{
			enum type
			{
				Default,
				LookUp,
				LookUpPresampled,
				UV
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
		typedef Blend::type Blend_t;
		typedef BlendFunction::type BlendFunction_t;
		typedef BufferUsage::type BufferUsage_t;
		typedef ClearOptions::type ClearOptions_t;
		typedef ColorWriteChannels::type ColorWriteChannels_t;
		typedef CompareFunction::type CompareFunction_t;
		typedef CompilerIncludeHandlerType::type CompilerIncludeHandlerType_t;
		typedef CompilerOptions::type CompilerOptions_t;
		typedef CubeMapFace::type CubeMapFace_t;
		typedef CullMode::type CullMode_t;
		typedef DepthFormat::type DepthFormat_t;
		typedef DeviceType::type DeviceType_t;
		typedef EffectParameterClass::type EffectParameterClass_t;
		typedef FillMode::type FillMode_t;
		typedef FilterOptions::type FilterOptions_t;
		typedef FogMode::type FogMode_t;
		typedef GraphicsDeviceStatus::type GraphicsDeviceStatus_t;
		typedef ImageFileFormat::type ImageFileFormat_t;
		typedef IndexElementSize::type IndexElementSize_t;
		typedef MultiSampleType::type MultiSampleType_t;
		typedef PresentInterval::type PresentInterval_t;
		typedef PresentOptions::type PresentOptions_t;
		typedef PrimitiveType::type PrimitiveType_t;
		typedef QueryUsages::type QueryUsages_t;
		typedef RenderTargetUsage::type RenderTargetUsage_t;
		typedef ResourceType::type ResourceType_t;
		typedef SaveStateMode::type SaveStateMode_t;
		typedef SetDataOptions::type SetDataOptions_t;
		typedef ShaderProfile::type ShaderProfile_t;
		typedef ShaderRegisterSet::type ShaderRegisterSet_t;
		typedef SpriteBlendMode::type SpriteBlendMode_t;
		typedef SpriteEffects::type SpriteEffects_t;
		typedef SpriteSortMode::type SpriteSortMode_t;
		typedef StencilOperation::type StencilOperation_t;
		typedef SurfaceFormat::type SurfaceFormat_t;
		typedef SwapEffect::type SwapEffect_t;
		typedef TextureAddressMode::type TextureAddressMode_t;
		typedef TextureFilter::type TextureFilter_t;
		typedef TextureUsage::type TextureUsage_t;						// Specifies special usage of the texture data.
		typedef TextureWrapCoordinates::type TextureWrapCoordinates_t;	// Defines supported wrap coordinates.
		typedef VertexElementFormat::type VertexElementFormat_t;		// Defines vertex element formats.
		typedef VertexElementMethod::type VertexElementMethod_t;		// Defines the tessellator processing method for a vertex element.
		typedef VertexElementUsage::type VertexElementUsage_t;			// Defines usage for vertex elements.
	}
}

#endif //_XFX_GRAPHICS_ENUMS_
