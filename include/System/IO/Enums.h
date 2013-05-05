#ifndef _SYSTEM_IO_ENUMS_
#define _SYSTEM_IO_ENUMS_

namespace System
{
	namespace IO
	{
		// Defines constants for read, write, or read/write access to a file.
		struct FileAccess
		{
			enum type
			{
				Read = 1,
				ReadWrite = 3,
				Write = 2
			};
		};

		// Provides attributes for files and directories.
		struct FileAttributes
		{
			enum type
			{
				Archive = 32,
				Compressed = 2048,
				Device = 64,
				Directory = 16,
				Encrypted = 16384,
				Hidden = 2,
				Normal = 128,
				NotContentIndexed = 8192,
				Offline = 4096,
				ReadOnly = 1,
				ReparsePoint = 1024,
				SparseFile = 512,
				System = 4,
				Temporary = 256
			};
		};

		// Specifies how the operating system should open a file.
		struct FileMode
		{
			enum type
			{
				Append = 6,
				Create = 2,
				CreateNew = 1,
				Open = 3,
				OpenOrCreate = 4,
				Truncate = 5
			};
		};

		// Represents additional options for creating a FileStream object.
		struct FileOptions
		{
			enum type
			{
				Asynchronous = 0x40000000,
				DeleteOnClose = 0x4000000,
				Encrypted = 0x4000,
				None = 0,
				RandomAccess = 0x10000000,
				SequentialScan = 0x8000000,
				WriteThrough = 0x80000000
			};
		};

		// Contains constants for controlling the kind of access other System.IO.FileStream objects can have to the same file.
		struct FileShare
		{
			enum type
			{
				None = 0,
				Read = 1,
				ReadWrite = 3,
				Write = 2
			};
		};

		// Provides the fields that represent reference points in streams for seeking.
		struct SeekOrigin
		{
			enum type
			{
				Begin,
				Current,
				End
			};
		};

		typedef FileAccess::type		FileAccess_t;
		typedef FileAttributes::type	FileAttributes_t;
		typedef FileMode::type			FileMode_t;
		typedef FileOptions::type		FileOptions_t;
		typedef FileShare::type			FileShare_t;
		typedef SeekOrigin::type		SeekOrigin_t;
	}
}

#endif //_SYSTEM_IO_ENUMS_
