/*****************************************************************************
 *	EffectAnnotation.h  													 *
 *																			 *
 *	XFX::Graphics::EffectAnnotation definition file 						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_EFFECTANNOTATION_
#define _XFX_GRAPHICS_EFFECTANNOTATION_

#include <System/String.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	struct Matrix;
	struct Vector2;
	struct Vector3;
	struct Vector4;

	namespace Graphics
	{
		/**
		 * Represents an annotation to an EffectParameter.
		 */
		class EffectAnnotation
		{
		public:
			/**
			 * Gets the number of columns in this effect annotation.
			 */
			int getColumnCount() const;
			/**
			 * Gets the name of the effect annotation.
			 */
			String& getName() const;
			/**
			 * Gets the parameter class of this effect annotation.
			 */
			EffectParameterClass_t getParameterClass() const;
			/**
			 * Gets the parameter type of this effect annotation.
			 */
			EffectParameterType_t getParameterType() const;
			/**
			 * Gets the row count of this effect annotation.
			 */
			int getRowCount() const;
			/**
			 * Gets the semantic of this effect annotation.
			 */
			String& getSemantic() const;

			/**
			 * Gets the value of the EffectAnnotation as a Boolean.
			 */
			bool GetValueBoolean() const;
			/**
			 * Gets the value of the EffectAnnotation as a Int32.
			 */
			int GetValueInt32() const;
			/**
			 * Gets the value of the EffectAnnotation as a Matrix.
			 */
			Matrix GetValueMatrix() const;
			/**
			 * Gets the value of the EffectAnnotation as a Single.
			 */
			float GetValueSingle() const;
			/**
			 * Gets the value of the EffectAnnotation as a String.
			 */
			String& GetValueString() const;
			/**
			 * Gets the value of the EffectAnnotation as a Vector2.
			 */
			Vector2 GetValueVector2() const;
			/**
			 * Gets the value of the EffectAnnotation as a Vector3.
			 */
			Vector3 GetValueVector3() const;
			/**
			 * Gets the value of the EffectAnnotation as a Vector4.
			 */
			Vector4 GetValueVector4() const;
		};
	}
}

#endif //_XFX_GRAPHICS_EFFECTANNOTATION_
