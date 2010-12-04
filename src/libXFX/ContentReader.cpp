#include <Content/ContentReader.h>
#include <Matrix.h>
#include <Quaternion.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>

namespace XFX
{
	namespace Content
	{
		const short ContentReader::XnbVersion = 2;

		ContentReader::ContentReader(ContentManager manager, Stream stream, GraphicsDevice graphicsDevice) 
			: BinaryReader(stream)
		{
			_graphicsDevice = graphicsDevice;
		}

		ContentReader::ContentReader(ContentManager manager, Stream input, char* assetName)
			: BinaryReader(PrepareStream(input, assetName))
		{
			contentManager = manager;
			_assetName = assetName;
		}

		Matrix ContentReader::ReadMatrix()
		{
			Matrix result;
			result.M11 = ReadSingle();
			result.M12 = ReadSingle();
			result.M13 = ReadSingle();
			result.M14 = ReadSingle();
			result.M21 = ReadSingle();
			result.M22 = ReadSingle();
			result.M23 = ReadSingle();
			result.M24 = ReadSingle();
			result.M31 = ReadSingle();
			result.M32 = ReadSingle();
			result.M33 = ReadSingle();
			result.M34 = ReadSingle();
			result.M41 = ReadSingle();
			result.M42 = ReadSingle();
			result.M43 = ReadSingle();
			result.M44 = ReadSingle();
			return result;
		}

		Quaternion ContentReader::ReadQuaternion()
		{
			Quaternion result;
			result.X = ReadSingle();
			result.Y = ReadSingle();
			result.Z = ReadSingle();
			result.W = ReadSingle();
			return result;
		}

		Vector2 ContentReader::ReadVector2()
		{
			Vector2 result;
			result.X = ReadSingle();
			result.Y = ReadSingle();
			return result;
		}

		Vector3 ContentReader::ReadVector3()
		{
			Vector3 result;
			result.X = ReadSingle();
			result.Y = ReadSingle();
			result.Z = ReadSingle();
			return result;
		}

		Vector4 ContentReader::ReadVector4()
		{
			Vector4 result;
			result.X = ReadSingle();
			result.Y = ReadSingle();
			result.Z = ReadSingle();
			result.W = ReadSingle();
			return result;
		}
	}
}
