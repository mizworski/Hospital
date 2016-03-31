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
    diseaseListNode *diseaseList;
    patient *nextPatient;
    int diseaseCount;
};

static hospitalData hospitalGlobalData;

void initializeHospitalGlobalData(void) {
    // Initialize global structure with dummy ahead list.
    hospitalGlobalData.firstPatient = malloc(sizeof(patient));
    hospitalGlobalData.storedDiseasesCount = 0;
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
    diseaseListNode *diseaseListBeingRemoved = patientBeingRemoved->diseaseList;
    diseaseListNode *temporaryDiseaseList;

    // Frees diseaseStructure from patient's diseaseList one by one.
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
           strcmp(currentPatient->nextPatient->patientName, patientName) < 0) {
        // Lazy evaluation.
        currentPatient = currentPatient->nextPatient;
    }

    return currentPatient;
}

patient* getPatientPointer(char *patientName,
                           patient *currentPatient) {
    // Checks if we are at the end of the list or proceeding patient's
    // patientName is greater (in lexicographical order).
    // If so allocates and initializes newPatient.
    if (currentPatient->nextPatient == NULL || // Lazy evaluation.
            strcmp(currentPatient->nextPatient->patientName, patientName) > 0) {
        patient *newPatient = malloc(sizeof(patient));

        newPatient->patientName = patientName;
        // Initializes dummy ahead diseaseList.
        newPatient->diseaseList = malloc(sizeof(diseaseListNode));
        newPatient->nextPatient = NULL;
        newPatient->diseaseCount = 0;
        newPatient->nextPatient = currentPatient->nextPatient;
        currentPatient->nextPatient = newPatient;
    }

    // Patient proceeding its preceding patient is that patient.
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
                  diseaseName) < 00) { // Lazy evaluation.
        currentDisease = currentDisease->nextDisease;
    }

    return currentDisease;
}

void createDiseaseRegistry(patient* currentPatient,
                           diseaseListNode* precedingDisease,
                           char *diseaseName,
                           char *diseaseDescription) {
    // Allocates memory for diseaseListNode and diseaseStructure.
    diseaseListNode *newDiseaseNode = malloc(sizeof(diseaseListNode));
    diseaseStructure *newDisease = malloc(sizeof(diseaseStructure));

    // Initializes diseaseListNode with arguments passed to the function.
    newDiseaseNode->nextDisease = precedingDisease->nextDisease;
    precedingDisease->nextDisease = newDiseaseNode;
    newDiseaseNode->diseaseReference = newDisease;

    // Initializes diseaseStructure with arguments passed to the function.
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
    // We want to sort our patients by their patientName field in
    // lexicographical, ascending order.

    // Finds patient with patientName field preceding patientName given as
    // argument.
    patient *precedingPatient = findPatientPrecedingGivenName(patientName);

    // Gets pointer to patient with patientName same as given argument
    // (allocates and initializes new structure if patient doesn't exists).
    precedingPatient = getPatientPointer(patientName, precedingPatient);

    // We also want to sort our diseases on diseaseList in lexicographical,
    // ascending order.

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
    printf("IGNORED\n");
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
            printIgnoredUponFailure();// There is no default.
            break;
    }
}
