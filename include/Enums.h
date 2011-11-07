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
	struct ContainmentType
	{
		enum type
		{
			Contains,
			Disjoint,
			Intersects
		};
	};

	struct CurveContinuity
	{
		enum type
		{
			Smooth,
			Step
		};
	};
	
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
	
	struct CurveTangent
	{
		enum type
		{
			Flat,
			Linear,
			Smooth
		};
	};
	
	struct PlaneIntersectionType
	{
		enum type
		{
			Back,
			Front,
			Intersecting
		};
	};
	
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

	struct TargetPlatform
	{
		enum type
		{
			Unknown,
			Linux,
			XBOX
		};
	};
	
	typedef ContainmentType::type		ContainmentType_t;			// Describes how one bounding volume contains another.
	typedef CurveContinuity::type		CurveContinuity_t;			// Defines the continuity of CurveKeys on a Curve.
	typedef CurveLoopType::type			CurveLoopType_t;			// Defines how the value of a Curve will be determined for positions before the first point on the Curve or after the last point on the Curve.
	typedef CurveTangent::type			CurveTangent_t;				// Specifies different tangent types to be calculated for CurveKey points in a Curve.
	typedef PlaneIntersectionType::type	PlaneIntersectionType_t;	// Describes the intersection between a plane and a bounding volume.
	typedef PlayerIndex::type			PlayerIndex_t;				// Specifies the index of a player.
	typedef TargetPlatform::type		TargetPlatform_t;			// Defines the target platform to be used when compiling content.
}

#endif //_ENUMS_
