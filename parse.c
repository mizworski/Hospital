#include "parse.h"

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

    // Finds first char in operationString that is space or new line.
    while (operationString[charCount] != ' ' &&
           operationString[charCount] != '\n') {
        charCount++;
    }

    // Number or chars skipped in loop.
    *charsShiftInString = (size_t) charCount;

    // Compares lengths of operations defined in specification and operations
    // string itself with first charsShiftInString chars of operationString
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

    // Adds one to get position of first char after operation.
    (*charsShiftInString)++;

    // Identifies which procedure was called.
    return operationCode;
}

char* getSingleArgumentFromString(char **bufferedString) {
    int charCount = 0;
    char *argumentFromString = NULL;

    // Counts chars in single word read from bufferedString.
    while ((*bufferedString)[charCount] != ' ' &&
           (*bufferedString)[charCount] != '\0') {
        charCount++;
    }

    // Allocates memory for new string with length of charCount + 1
    // (for \0 char at the end of the string).
    // Then copies string from bufferedString and set last char as '\0'.
    argumentFromString = malloc((charCount + 1) * sizeof(char));
    strncpy(argumentFromString, *bufferedString, (size_t) charCount);
    argumentFromString[charCount] = '\0';

    // Adds one to skip whitespace in bufferedString.
    *bufferedString += charCount + 1;

    // Returns string that is requested argument.
    return argumentFromString;
}

// Does almost the same in exception of that it does not read to the first
// whitespace but instead to the '\n' and then sets last char of string as '\0'.
char* getStringTillEndLine(char **bufferedString) {
    int charCount = 0;
    char *argumentFromString = NULL;

    while ((*bufferedString)[charCount] != '\n') {
        charCount++;
    }

    argumentFromString = malloc((charCount + 1) * sizeof(char));

    strncpy(argumentFromString, *bufferedString, (size_t) charCount);
    argumentFromString[charCount] = '\0';

    return argumentFromString;
}

void getArgumentsFromString(char *bufferedString,
                            int operationCode,
                            int *integerArgument,
                            char **stringArgument1,
                            char **stringArgument2) {
    // Dummy pointer required for strtol() function call but was not used.
    char **dummyPointer = NULL;
    // Integer buffer is used to keep string that was read from
    // bufferedString in order to free it afterwards.
    char *integerBuffer = NULL;

    // Gets arguments from bufferedString and then sets arguments values
    // given to the function.
    switch (operationCode) {
        case NEW_DISEASE_ENTER_DESCRIPTION:
            *stringArgument1 = getSingleArgumentFromString(&bufferedString);
            *stringArgument2 = getStringTillEndLine(&bufferedString);
            *integerArgument = -1;
            break;
        case NEW_DISEASE_COPY_DESCRIPTION:
            *stringArgument1 = getSingleArgumentFromString(&bufferedString);
            *stringArgument2 = getStringTillEndLine(&bufferedString);
            *integerArgument = -1;
            break;
        case CHANGE_DESCRIPTION:
            *stringArgument1 = getSingleArgumentFromString(&bufferedString);
            integerBuffer = getSingleArgumentFromString(&bufferedString);
            *integerArgument =
                    (int) strtol(integerBuffer,
                                 dummyPointer,
                                 INTEGER_FROM_STRING_BASE);
            free(integerBuffer);
            integerBuffer = NULL;
            *stringArgument2 = getStringTillEndLine(&bufferedString);
            break;
        case PRINT_DESCRIPTION:
            *stringArgument1 = getSingleArgumentFromString(&bufferedString);
            integerBuffer = getStringTillEndLine(&bufferedString);
            *integerArgument = (int) strtol(integerBuffer,
                                            dummyPointer,
                                            INTEGER_FROM_STRING_BASE);
            free(integerBuffer);
            integerBuffer = NULL;
            break;
        case DELETE_PATIENT_DATA:
            *stringArgument1 = getStringTillEndLine(&bufferedString);
            *stringArgument2 = NULL;
            *integerArgument = -1;
            break;
        case WRONG_INPUT:
            break;
        default:
            break;
    }
}

// Value needed to optimise allocation of bufferedString.
int getReadLineLength(char *lineRead) {
    int charCount = 0;

    while (lineRead[charCount] != '\n' && charCount < MAX_LINE_SIZE) {
        charCount++;
    }

    return charCount;
}

int readSingleLineAndReturnOperationCode(int *integerArgument,
                                         char **stringArgument1,
                                         char **stringArgument2) {
    char *lineReadArrayPointer = NULL;
    char lineRead[MAX_LINE_SIZE];
    char *bufferedString = NULL;
    // Pointer needed to free firstly allocated bufferedString.
    char *bufferStartingPoint = bufferedString;
    int operationCode;
    int readLineLength;

    // When function fails to read new line it returns null.
    lineReadArrayPointer = fgets(lineRead, MAX_LINE_SIZE, stdin);

    // Allocation of bufferedString
    if (lineReadArrayPointer != NULL) {
        readLineLength = getReadLineLength(lineRead);
        bufferedString = malloc(readLineLength * sizeof(char));
        bufferStartingPoint = bufferedString;
    }

    if (lineReadArrayPointer == NULL) {
        operationCode = LINE_WAS_NOT_READ;
    } else {
        size_t charsShiftInString;

        // Gets operation code of available operations.
        operationCode = getOperationCode(lineRead, &charsShiftInString);

        // Copies lineRead shifted by number of characters, that was used by
        // procedure call, to bufferedString.
        // Safe to use because bufferString size is not greater than
        // MAX_LINE_SIZE
        strcpy(bufferedString, lineReadArrayPointer + charsShiftInString);

        getArgumentsFromString(bufferedString,
                               operationCode,
                               integerArgument,
                               stringArgument1,
                               stringArgument2);
    }

    // Frees buffer that is not needed anymore.
    free(bufferStartingPoint);

    return operationCode;
}
