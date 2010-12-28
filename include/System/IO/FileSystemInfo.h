#ifndef _IO_FILESYSTEMINFO_
#define _IO_FILESYSTEMINFO_

namespace System
{
	namespace IO
	{
		class FileSystemInfo
		{
		protected:
			char* FullPath;
			char* OriginalPath;

		public:
			virtual char* FullName();
		};
	}
}

#endif //_IO_FILESYSTEMINFO_
