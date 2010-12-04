/********************************************************
 *	Enums.h												*
 *														*
 *	XFX::Net enumerations definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_NET_ENUMS_
#define _XFX_NET_ENUMS_

namespace XFX
{
	namespace Net
	{
		/// <summary>
		/// Defines the reason a session ended.
		/// </summary>
		struct NetworkSessionEndReason
		{
			enum type
			{
				ClientSignedOut,
				HostEndedSession,
				RemovedByHost,
				Disconnected
			};
		};
		/// <summary>
		/// Contains additional data about a NetworkSessionJoinException.
		/// </summary>
		struct NetworkSessionJoinError
		{
			enum type
			{
				SessionNotFound,
				SessionNotJoinable,
				SessionFull
			};
		};
		/// <summary>
		/// Defines the different states of a multiplayer session.
		/// </summary>
		struct NetworkSessionState
		{
			enum type
			{
				Lobby,
				Playing,
				Ended
			};
		};
		/// <summary>
		/// Defines the different types of a multiplayer session.
		/// </summary>
		struct NetworkSessionType
		{
			enum type
			{
				Local,
				SystemLink,
				PlayerMatch,
				Ranked
			};
		};

		/// <summary>
		/// Defines options for network packet transmission.
		/// </summary>
		struct SendDataOptions
		{
			enum type
			{
				InOrder = 2,
				None = 0,
				Reliable = 1,
				ReliableInOrder = 3
			};
		};

		typedef NetworkSessionEndReason::type	NetworkSessionEndReason_t;
		typedef NetworkSessionJoinError::type	NetworkSessionJoinError_t;
		typedef NetworkSessionState::type		NetworkSessionState_t;
		typedef NetworkSessionType::type		NetworkSessionType_t;
		typedef SendDataOptions::type			SendDataOptions_t;
	}
}

#endif //_XFX_NET_ENUMS_
