#ifndef _SYSTEM_IO_FILESYSTEMINFO_
#define _SYSTEM_IO_FILESYSTEMINFO_

#include <System/Object.h>

namespace System
{
	namespace IO
	{
		class FileSystemInfo : public virtual Object
		{
		protected:
			virtual ~FileSystemInfo() {}
			String FullPath;
			String OriginalPath;

		public:
			virtual const char* FullName();
		};
	}
}

#endif //_IO_FILESYSTEMINFO_
