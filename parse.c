#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WAS_NOT_READ -1
#define WRONG_INPUT 0
#define NEW_DISEASE_ENTER_DESCRIPTION 1
#define NEW_DISEASE_COPY_DESCRIPTION 2
#define CHANGE_DESCRIPTION 3
#define PRINT_DESCRIPTION 4
#define DELETE_PATIENT_DATA 5
#define MAX_ARGUMENT_QUANTITY 5
#define DELIMITERS " "
#define DEFAULT_BUFFER_SIZE 0
#define INTEGER_FROM_STRING_BASE 10
#define INTEGER_ARGUMENT_POSITION stringTokens[2]

// Z tymi definami jest problem, bo jak daje liczbe jako input, to nie wywala
// bledu. albo i nie, bo z normalnym inputem tez jest lipa.

int readSingleLineAndReturnOperationCode (int *integerArgument,
                                          char **stringArgument1,
                                          char **stringArgument2,
                                          char **stringArgument3) {
    char *lineReadFromStdin = NULL;
    char *stringTokens[MAX_ARGUMENT_QUANTITY];
    char *ptr; // Useless dummy.
    int operationCode = LINE_WAS_NOT_READ;
    size_t bufferSize = DEFAULT_BUFFER_SIZE; // Dummy.
    ssize_t lineLength;

    lineLength = getline(&lineReadFromStdin, &bufferSize, stdin);

    if (lineLength != LINE_WAS_NOT_READ) {
        int i = 1;

        stringTokens[0] = strtok(lineReadFromStdin, DELIMITERS);
        while (i < MAX_ARGUMENT_QUANTITY && stringTokens[i] != NULL) // Lazy evaluation.
        {
            stringTokens[i++] = strtok(NULL, DELIMITERS);
        }

        if (strcmp(stringTokens[0], "NEW_DISEASE_ENTER_DESCRIPTION")) {
            operationCode = NEW_DISEASE_ENTER_DESCRIPTION;
            stringArgument1 = &stringTokens[1];
            stringArgument2 = &stringTokens[2];
            stringArgument3 = &stringTokens[3];
        } else if (strcmp(stringTokens[0], "NEW_DISEASE_COPY_DESCRIPTION")) {
            operationCode = NEW_DISEASE_COPY_DESCRIPTION;
            stringArgument1 = &stringTokens[1];
            stringArgument2 = &stringTokens[2];
        } else if (strcmp(stringTokens[0], "CHANGE_DESCRIPTION")) {
            operationCode = CHANGE_DESCRIPTION;
            *integerArgument = (int) strtol(INTEGER_ARGUMENT_POSITION,
                                            &ptr,
                                            INTEGER_FROM_STRING_BASE);
            stringArgument1 = &stringTokens[1];
            stringArgument2 = &stringTokens[3];
            stringArgument3 = &stringTokens[4];
        } else if (strcmp(stringTokens[0], "PRINT_DESCRIPTION")) {
            operationCode = PRINT_DESCRIPTION;
            *integerArgument = (int) strtol(INTEGER_ARGUMENT_POSITION,
                                            &ptr,
                                            INTEGER_FROM_STRING_BASE);
            stringArgument1 = &stringTokens[1];
        } else if (strcmp(stringTokens[0], "DELETE_PATIENT_DATA")) {
            operationCode = DELETE_PATIENT_DATA;
            stringArgument1 = &stringTokens[1];
        } else {
            operationCode = WRONG_INPUT;
        }
    }

    return operationCode;
}