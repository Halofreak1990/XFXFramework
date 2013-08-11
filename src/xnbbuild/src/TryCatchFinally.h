#ifndef _TRYCATCHFINALLY_H
#define _TRYCATCHFINALLY_H

#include <stdio.h>
#include <setjmp.h>

#define TRY do{ jmp_buf ex_buf__; switch(setjmp(ex_buf__) ){ case 0: while(1){
#define CATCH(x) break; case x:
#define FINALLY break; } default:
#define ETRY } }while(0)
#define THROW(x) longjmp(ex_buf__, x)

#endif //_TRYCATCHFINALLY_H
