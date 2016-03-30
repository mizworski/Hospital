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
#define MAX_LINE_SIZE 100000
#define MAX_ARGUMENT_QUANTITY 5
#define DELIMITERS " "
#define DEFAULT_BUFFER_SIZE 0
#define INTEGER_FROM_STRING_BASE 10
#define INTEGER_ARGUMENT_POSITION stringTokens[2]

// Z tymi definami jest problem, bo jak daje liczbe jako input, to nie wywala
// bledu. albo i nie, bo z normalnym inputem tez jest lipa.

int getOperationCode(char *operationString, size_t *charsShiftInString) {
    int operationCode;
    int charCount = 0;

    while (operationString[charCount] != ' ' && operationString[charCount] != '\n') {
        charCount++;
    }

    *charsShiftInString = (size_t) charCount;

    if ((strncmp(operationString, "NEW_DISEASE_ENTER_DESCRIPTION", *charsShiftInString) == 0)) {
        operationCode = NEW_DISEASE_ENTER_DESCRIPTION;
    } else if ((strncmp(operationString, "NEW_DISEASE_COPY_DESCRIPTION", *charsShiftInString)) == 0) {
        operationCode = NEW_DISEASE_COPY_DESCRIPTION;
    } else if ((strncmp(operationString, "CHANGE_DESCRIPTION", *charsShiftInString)) == 0) {
        operationCode = CHANGE_DESCRIPTION;
    } else if ((strncmp(operationString, "PRINT_DESCRIPTION", *charsShiftInString)) == 0) {
        operationCode = PRINT_DESCRIPTION;
    } else if ((strncmp(operationString, "DELETE_PATIENT_DATA", *charsShiftInString)) == 0) {
        operationCode = DELETE_PATIENT_DATA;
    } else {
        operationCode = WRONG_INPUT;
    }

    return operationCode;
}

void getArgumentsFromString(char *bufferedString,
                            int operationCode,
                            int *integerArgument,
                            char **stringArgument1,
                            char **stringArgument2,
                            char **stringArgument3) {
    switch (operationCode) {
        case NEW_DISEASE_ENTER_DESCRIPTION:
            break;
        case NEW_DISEASE_COPY_DESCRIPTION:
            break;
        case CHANGE_DESCRIPTION:
            break;
        case PRINT_DESCRIPTION:
            break;
        case DELETE_PATIENT_DATA:
            break;
        case WRONG_INPUT:
            break;
        default: // There is no default.
            break;
    }
}

int readSingleLineAndReturnOperationCode(int *integerArgument,
                                         char **stringArgument1,
                                         char **stringArgument2,
                                         char **stringArgument3) {
    char *lineReadFromStdin = NULL;
    char bufferedString[MAX_LINE_SIZE];
    int operationCode;
    size_t bufferSize = DEFAULT_BUFFER_SIZE; // Dummy.
    ssize_t lineLength;

    lineLength = getline(&lineReadFromStdin, &bufferSize, stdin);

    if (lineLength == LINE_WAS_NOT_READ) {
        operationCode = LINE_WAS_NOT_READ;
    } else {
        size_t charsShiftInString;

        operationCode = getOperationCode(lineReadFromStdin, &charsShiftInString);

        strcpy(bufferedString, lineReadFromStdin + charsShiftInString);

        getArgumentsFromString(bufferedString,
                               operationCode,
                               integerArgument,
                               stringArgument1,
                               stringArgument2,
                               stringArgument3);
    }
        /*
        if ((strcmp(stringTokens[0], "NEW_DISEASE_ENTER_DESCRIPTION")) == 0) {
            operationCode = NEW_DISEASE_ENTER_DESCRIPTION;
            stringArgument1 = &stringTokens[1];
            stringArgument2 = &stringTokens[2];
            stringArgument3 = &stringTokens[3];
        } else if ((strcmp(stringTokens[0], "NEW_DISEASE_COPY_DESCRIPTION"))
                   == 0) { // where to break?
            operationCode = NEW_DISEASE_COPY_DESCRIPTION;
            stringArgument1 = &stringTokens[1];
            stringArgument2 = &stringTokens[2];
        } else if ((strcmp(stringTokens[0], "CHANGE_DESCRIPTION")) == 0) {
            operationCode = CHANGE_DESCRIPTION;
            *integerArgument = (int) strtol(INTEGER_ARGUMENT_POSITION,
                                            &ptr,
                                            INTEGER_FROM_STRING_BASE);
            stringArgument1 = &stringTokens[1];
            stringArgument2 = &stringTokens[3];
            stringArgument3 = &stringTokens[4];
        } else if ((strcmp(stringTokens[0], "PRINT_DESCRIPTION")) == 0) {
            operationCode = PRINT_DESCRIPTION;
            *integerArgument = (int) strtol(INTEGER_ARGUMENT_POSITION,
                                            &ptr,
                                            INTEGER_FROM_STRING_BASE);
            stringArgument1 = &stringTokens[1];
        } else if ((strcmp(stringTokens[0], "DELETE_PATIENT_DATA")) == 0) {
            operationCode = DELETE_PATIENT_DATA;
            stringArgument1 = &stringTokens[1];
        } else {
            operationCode = WRONG_INPUT;
        }*/

    return operationCode;
}
