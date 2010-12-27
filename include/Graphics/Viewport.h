/********************************************************
 *	Viewport.h											*
 *														*
 *	XFX Viewport definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_VIEWPORT_
#define _XFX_GRAPHICS_VIEWPORT_
 
namespace XFX
{
	struct Matrix;
	struct Vector3;
	
	namespace Graphics
	{
		/// <summary>
		/// Defines the window dimensions of a render-target surface onto which a 3D volume projects.
		/// </summary>
		struct Viewport
		{
		private:
			static bool WithinEpsilon(float a, float b);

		public:
			float AspectRatio();
			int Height;
			int MaxDepth;
			int MinDepth;
			int Width;
			int X;
			int Y;
			
			Vector3 Project(Vector3 source, Matrix projection, Matrix view, Matrix world);
			Vector3 Unproject(Vector3 source, Matrix projection, Matrix view, Matrix world);
		};
	}
}

#endif //_XFX_GRAPHICS_VIEWPORT_
