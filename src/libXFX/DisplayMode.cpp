// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <Rectangle.h>
#include <Graphics/DisplayMode.h>

namespace XFX
{
	namespace Graphics
	{
		float DisplayMode::AspectRatio() const
		{
			return Width / Height;
		}
		
		Rectangle DisplayMode::TitleSafeArea() const
		{			
			/*
				Based on my own findings on a PAL SD TV set, this roughly equates to a resolution of 600 * 450
				however, that's on a normal 4:3 TV, and not a Widescreen 0_o'
				Either I get a widescreen or let someone else verify correctness.
				The reason I don't want to use the 10% rule Microsoft uses, is because I think a 10% margin is
				a little too much, but maybe I'm stupid, and should just use proven methods.
			*/
			return Rectangle(20, 0, Width - 20, Height - 30);
		}
		
		DisplayMode::DisplayMode()
		{
			Width = 0;
			Height = 0;
			Format = SurfaceFormat::Unknown;
			RefreshRate = 50;
		}
		
		bool DisplayMode::Equals(const DisplayMode other) const
		{
			return ((Width == other.Width) && (Height == other.Height) && (Format == other.Format));
		}
		
		int DisplayMode::GetHashCode() const
		{
			return (int)AspectRatio() ^ Width ^ Height ^ TitleSafeArea().GetHashCode() ^ Format ^ RefreshRate;
		}
		
		bool DisplayMode::operator!=(const DisplayMode other) const
		{
			return !Equals(other);
		}
		
		bool DisplayMode::operator==(const DisplayMode other) const
		{
			return Equals(other);
		}
	}
}
