#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readSingleLineAndReturnOperationCode (int *integerArgument,
                                          char **stringArgument1,
                                          char **stringArgument2,
                                          char **stringArgument3) {
    char *line = NULL;
    char *stringTokens[5];
    char *ptr; // Useless dummy.
    int operationCode = -1;
    size_t bufferSize = 0;
    ssize_t lineLength;

    lineLength = getline(&line, &bufferSize, stdin);

    if (lineLength != -1) {
        int i = 1;
        stringTokens[0] = strtok(line, " ");
        while (i < 5 && stringTokens[i] != NULL) // Lazy evaluation.
        {
            stringTokens[i++] = strtok(NULL, " ");
        }

        if (strcmp(stringTokens[0], "NEW_DISEASE_ENTER_DESCRIPTION")) {
            operationCode = 1;
            stringArgument1 = &stringTokens[1];
            stringArgument2 = &stringTokens[2];
            stringArgument3 = &stringTokens[3];
        } else if (strcmp(stringTokens[0], "NEW_DISEASE_COPY_DESCRIPTION")) {
            operationCode = 2;
            stringArgument1 = &stringTokens[1];
            stringArgument2 = &stringTokens[2];
        } else if (strcmp(stringTokens[0], "CHANGE_DESCRIPTION")) {
            operationCode = 3;
            *integerArgument = (int) strtol(stringTokens[2], &ptr, 10);
            stringArgument1 = &stringTokens[1];
            stringArgument2 = &stringTokens[3];
            stringArgument3 = &stringTokens[4];
        } else if (strcmp(stringTokens[0], "PRINT_DESCRIPTION")) {
            operationCode = 4;
            *integerArgument = (int) strtol(stringTokens[2], &ptr, 10);
            stringArgument1 = &stringTokens[1];
        } else if (strcmp(stringTokens[0], "DELETE_PATIENT_DATA")) {
            operationCode = 5;
            stringArgument1 = &stringTokens[1];
        } else {
            operationCode = 0;
        }
    }

    return operationCode;
}