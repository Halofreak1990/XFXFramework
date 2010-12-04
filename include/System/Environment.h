
#ifndef _ENVIRONMENT_
#define _ENVIRONMENT_

namespace System
{
	class OperatingSystem;
	class String;
	class Version;

	class Environment
	{
		/// <summary>
		/// Specifies enumerated constants used to retrieve directory paths to system special folders.
		/// </summary>
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
		static Version Version_();
	};
}

#endif //_ENVIRONMENT_
