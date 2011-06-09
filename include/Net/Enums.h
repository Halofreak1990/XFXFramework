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
		
		struct NetworkSessionJoinError
		{
			enum type
			{
				SessionNotFound,
				SessionNotJoinable,
				SessionFull
			};
		};
		
		struct NetworkSessionState
		{
			enum type
			{
				Lobby,
				Playing,
				Ended
			};
		};

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
