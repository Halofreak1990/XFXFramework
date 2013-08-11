#if _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Path.h"

const char * Path_Combine(char const * const path1, char const * const path2)
{
	const char * strPtr = NULL;
	char * pathString = NULL;
	size_t newLen = 0;

	strPtr = strrchr(path1, '\\');

	if (((size_t)strPtr - (size_t)path1) != 0)
	{
		newLen = strlen(path1) + 1 + strlen(path2);

		pathString = (char *)malloc(newLen + 1);

		sprintf(pathString, "%s\\%s", path1, path2);
	}
	else
	{
		newLen = strlen(path1) + strlen(path2);

		pathString = (char *)malloc(newLen + 1);

		sprintf(pathString, "%s%s", path1, path2);
	}

	pathString[newLen] = '\0';

	return pathString;
}

const char * Path_GetDirectory(char const * const path)
{
	const char * strPtr = NULL;
	size_t pathLen = 0;
	char * pathString;

	strPtr = strrchr(path, '\\');

	pathLen = (size_t)strPtr - (size_t)path;

	pathString = (char *)malloc(pathLen + 1);

	strncpy(pathString, path, pathLen);

	pathString[pathLen] = '\0';

	return pathString;
}

const char * Path_GetExtension(char const * const path)
{
	const char * strPtr = NULL;
	size_t pathLen = 0;
	size_t strLen = 0;
	char * pathString = NULL;

	strPtr = strrchr(path, '.');

	if (strPtr == NULL)
	{
		// no extension, return an empty string.
		return "";
	}

	strLen = strlen(path);

	pathLen = (size_t)strPtr - (size_t)path;

	strLen -= pathLen;

	pathString = (char *)malloc(strLen + 1);

	strncpy(pathString, strPtr + 1, strLen);

	pathString[strLen] = '\0';

	return pathString;
}

const char * Path_GetFileName(char const * const path)
{
	const char * strPtr = NULL;
	size_t pathLen = 0;
	size_t strLen = 0;
	char * pathString = NULL;

	strPtr = strrchr(path, '\\');

	strLen = strlen(path);

	pathLen = (size_t)strPtr - (size_t)path;

	strLen -= pathLen;

	pathString = (char *)malloc(strLen + 1);

	strncpy(pathString, strPtr + 1, strLen);

	pathString[strLen] = '\0';

	return pathString;
}

const char * Path_GetFileNameWithoutExtension(char const * const path)
{
	const char * strPtr = NULL;
	size_t pathLen = 0;
	char * pathString = NULL;
	const char * fileName = NULL;

	fileName = Path_GetFileName(path);

	strPtr = strchr(fileName, '.');

	pathLen = (size_t)strPtr - (size_t)fileName;

	pathString = (char *)malloc(pathLen + 1);

	strncpy(pathString, fileName, pathLen);

	free((void *)fileName);

	pathString[pathLen] = '\0';

	return pathString;
}

struct _path Path = 
{
	Path_Combine,
	Path_GetDirectory,
	Path_GetExtension,
	Path_GetFileName,
	Path_GetFileNameWithoutExtension
};
