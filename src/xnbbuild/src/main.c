#if _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Path.h"
#include "TryCatchFinally.h"

/**
 * Application entry point
 *
 * @param argc
 * The amount of values passed in argv.
 *
 * @param argv
 * An array of strings that contains the command-line arguments.
 *
 * @return
 * Application error code
 */
int main(int argc, char** argv)
{
	FILE *fpIn = NULL;
	FILE *fpOut = NULL;
	const char * inFile = NULL;
	const char * outDir = NULL;
	int i;

	if (argc == 0)
	{
		printf("");
	}

	for (i = 0; i < argc; i++)
	{
		if (strncmp(argv[i], "-outdir", 7) == 0)
		{
			
		}

		if (argc > 0)
		{
			inFile = Path.GetFileName(argv[argc - 1]);
		}
	}

	TRY
		fpIn = fopen(inFile, "rb");
		fpOut = fopen(Path.Combine(outDir, inFile), "wb");


	FINALLY
		break;
	ETRY;

	return 0;
}
