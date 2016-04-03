#include <stdbool.h>
#include <string.h>

#include "parse.h"
#include "structure.h"

#define DEBUG_MODE  "-v"

int main (int argc, char **argv) {
    int operationCode;
    int integerArgument;
    char *stringArgument1 = NULL;
    char *stringArgument2 = NULL;
    bool debugMode = false;

    // Checks if program was executed in debug mode.
    for(int i = 0; i < argc; i++) {
        if (strcmp(DEBUG_MODE, argv[i]) == 0) {
            debugMode = true;
        }
    }

    // Initializes global structure where patients list and descriptions
    // count is stored.
    initializeHospitalGlobalData();

    // Reads line for the first time.
    operationCode = readSingleLineAndReturnOperationCode(&integerArgument,
                                                         &stringArgument1,
                                                         &stringArgument2);
    while (operationCode != LINE_WAS_NOT_READ ) {
        performOperation(operationCode,
                         &integerArgument,
                         stringArgument1,
                         stringArgument2);

        if (debugMode) {
            debugModePrintDescriptions();
        }

        operationCode = readSingleLineAndReturnOperationCode(&integerArgument,
                                                             &stringArgument1,
                                                             &stringArgument2);
    }

    // Frees memory that was used during program runtime.
    freeAllocatedMemory();

    return 0;
}