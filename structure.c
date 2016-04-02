#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct hospitalData hospitalData;
typedef struct patient patient;
typedef struct diseaseStructure diseaseStructure;
typedef struct diseaseListNode diseaseListNode;

struct hospitalData {
    patient *firstPatient;
    int storedDiseasesCount;
};

struct diseaseStructure {
    char *diseaseName;
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
    int diseaseCount; // NOT NEEDED
};

static hospitalData hospitalGlobalData;

void initializeHospitalGlobalData(void) {
    // Initialize global structure with dummy ahead list.
    hospitalGlobalData.firstPatient = malloc(sizeof(patient));
    hospitalGlobalData.storedDiseasesCount = 0;
}

void printIgnoredUponFailure(void) {
    printf("IGNORED\n");
}

void decreaseCountAndFreeIfNotReferenced(diseaseStructure *diseaseReference) {
    diseaseReference->referenceCount--;

    // If disease is not being referenced by any patient then it can and have
    // to be freed.
    if(diseaseReference->referenceCount == 0) {
        free(diseaseReference->diseaseName);
        free(diseaseReference->diseaseDescription);
    }
    free(diseaseReference);
}

void clearPatientData(patient *patientBeingRemoved) {
    diseaseListNode *diseaseListBeingRemoved = patientBeingRemoved->diseaseListHead;
    diseaseListNode *temporaryDiseaseList;

    // Frees diseaseStructure from patient's diseaseListHead one by one.
    while (diseaseListBeingRemoved != NULL) {
        temporaryDiseaseList = diseaseListBeingRemoved;
        decreaseCountAndFreeIfNotReferenced(diseaseListBeingRemoved->diseaseReference);
        diseaseListBeingRemoved = diseaseListBeingRemoved->nextDisease;
        free(temporaryDiseaseList);
    }
    free(patientBeingRemoved->patientName);
    free(patientBeingRemoved);
}

void clearAllocatedMemory(void) {
    // Frees list of patients from global structure.
    patient *patientBeingRemoved = hospitalGlobalData.firstPatient;
    patient *temporaryPatient;
    while (patientBeingRemoved != NULL) {
        temporaryPatient = patientBeingRemoved;
        patientBeingRemoved = patientBeingRemoved->nextPatient;
        clearPatientData(temporaryPatient);
    }
}

patient* findPatientPrecedingGivenName(char *patientName) {
    patient *currentPatient = hospitalGlobalData.firstPatient;

    // Find patient
    while (currentPatient->nextPatient != NULL &&
           strcmp(currentPatient->nextPatient->patientName, patientName) != 0) {
        // Lazy evaluation.
        currentPatient = currentPatient->nextPatient;
    }

    return currentPatient;
}

patient* getPatientPointerAllocateIfNull(char *patientName,
                                         patient *currentPatient) {
    // Checks if we are at the end of the list or proceeding patient's
    // patientName is greater (in lexicographical order).
    // If so allocates and initializes newPatient.
    if (currentPatient->nextPatient == NULL || // Lazy evaluation.
            strcmp(currentPatient->nextPatient->patientName, patientName) != 0) {
        patient *newPatient = malloc(sizeof(patient));

        newPatient->patientName = patientName;
        // Initializes dummy ahead diseaseListHead.
        newPatient->diseaseListHead = malloc(sizeof(diseaseListNode));
        newPatient->diseaseListLast = newPatient->diseaseListHead;
        newPatient->nextPatient = NULL;
        newPatient->diseaseCount = 0; // NOT NEEDED
        newPatient->nextPatient = currentPatient->nextPatient;
        currentPatient->nextPatient = newPatient;
    }

    // Patient proceeding its preceding patient is that patient.
    return currentPatient->nextPatient;
}

void createDiseaseRegistry(patient* currentPatient,
                           char *diseaseName,
                           char *diseaseDescription) {
    // Allocates memory for diseaseListNode and diseaseStructure.
    diseaseListNode *newDiseaseNode = malloc(sizeof(diseaseListNode));
    diseaseStructure *newDisease = malloc(sizeof(diseaseStructure));

    // Initializes diseaseListNode with arguments passed to the function.
    newDiseaseNode->nextDisease = currentPatient->diseaseListLast->nextDisease;
    currentPatient->diseaseListLast->nextDisease = newDiseaseNode;
    newDiseaseNode->diseaseReference = newDisease;

    // Initializes diseaseStructure with arguments passed to the function.
    newDisease->diseaseName = diseaseName;
    newDisease->diseaseDescription = diseaseDescription;
    newDisease->referenceCount = 1;

    // Updates currentPatient and global hospitalGlobalData structures.
    currentPatient->diseaseCount++; // NOT NEEDED
    hospitalGlobalData.storedDiseasesCount++;
}

void addNewDisease(char *patientName,
                   char *diseaseName,
                   char *diseaseDescription) {
    patient* currentPatient = NULL;
    // We are inserting patients into our list without any order because it
    // does not change our time complexity.

    // Finds patient with patientName field preceding patientName given as
    // argument. If patient with patientName does not exist in the database
    // then pointer to the last patient on the list is given.
    patient *precedingPatient = findPatientPrecedingGivenName(patientName);

    // Gets pointer to patient with patientName same as given argument
    // (allocates and initializes new structure if patient doesn't exists).
    currentPatient = getPatientPointerAllocateIfNull(patientName,
                                                     precedingPatient);

    // Allocates and initializes new structure for disease and inserts that
    // disease at the end of patient diseaseList.
    createDiseaseRegistry(currentPatient,
                          diseaseName,
                          diseaseDescription);
}

void copyLatestDisease(char *toPatientName,
                       char *fromPatientName) {
    patient *fromPatient = NULL;
//    diseaseStructure *diseaseCopied = NULL;

    fromPatient = findPatientPrecedingGivenName(fromPatientName);
    fromPatient = fromPatient->nextPatient;
    if (fromPatient == NULL ||
            fromPatient->diseaseListHead == fromPatient->diseaseListLast) {
        printIgnoredUponFailure();
        free(fromPatient);
        free(toPatientName);
    } else {

    }
}

void changePatientDiseaseDescription(char *patientName,
                                     int diseaseID,
                                     char *diseaseName,
                                     char *diseaseDescription) {

}

void printDiseaseDescription(char *patientName,
                              int diseaseID) {

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
        case 0:
        default:
            printIgnoredUponFailure();
    }
}

void debugModePrintDescriptions() {
    fprintf(stderr, "DESCRIPTIONS: %d\n", hospitalGlobalData
            .storedDiseasesCount);
}
