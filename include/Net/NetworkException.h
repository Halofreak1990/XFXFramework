#ifndef _XFX_NET_NETWORKEXCEPTION_
#define _XFX_NET_NETWORKEXCEPTION_

#include <System/Exception.h>
#include "Enums.h"

namespace XFX
{
	namespace Net
	{
		/// <summary>
		/// Thrown if there is a network communication failure.
		/// </summary>
		class NetworkException : Exception
		{
		public:
			public NetworkException();
			public NetworkException(char* message);
			public NetworkException(char* message, Exception innerException);
		};

		/// <summary>
		/// Thrown if an error was encountered while joining a session.
		/// </summary>
		class NetworkSessionJoinException : NetworkException
		{
		public:
			public NetworkSessionJoinException();
			public NetworkSessionJoinException(char* message);
			public NetworkSessionJoinException(char* message, NetworkSessionJoinError joinError);
			public NetworkSessionJoinException(char* message, Exception innerException);

			public NetworkSessionJoinError JoinError(); //! get
			public void JoinError(NetworkSessionJoinError joinError); //! set
		};
	}
}

#endif //_XFX_NET_NETWORKEXCEPTION_
