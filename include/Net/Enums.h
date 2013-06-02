/********************************************************
 *	Enums.h												*
 *														*
 *	XFX::Net enumerations definition file				*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_NET_ENUMS_
#define _XFX_NET_ENUMS_

namespace XFX
{
	namespace Net
	{
		// Defines the reason a session ended.
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
		
		// Contains additional data about a NetworkSessionJoinException.
		struct NetworkSessionJoinError
		{
			enum type
			{
				SessionNotFound,
				SessionNotJoinable,
				SessionFull
			};
		};
		
		// Defines the different states of a multiplayer session.
		struct NetworkSessionState
		{
			enum type
			{
				Lobby,
				Playing,
				Ended
			};
		};

		// Defines the different types of a multiplayer session.
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

		// Defines options for network packet transmission.
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

		typedef NetworkSessionEndReason::type	NetworkSessionEndReason_t;	// Defines the reason a session ended.
		typedef NetworkSessionJoinError::type	NetworkSessionJoinError_t;	// Contains additional data about a NetworkSessionJoinException.
		typedef NetworkSessionState::type		NetworkSessionState_t;		// Defines the different states of a multiplayer session.
		typedef NetworkSessionType::type		NetworkSessionType_t;		// Defines the different types of a multiplayer session.
		typedef SendDataOptions::type			SendDataOptions_t;			// Defines options for network packet transmission.
	}
}

#endif //_XFX_NET_ENUMS_
