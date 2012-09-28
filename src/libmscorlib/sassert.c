#include <sassert.h>

#include <openxdk/debug.h>
#include <hal/xbox.h>

void __sassert(const char *fileName, int lineNumber, const char* conditionString, const char* message)
{
	debugClearScreen();
    debugPrint("\tAssertion!\n\tFile: \n%s\n\nLine: %d\n\nCondition:\n%s\n\n\t%s", fileName, lineNumber, conditionString, message);

	XSleep(100);

    __asm__ ("cli\nhlt");
}
