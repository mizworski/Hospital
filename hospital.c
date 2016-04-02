#include <stdbool.h>
#include <string.h>

#include "parse.h"
#include "structure.h"

#define DEBUG_MODE          "-v"
#define LINE_WAS_NOT_READ   -1

int main (int argc, char **argv) {
    int operationCode;
    int integerArgument;
    char *stringArgument1;
    char *stringArgument2;
    char *stringArgument3;
    bool debugMode = false;

    // Checks if program was executed in debug mode.
    for(int i = 0; i < argc; i++) {
        if (strcmp(DEBUG_MODE, argv[i]) == 0) {
            debugMode = true;
        }
    }

    initializeHospitalGlobalData();

    do {
        operationCode = readSingleLineAndReturnOperationCode(&integerArgument,
                                                             &stringArgument1,
                                                             &stringArgument2,
                                                             &stringArgument3);
        performOperation(operationCode,
                         &integerArgument,
                         &stringArgument1,
                         &stringArgument2,
                         &stringArgument3);

        if (debugMode) {
            debugModePrintDescriptions();
        }
    } while (operationCode != LINE_WAS_NOT_READ);

    clearAllocatedMemory();

    return 0;
}