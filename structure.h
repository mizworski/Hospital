#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct patient patient;
typedef struct diseaseStructure diseaseStructure;
typedef struct diseaseListNode diseaseListNode;

struct diseaseStructure {
    char *diseaseDescription;
    int referenceCount;
};

struct diseaseListNode {
    diseaseListNode *nextDisease;
    diseaseStructure *diseaseReference;
};

struct patient {
    char *patientName;
    diseaseListNode *diseaseListHead;
    diseaseListNode *diseaseListLast;
    patient *nextPatient;
};

void initializeHospitalGlobalData(void);

void printIgnoredUponFailure(void);

void printOKUponSuccess(void);

void debugModePrintDescriptions(void);

void decreaseCountAndDeleteIfNotReferred(diseaseStructure *diseaseReference);

patient* findPatientPrecedingGivenName(char *patientName);

patient* getPatientPointerAllocateIfNull(char *patientName,
                                         patient *currentPatient);

diseaseStructure* createNewDiseaseStructure(char *diseaseDescription);

void createNewDiseaseListNode(patient *currentPatient,
                              char *diseaseDescription);

void addNewDisease(char *patientName,
                   char *diseaseDescription);

void addDiseaseToListAfterListNode(diseaseListNode *precedingDiseaseListNode,
                                   diseaseStructure *diseaseAdded);

void copyLatestDisease(char *fromPatientName,
                       char *toPatientName);

diseaseListNode* findDiseaseListNode (patient *currentPatient,
                                      int diseaseID);

void changePatientDiseaseDescription(char *patientName,
                                     int diseaseID,
                                     char *diseaseDescription);

void printDiseaseDescription (char *patientName,
                              int diseaseID);

void deletePatientDiseaseList(patient *currentPatient);

void deletePatientData(patient *patientBeingRemoved);

void deletePatientNameDiseaseList(char *patientName);

void freeAllocatedMemory(void);

void performOperation(int operationCode,
                      int *integerArgument,
                      char *stringArgument1,
                      char *stringArgument2);

#endif /* STRUCTURE_H */