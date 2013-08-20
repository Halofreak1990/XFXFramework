// Copyright (C) XFX Team
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

#include <Media/VideoPlayer.h>
#include <Media/Video.h>

namespace XFX
{
	namespace Media
	{
		bool VideoPlayer::IsDisposed()
		{
			return isDisposed;
		}

		TimeSpan VideoPlayer::getPlayPosition()
		{
			// TODO: implement remainder
		}

		MediaState_t VideoPlayer::getState()
		{
			// TODO: implement remainder
		}

		Video* VideoPlayer::getVideo()
		{
			return playingVideo;
		}

		VideoPlayer::VideoPlayer()
		{
			// TODO: implement remainder
		}

		void VideoPlayer::Dispose()
		{
			Dispose(true);
		}

		void VideoPlayer::Dispose(bool disposing)
		{
			// TODO: implement remainder
		}

		Texture2D* VideoPlayer::GetTexture()
		{
			// TODO: return current video frame
		}

		void VideoPlayer::Pause()
		{
			// TODO: implement remainder
		}

		void VideoPlayer::Play(Video * const video)
		{
			sassert(video != null, String::Format("value; %s", FrameworkResources::ArgumentNull_Generic));

			// TODO: implement remainder
		}

		void VideoPlayer::Resume()
		{
			// TODO: implement remainder
		}

		void VideoPlayer::Stop()
		{
			// TODO: implement remainder
		}
	}
}
