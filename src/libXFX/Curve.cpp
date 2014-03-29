// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       software without specific prior written permission.
// 
// SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <Curve.h>
#include <System/Math.h>
#include <System/Single.h>

namespace XFX
{
	const Type CurveTypeInfo("Curve", "XFX::Curve", TypeCode::Object);

	bool Curve::IsConstant() const
	{
		return keys.Count() <= 1;
	}

	CurveKeyCollection Curve::getKeys() const
	{
		return keys;
	}

	Curve::Curve()
	{
	}

	Curve Curve::Clone() const
	{
		Curve curve = Curve();

		curve.keys = keys.Clone();
		curve.PreLoop = PreLoop;
		curve.PostLoop = PostLoop;

		return curve;
	}

	void Curve::ComputeTangent(int keyIndex, CurveTangent_t tangentInType, CurveTangent_t tangentOutType)
	{
		// See http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.curvetangent.aspx

		CurveKey key = keys[keyIndex];

		float p0, p, p1;
		p0 = p = p1 = key.getPosition();

		float v0, v, v1;
		v0 = v = v1 = key.Value;

		if ( keyIndex > 0 )
		{
			p0 = keys[keyIndex - 1].getPosition();
			v0 = keys[keyIndex - 1].Value;
		}

		if (keyIndex < keys.Count() - 1)
		{
			p1 = keys[keyIndex + 1].getPosition();
			v1 = keys[keyIndex + 1].Value;
		}

		switch (tangentInType)
		{
		case CurveTangent::Flat:
			key.TangentIn = 0;
			break;
		case CurveTangent::Linear:
			key.TangentIn = v - v0;
			break;
		case CurveTangent::Smooth:
			float pn = p1 - p0;

			if (Math::Abs(pn) < Single::Epsilon)
			{
				key.TangentIn = 0;
			}
			else
			{
				key.TangentIn = (v1 - v0) * ((p - p0) / pn);
			}
			break;
		}

		switch (tangentOutType)
		{
		case CurveTangent::Flat:
			key.TangentOut = 0;
			break;
		case CurveTangent::Linear:
			key.TangentOut = v1 - v;
			break;
		case CurveTangent::Smooth:
			float pn = p1 - p0;

			if (Math::Abs(pn) < Single::Epsilon)
			{
				key.TangentOut = 0;
			}
			else
			{
				key.TangentOut = (v1 - v0) * ((p1 - p) / pn);
			}
			break;
		}
	}

	void Curve::ComputeTangents(CurveTangent_t tangentInType, CurveTangent_t tangentOutType)
	{
		for (int i = 0; i < keys.Count(); i++)
		{
			ComputeTangent(i, tangentInType, tangentOutType);
		}
	}

	float Curve::Evaluate(float position)
	{
		CurveKey first = keys[0];
		CurveKey last = keys[keys.Count() - 1];

		if (position < first.getPosition())
		{
			switch (PreLoop)
			{
			case CurveLoopType::Constant:
				//constant
				return first.Value;

			case CurveLoopType::Linear:
				// linear y = a*x +b with a tangent of last point
				return first.Value - first.TangentIn * (first.getPosition() - position);

			case CurveLoopType::Cycle:
				//start -> end / start -> end
				int cycle = GetNumberOfCycle(position);
				float virtualPos = position - (cycle * (last.getPosition() - first.getPosition()));
				return GetCurvePosition(virtualPos);

			case CurveLoopType::CycleOffset:
				//make the curve continue (with no step) so must up the curve each cycle of delta(value)
				cycle = GetNumberOfCycle(position);
				virtualPos = position - (cycle * (last.getPosition() - first.getPosition()));
				return (GetCurvePosition(virtualPos) + cycle * (last.Value - first.Value));

			case CurveLoopType::Oscillate:
				//go back on curve from end and target start 
				// start-> end / end -> start
				cycle = GetNumberOfCycle(position);

				if (0 == cycle % 2f)//if pair
				{
					virtualPos = position - (cycle * (last.getPosition() - first.getPosition()));
				}
				else
				{
					virtualPos = last.getPosition() - position + first.getPosition() + (cycle * (last.getPosition() - first.getPosition()));
				}

				return GetCurvePosition(virtualPos);
			}
		}
		else if (position > last.getPosition())
		{
			int cycle;

			switch (PostLoop)
			{
			case CurveLoopType::Constant:
				//constant
				return last.Value;

			case CurveLoopType::Linear:
				// linear y = a*x +b with a tangent of last point
				return last.Value + first.TangentOut * (position - last.getPosition());

			case CurveLoopType::Cycle:
				//start -> end / start -> end
				cycle = GetNumberOfCycle(position);
				float virtualPos = position - (cycle * (last.getPosition() - first.getPosition()));
				return GetCurvePosition(virtualPos);

			case CurveLoopType::CycleOffset:
				//make the curve continue (with no step) so must up the curve each cycle of delta(value)
				cycle = GetNumberOfCycle(position);
				virtualPos = position - (cycle * (last.getPosition() - first.getPosition()));
				return (GetCurvePosition(virtualPos) + cycle * (last.Value - first.Value));

			case CurveLoopType::Oscillate:
				//go back on curve from end and target start 
				// start-> end / end -> start
				cycle = GetNumberOfCycle(position);
				virtualPos = position - (cycle * (last.getPosition() - first.getPosition()));

				if (0 == cycle % 2) // if pair
				{
					virtualPos = position - (cycle * (last.getPosition() - first.getPosition()));
				}
				else
				{
					virtualPos = last.getPosition() - position + first.getPosition() + (cycle * (last.getPosition() - first.getPosition()));
				}

				return GetCurvePosition(virtualPos);
			}
		}

		//in curve
		return GetCurvePosition(position);
	}

	float Curve::GetCurvePosition(float position)
	{
		// only for position in curve
		CurveKey prev = keys[0];

		for (int i = 1; i < keys.Count(); i++)
		{
			CurveKey next = keys[i];

			if (next.getPosition() >= position)
			{
				if (prev.Continuity == CurveContinuity::Step)
				{
					if (position >= 1.0f)
					{
						return next.Value;
					}

					return prev.Value;
				}

				float t = (position - prev.getPosition()) / (next.getPosition() - prev.getPosition());//to have t in [0,1]
				float ts = t * t;
				float tss = ts * t;
				//After a lot of search on internet I have found all about spline function
				// and bezier (phi'sss ancien) but finally use hermite curve 
				//http://en.wikipedia.org/wiki/Cubic_Hermite_spline
				//P(t) = (2*t^3 - 3t^2 + 1)*P0 + (t^3 - 2t^2 + t)m0 + (-2t^3 + 3t^2)P1 + (t^3-t^2)m1
				//with P0.value = prev.value , m0 = prev.tangentOut, P1= next.value, m1 = next.TangentIn
				return (2 * tss - 3 * ts + 1.0f) * prev.Value + (tss - 2 * ts + t) * prev.TangentOut + (3 * ts - 2 * tss) * next.Value + (tss - ts) * next.TangentIn;
			}

			prev = next;
		}

		return 0.0f;
	}

	int Curve::GetNumberOfCycle(float position)
	{
		float cycle = (position - keys[0].getPosition()) / (keys[keys.Count() - 1].getPosition() - keys[0].getPosition());

		if (cycle < 0.0f)
		{
			cycle--;
		}

		return (int)cycle;
	}

	const Type& Curve::GetType()
	{
		return CurveTypeInfo;
	}
}
