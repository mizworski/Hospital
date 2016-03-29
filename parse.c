#include <stdio.h>

int readSingleLineAndReturnOperationCode (int *integerArgument,
                                          char **stringArgument1,
                                          char **stringArgument2,
                                          char **stringArgument3) {
    char *line = NULL;
    int operationCode = -1;
    size_t bufferSize = 0;
    ssize_t lineLength;

    lineLength = getline(&line, &bufferSize, stdin);

    if (lineLength != -1) {
        
    }

    return operationCode;
}