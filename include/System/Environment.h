
#ifndef _SYSTEM_ENVIRONMENT_
#define _SYSTEM_ENVIRONMENT_

namespace System
{
	class OperatingSystem;
	class String;
	class Version;

	class Environment
	{
		// Specifies enumerated constants used to retrieve directory paths to system special folders.
		struct SpecialFolder
		{
			enum type
			{
				ApplicationData = 26,
				Favorites = 22,
				Personal = 5,
				Programs = 2,
				StartMenu = 11,
				Startup = 7
			};
		};

		typedef SpecialFolder::type SpecialFolder_t;

	public:
		static char* GetFolderPath(SpecialFolder_t folder);
		static char* NewLine();
		static OperatingSystem OSVersion();
		static int ProcessorCount();
		static int TickCount();
		static Version getVersion();
	};
}

#endif //_SYSTEM_ENVIRONMENT_
