#ifndef _PATH_H
#define _PATH_H

struct _path
{
	const char * (*Combine)(char const * const, char const * const);
	const char * (*GetDirectory)(char const * const);
	const char * (*GetExtension)(char const * const);
	const char * (*GetFileName)(char const * const);
	const char * (*GetFileNameWithoutExtension)(char const * const);
};

extern struct _path Path;

#endif //_PATH_H
