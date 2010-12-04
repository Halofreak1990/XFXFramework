/********************************************************
 *	System.h											*
 *														*
 *	XFX System namespace include file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef SYSTEM_H
#define SYSTEM_H

//For more resemblance to XNA and easier differentiating between normal classes and interface types
#define interface class

//For documentation purposes
#define out

#ifdef ENABLE_XBOX
//Include commonly used OpenXDK headers
extern "C" {
#include <hal/xbox.h>
#include <openxdk/openxdk.h>
#include <xboxkrnl/hal.h>
#include <xboxkrnl/xboxkrnl.h>
#include <openxdk/debug.h>
#endif

#include <string.h>
}

#include "IDisposable.h"
#include "IServiceProvider.h"
#include "Math.h"
#include "Thread.h"
#include "TimeSpan.h"

#endif //SYSTEM_H
