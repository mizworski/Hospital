#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WAS_NOT_READ   -1

int getOperationCode(char *operationString, size_t *charsShiftInString);

char* getSingleArgumentFromString(char **bufferedString);

void getArgumentsFromString(char *bufferedString,
                            int operationCode,
                            int *integerArgument,
                            char **stringArgument1,
                            char **stringArgument2);

int readSingleLineAndReturnOperationCode (int *integerArgument,
                                          char **stringArgument1,
                                          char **stringArgument2);
#endif /* PARSE_H */