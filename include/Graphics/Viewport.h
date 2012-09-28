/********************************************************
 *	Viewport.h											*
 *														*
 *	XFX Viewport definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_VIEWPORT_
#define _XFX_GRAPHICS_VIEWPORT_

#include <System/Object.h>

using namespace System;

namespace XFX
{
	struct Matrix;
	struct Rectangle;
	struct Vector3;
	
	namespace Graphics
	{
		// Defines the window dimensions of a render-target surface onto which a 3D volume projects.
		struct Viewport : Object
		{
		private:
			static bool WithinEpsilon(float a, float b);

		public:
			float getAspectRatio() const;
			Rectangle getBounds() const;
			void setBounds(const Rectangle value);
			int Height;
			float MaxDepth;
			float MinDepth;
			Rectangle getTitleSafeArea() const;
			int Width;
			int X;
			int Y;

			Viewport();
			Viewport(const int x, const int y, const int width, const int height);
			Viewport(const Rectangle bounds);
			
			bool Equals(const Object* obj) const;
			bool Equals(const Viewport obj) const;
			int GetHashCode() const;
			int GetType() const;
			Vector3 Project(const Vector3 source, const Matrix projection, const Matrix view, const Matrix world) const;
			const char* ToString() const;
			Vector3 Unproject(const Vector3 source, const Matrix projection, const Matrix view, const Matrix world) const;

			bool operator !=(const Viewport& right) const;
			bool operator ==(const Viewport& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_VIEWPORT_
