#ifndef _SASSERT_H
#define _SASSERT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"

#undef sassert

#ifdef NDEBUG           /* required by ANSI standard */
#define sassert(e,s)  	((void)0)
#else
//! Causes a blue screen of death if e is not true with the msg "msg" displayed
#define sassert(e,msg)       ((e) ? (void)0 : __sassert(__FILE__, __LINE__, #e, msg))

#endif /* NDEBUG */

void __sassert(const char *fileName, int lineNumber, const char* conditionString, const char* message);

#ifdef __cplusplus
}
#endif

#endif //_SASSERT_H
