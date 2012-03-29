#include <sassert.h>

#include <openxdk/debug.h>

void __sassert(const char *fileName, int lineNumber, const char* conditionString, const char* message)
{
	debugClearScreen();
    debugPrint("\x1b[j\x1b[42mAssertion!\n\x1b[39mFile: \n%s\n\nLine: %d\n\nCondition:\n%s\n\n\x1b[41m%s", fileName, lineNumber, conditionString, message);

    __asm__ ("cli\nhlt");
}
