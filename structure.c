#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct hospitalData hospitalData;
typedef struct patient patient;
typedef struct diseaseObject diseaseReference;
typedef struct diseaseListNode diseaseListNode;

struct hospitalData {
    patient *firstPatient;
//    diseaseListNode *firstDisease;
    int storedDiseasesCount;
};

struct diseaseObject {
    char *diseaseName;
    char *diseaseDescription;
    int referenceCount;
};

struct diseaseListNode {
    diseaseListNode *nextDisease;
    struct diseaseObject *diseaseReference; // Something is wrong with typedef.
};

struct patient {
    char *patientName;
    diseaseListNode *diseaseList;
    patient *nextPatient;
    int diseaseCount;
};

hospitalData hospitalGlobalData;

void initializeHospitalGlobalData(void) {
    // Initialize global structure with dummy ahead list.
    hospitalGlobalData.firstPatient = malloc(sizeof(patient));
//    hospitalGlobalData.firstDisease = malloc(sizeof(diseaseListNode));
    hospitalGlobalData.storedDiseasesCount = 0;
}

void clearAllocatedMemory(void) {

}

patient* findPatientPrecedingGivenName(char *patientName) {
    patient *currentPatient = hospitalGlobalData.firstPatient;

    // Insert patient into descending list sorted by patientName field.

    // Find patient in patientList that's
    // patientName field proceeds argument patientName.
    while (currentPatient->nextPatient != NULL &&
           strcmp(currentPatient->patientName, patientName) > 0) {
        // Lazy evaluation.
        currentPatient = currentPatient->nextPatient;
    }

    return currentPatient;
}

patient* getPatientPointer(char *patientName,
                           patient *currentPatient) {
    if (strcmp(currentPatient->patientName, patientName) < 0) {
        patient *newPatient = malloc(sizeof(patient));

        newPatient->patientName = patientName;
        newPatient->diseaseList = malloc(sizeof(diseaseListNode));
        newPatient->nextPatient = NULL;
        newPatient->diseaseCount = 0;
        newPatient->nextPatient = currentPatient->nextPatient;
        currentPatient->nextPatient = newPatient;
    }

    return currentPatient->nextPatient;
}

diseaseListNode* findDiseasePrecedingGivenDisease(char *diseaseName,
                                                  diseaseListNode
                                                  *diseaseList) {
    diseaseListNode *currentDisease = diseaseList;

    // Finds disease in diseaseList that's
    // diseaseName field proceeds argument diseaseName.
    while (currentDisease->nextDisease != NULL &&
           strcmp(currentDisease->nextDisease->diseaseReference->diseaseName,
                  diseaseName) > 0) { // Lazy evaluation.
        currentDisease = currentDisease->nextDisease;
    }

    return currentDisease;
}

void createDiseaseRegistry(patient* currentPatient,
                           diseaseListNode* precedingDisease,
                           char *diseaseName,
                           char *diseaseDescription) {
    // Allocates memory for diseaseListNode and diseaseReference.
    diseaseListNode *newDiseaseNode = malloc(sizeof(diseaseListNode));
    diseaseReference *newDisease = malloc(sizeof(diseaseReference));

    // Initializes diseaseListNode with arguments passed to the function.
    newDiseaseNode->nextDisease = precedingDisease->nextDisease;
    precedingDisease->nextDisease = newDiseaseNode;
    newDiseaseNode->diseaseReference = newDisease;

    // Initializes diseaseReference with arguments passed to the function.
    newDisease->diseaseName = diseaseName;
    newDisease->diseaseDescription = diseaseDescription;
    newDisease->referenceCount = 1;

    // Updates currentPatient and global hospitalGlobalData structures.
    currentPatient->diseaseCount += 1;
    hospitalGlobalData.storedDiseasesCount += 1;
}

void addNewDisease(char *patientName,
                   char *diseaseName,
                   char *diseaseDescription) {
    // Finds patient with patientName preceding patientName given as argument.
    patient *precedingPatient = findPatientPrecedingGivenName(patientName);

    // Gets pointer to patient with patientName same as given argument
    // (allocates and initializes new structure if patient doesn't exists).
    precedingPatient = getPatientPointer(patientName, precedingPatient);

    // Finds disease with diseaseName preceding diseaseName given as argument.
    diseaseListNode *precedingDisease =
            findDiseasePrecedingGivenDisease(diseaseName,
                                             precedingPatient->diseaseList);

    // Allocates and initializes new structure for disease.
    createDiseaseRegistry(precedingPatient,
                          precedingDisease,
                          diseaseName,
                          diseaseDescription);
}

void copyLatestDisease(char *toPatientName,
                       char *fromPatientName) {
    // I assume that if
}

void changePatientDiseaseDescription(char *patientName,
                                     int diseaseID,
                                     char *diseaseName,
                                     char *diseaseDescription) {

}

void printDiseaseDescription(char *patientName,
                              int diseaseID) {

}

void printIgnoredUponFailure(void) {
    printf("IGNORED");
}

void deletePatientDiseaseData(char *patientName) {

}

void performOperation(int operationCode,
                      int *integerArgument,
                      char **stringArgument1,
                      char **stringArgument2,
                      char **stringArgument3) {
    switch (operationCode) {
        case -1:
        case 0:
            break;
        case 1:
            addNewDisease(*stringArgument1,
                          *stringArgument2,
                          *stringArgument3);
            break;
        case 2:
            copyLatestDisease(*stringArgument1,
                              *stringArgument2);
            break;
        case 3:
            changePatientDiseaseDescription(*stringArgument1,
                                            *integerArgument,
                                            *stringArgument2,
                                            *stringArgument3);
            break;
        case 4:
            printDiseaseDescription(*stringArgument1,
                                    *integerArgument);
            break;
        case 5:
            deletePatientDiseaseData(*stringArgument1);
            break;
        default: // There is no default.
            break;
    }
}

// TRASH

/*

void addNewPatient(char *patientName) {
    patient *newPatient = malloc(sizeof(patient));
    patient *currentPatient = hospitalGlobalData.firstPatient;

    while (currentPatient->nextPatient != NULL &&
            strcmp(currentPatient->patientName, patientName) > 0) {
        currentPatient = currentPatient->nextPatient;
    }

    newPatient->nextPatient = currentPatient->nextPatient;
    currentPatient->nextPatient = newPatient;
}
*/

/*
void addNewDisease(char *patientName,
                   char *diseaseName,
                   char *diseaseDescription) {
    patient *currentPatient = hospitalGlobalData.firstPatient;

    // Insert patient into descending list sorted by patientName field.

    // Find patient in patientList that's
    // patientName field proceeds argument patientName.
    while (currentPatient->nextPatient != NULL &&
           strcmp(currentPatient->patientName, patientName) > 0) {
        currentPatient = currentPatient->nextPatient;
    }

    // Checks whether patient with patientName value exists in hospitalData
    // if not, allocates memory for new patient and initializes it's structure.
    if (strcmp(currentPatient->patientName, patientName) < 0) {
        patient *newPatient = malloc(sizeof(patient));

        newPatient->patientName = patientName;
        newPatient->diseaseList = malloc(sizeof(diseaseListNode));
        newPatient->nextPatient = NULL;
        newPatient->diseaseCount = 0;
        newPatient->nextPatient = currentPatient->nextPatient;
        currentPatient->nextPatient = newPatient;
    }

    currentPatient = currentPatient->nextPatient;

    // Adds new disease to patient diseaseList.

    diseaseListNode *currentDisease = currentPatient->diseaseList;

    // Finds disease in diseaseList that's
    // diseaseName field proceeds argument diseaseName.
    while (currentDisease->nextDisease != NULL &&
           strcmp(currentDisease->nextDisease->diseaseReference->diseaseName,
                  diseaseName) > 0) {
        currentDisease = currentDisease->nextDisease;
    }

    // Allocates memory for diseaseReference.
    diseaseReference *newDisease = malloc(sizeof(diseaseReference));

    // Initializes diseaseReference with arguments passed to the function.
    newDisease->diseaseName = diseaseName;
    newDisease->diseaseDescription = diseaseDescription;
    newDisease->referenceCount = 1;
    // MISSING INSERTION

    // Updates currentPatient and global hospitalGlobalData structures.
    currentPatient->diseaseCount += 1;
    hospitalGlobalData.storedDiseasesCount += 1;
}
*/
