#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WAS_NOT_READ                       -1
#define WRONG_INPUT                             0
#define NEW_DISEASE_ENTER_DESCRIPTION           1
#define NEW_DISEASE_COPY_DESCRIPTION            2
#define CHANGE_DESCRIPTION                      3
#define PRINT_DESCRIPTION                       4
#define DELETE_PATIENT_DATA                     5
#define MAX_LINE_SIZE                           100001 // \0 at the end of string.
#define INTEGER_FROM_STRING_BASE                10

#define NEW_DISEASE_ENTER_DESCRIPTION_LENGTH    strlen("NEW_DISEASE_ENTER_DESCRIPTION")
#define NEW_DISEASE_COPY_DESCRIPTION_LENGTH     strlen("NEW_DISEASE_COPY_DESCRIPTION")
#define CHANGE_DESCRIPTION_LENGTH               strlen("CHANGE_DESCRIPTION")
#define PRINT_DESCRIPTION_LENGTH                strlen("PRINT_DESCRIPTION")
#define DELETE_PATIENT_DATA_LENGTH              strlen("DELETE_PATIENT_DATA")

int getOperationCode(char *operationString, size_t *charsShiftInString) {
    int operationCode;
    int charCount = 0;

    while (operationString[charCount] != ' ' && operationString[charCount] != '\n') {
        charCount++;
    }

    *charsShiftInString = (size_t) charCount;

    if (*charsShiftInString == NEW_DISEASE_ENTER_DESCRIPTION_LENGTH &&
        (strncmp(operationString, "NEW_DISEASE_ENTER_DESCRIPTION", *charsShiftInString) == 0)) {
        operationCode = NEW_DISEASE_ENTER_DESCRIPTION;
    } else if (*charsShiftInString == NEW_DISEASE_COPY_DESCRIPTION_LENGTH &&
               (strncmp(operationString, "NEW_DISEASE_COPY_DESCRIPTION", *charsShiftInString) == 0)) {
        operationCode = NEW_DISEASE_COPY_DESCRIPTION;
    } else if (*charsShiftInString == CHANGE_DESCRIPTION_LENGTH &&
               (strncmp(operationString, "CHANGE_DESCRIPTION", *charsShiftInString)) == 0) {
        operationCode = CHANGE_DESCRIPTION;
    } else if (*charsShiftInString == PRINT_DESCRIPTION_LENGTH &&
               (strncmp(operationString, "PRINT_DESCRIPTION", *charsShiftInString)) == 0) {
        operationCode = PRINT_DESCRIPTION;
    } else if (*charsShiftInString == DELETE_PATIENT_DATA_LENGTH &&
               (strncmp(operationString, "DELETE_PATIENT_DATA", *charsShiftInString)) == 0) {
        operationCode = DELETE_PATIENT_DATA;
    } else {
        operationCode = WRONG_INPUT;
    }

    // Adds one to get position of first char.
    (*charsShiftInString)++;

    return operationCode;
}

char* getSingleArgumentFromString(char **bufferedString) {
    int charCount = 0;
    char *argumentFromString = NULL;

    while ((*bufferedString)[charCount] != ' ' &&
           (*bufferedString)[charCount] != '\n') {
        charCount++;
    }

    argumentFromString = malloc((charCount + 1) * sizeof(char));

    strncpy(argumentFromString, *bufferedString, (size_t) charCount);

    // Adds one to skip whitespace.
    *bufferedString += charCount + 1;

    return argumentFromString;
}

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
            *integerArgument = -1;
            break;
        case NEW_DISEASE_COPY_DESCRIPTION:
            *stringArgument1 = getSingleArgumentFromString(&bufferedString);
            *stringArgument2 = bufferedString;
            *stringArgument3 = NULL;
            *integerArgument = -1;
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
            *stringArgument2 = NULL;
            *stringArgument3 = NULL;
            break;
        case DELETE_PATIENT_DATA:
            *stringArgument1 = getSingleArgumentFromString(&bufferedString);
            *stringArgument2 = NULL;
            *stringArgument3 = NULL;
            *integerArgument = -1;
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
    char *lineReadArrayPointer = NULL;
    char lineRead[MAX_LINE_SIZE];
    char *bufferedString = malloc(MAX_LINE_SIZE * sizeof(char));
    int operationCode;

    lineReadArrayPointer = fgets(lineRead, MAX_LINE_SIZE, stdin);
    lineRead[strcspn(lineRead, "\n")] = 0;

    if (lineReadArrayPointer == NULL) {
        operationCode = LINE_WAS_NOT_READ;
    } else {
        size_t charsShiftInString;

        operationCode = getOperationCode(lineRead, &charsShiftInString);

        strcpy(bufferedString, lineReadArrayPointer + charsShiftInString);

        getArgumentsFromString(bufferedString,
                               operationCode,
                               integerArgument,
                               stringArgument1,
                               stringArgument2,
                               stringArgument3);
    }

    return operationCode;
}
