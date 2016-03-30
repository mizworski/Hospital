#ifndef IPP_1_PARSE_H
#define IPP_1_PARSE_H

#endif //IPP_1_PARSE_H
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