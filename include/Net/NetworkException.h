/********************************************************
 *	NetworkException.h									*
 *														*
 *	XFX NetworkException definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_NET_NETWORKEXCEPTION_
#define _XFX_NET_NETWORKEXCEPTION_

#include <System/Exception.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Net
	{
		/// <summary>
		/// Thrown if there is a network communication failure.
		/// </summary>
		class NetworkException : public Exception
		{
		public:
			NetworkException();
			NetworkException(char* message);
			NetworkException(char* message, Exception innerException);
		};

		/// <summary>
		/// Thrown if an error was encountered while joining a session.
		/// </summary>
		class NetworkSessionJoinException : public NetworkException
		{
		public:
			NetworkSessionJoinException();
			NetworkSessionJoinException(char* message);
			NetworkSessionJoinException(char* message, NetworkSessionJoinError joinError);
			NetworkSessionJoinException(char* message, Exception innerException);

			NetworkSessionJoinError JoinError(); //! get
			void JoinError(NetworkSessionJoinError joinError); //! set
		};
	}
}

#endif //_XFX_NET_NETWORKEXCEPTION_
