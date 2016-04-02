#include <stdbool.h>
#include <string.h>

#include "parse.h"
#include "structure.h"

#define DEBUG_MODE          "-v"

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

    initializeHospitalGlobalData();

    operationCode = readSingleLineAndReturnOperationCode(&integerArgument,
                                                         &stringArgument1,
                                                         &stringArgument2);
    /*int i = 0; // dsdsdsd*/
    while (operationCode != LINE_WAS_NOT_READ /*&& i < 10*/) { // dsdsds
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
        /*i++; // DASDAD*/
    }

    clearAllocatedMemory();

    return 0;
}