#include <stdio.h>

int getOperationCode(char *operationString, size_t *charsShiftInString);

char* getSingleArgumentFromString(char **bufferedString);

void getArgumentsFromString(char *bufferedString,
                            int operationCode,
                            int *integerArgument,
                            char **stringArgument1,
                            char **stringArgument2,
                            char **stringArgument3);

int readSingleLineAndReturnOperationCode (int *integerArgument,
                                          char **stringArgument1,
                                          char **stringArgument2,
                                          char **stringArgument3);