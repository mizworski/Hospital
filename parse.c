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
#define DEFAULT_BUFFER_SIZE 0
#define INTEGER_FROM_STRING_BASE 10

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

char* getSingleArgumentFromString(char **bufferedString) {
    int charCount = 0;
    char* argumentFromString = NULL;
    while (*bufferedString[charCount] != ' ' &&
           *bufferedString[charCount] != '\n') {
        charCount++;
    }

    strncpy(*bufferedString, argumentFromString, (size_t) charCount);

    // Adds one to skip whitespace.
    *bufferedString += charCount + 1;

    return argumentFromString;
}

// TODO remove \n from the end of the string.

void getArgumentsFromString(char *bufferedString,
                            int operationCode,
                            int *integerArgument,
                            char **stringArgument1,
                            char **stringArgument2,
                            char **stringArgument3) {
    char **dummyPointer = NULL;
    switch (operationCode) {
        case NEW_DISEASE_ENTER_DESCRIPTION:
            *stringArgument1 = getSingleArgumentFromString(&bufferedString);
            *stringArgument2 = getSingleArgumentFromString(&bufferedString);
            *stringArgument3 = bufferedString;
            break;
        case NEW_DISEASE_COPY_DESCRIPTION:
            *stringArgument1 = getSingleArgumentFromString(&bufferedString);
            *stringArgument2 = bufferedString;
            break;
        case CHANGE_DESCRIPTION:
            *stringArgument1 = getSingleArgumentFromString(&bufferedString);
            *integerArgument =
                    (int) strtol(getSingleArgumentFromString(&bufferedString),
                           dummyPointer,
                           INTEGER_FROM_STRING_BASE);
            *stringArgument2 = getSingleArgumentFromString(&bufferedString);
            *stringArgument3 = bufferedString;
            break;
        case PRINT_DESCRIPTION:
            *stringArgument1 = getSingleArgumentFromString(&bufferedString);
            *integerArgument = (int) strtol(bufferedString,
                                            dummyPointer,
                                            INTEGER_FROM_STRING_BASE);
            break;
        case DELETE_PATIENT_DATA:
            *stringArgument1 = getSingleArgumentFromString(&bufferedString);
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

    return operationCode;
}
