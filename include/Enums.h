/********************************************************
 *	Enums.h												*
 *														*
 *	XFX enumeration definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_ENUMS_
#define _XFX_ENUMS_

namespace XFX
{
	/// <summary>
	/// Describes how one bounding volume contains another. 
	/// </summary>
	struct ContainmentType
	{
		enum type
		{
			Contains,
			Disjoint,
			Intersects
		};
	};
	/// <summary>
	/// Defines the continuity of CurveKeys on a Curve.
	/// </summary>
	struct CurveContinuity
	{
		enum type
		{
			Smooth,
			Step
		};
	};
	/// <summary>
	/// Defines how the value of a Curve will be determined for positions before
	/// the first point on the Curve or after the last point on the Curve.
	/// </summary>
	struct CurveLoopType
	{
		enum type
		{
			Constant,
			Cycle,
			CycleOffset,
			Linear,
			Oscillate
		};
	};
	/// <summary>
	/// Specifies different tangent types to be calculated for CurveKey points in a Curve.
	/// </summary>
	struct CurveTangent
	{
		enum type
		{
			Flat,
			Linear,
			Smooth
		};
	};
	/// <summary>
	/// Describes the intersection between a plane and a bounding volume.
	/// </summary>
	struct PlaneIntersectionType
	{
		enum type
		{
			Back,
			Front,
			Intersecting
		};
	};
	/// <summary>
	/// Specifies the index of a player.
	/// </summary>
	struct PlayerIndex
	{
		enum type
		{
			One,
			Two,
			Three,
			Four
		};
	};
	/// <summary>
	/// Defines the target platform to be used when compiling content.
	/// </summary>
	struct TargetPlatform
	{
		enum type
		{
			Unknown,
			Linux,
			XBOX
		};
	};
	
	//Lots of typedefs, but there was no other way to make these enum hacks look good.
	typedef ContainmentType::type		ContainmentType_t;
	typedef CurveContinuity::type		CurveContinuity_t;
	typedef CurveLoopType::type			CurveLoopType_t;
	typedef CurveTangent::type			CurveTangent_t;
	typedef PlaneIntersectionType::type	PlaneIntersectionType_t;
	typedef PlayerIndex::type			PlayerIndex_t;
	typedef TargetPlatform::type		TargetPlatform_t;
}

#endif //_ENUMS_
