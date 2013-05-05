

#ifndef _SYSTEM_ENVIRONMENT_
#define _SYSTEM_ENVIRONMENT_

namespace System
{
	class OperatingSystem;
	class String;
	class Version;

	class Environment
	{
	private:
		Environment();

	public:
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

		static const char* NewLine;

		static const char* GetFolderPath(const SpecialFolder_t folder);
		static OperatingSystem OSVersion();
		static int ProcessorCount();
		static int TickCount();
		static Version getVersion();
	};
}

#endif //_SYSTEM_ENVIRONMENT_
