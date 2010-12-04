#ifndef __APICompat_H__

#define __APICompat_H__


#include <string.h>

#include <hal/fileio.h>


extern "C" {

#include <xboxkrnl/xboxkrnl.h>

#include <hal/xbox.h>

#include <hal/fileio.h>

}


#define Sleep XSleep



/* Port IO */

unsigned char _outp(unsigned short port, unsigned char databyte);

unsigned short _outpw(unsigned short port, unsigned short dataword);

unsigned long _outpd(unsigned short port, unsigned long dataword);

unsigned char _inp(unsigned short port);

unsigned short _inpw(unsigned short port);

unsigned long _inpd(unsigned short port);



/* Misc */

#define min(A, B) ((A) < (B)) ? (A) : (B)

char *itoa(int value, char *buffer, int radix);

void *ZeroMemory(void *s, size_t n);

#endif
