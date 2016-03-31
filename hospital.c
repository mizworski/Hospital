#include "parse.h"
#include "structure.h"

int main (void) {
    int operationCode;
    int integerArgument;
    char *stringArgument1;
    char *stringArgument2;
    char *stringArgument3;

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
    } while (operationCode != -1);

    clearAllocatedMemory();

    return 0;
}