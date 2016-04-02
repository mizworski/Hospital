#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCES_MESSAGE          "OK\n"
#define IGNORE_MESSAGE          "IGNORED\n"
#define DESCRIPTION_MESSAGE     "DESCRIPTIONS: %d\n"

// TODO SET NULL AFTER FREEING

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
    printf(IGNORE_MESSAGE);
}

void printOKUponSucces(void) {
    printf(SUCCES_MESSAGE);
}

void decreaseCountAndFreeIfNotReferred(diseaseStructure *diseaseReference) {
    diseaseReference->referenceCount--;

    // If disease is not being referenced by any patient then it can and have
    // to be freed.
    if (diseaseReference->referenceCount == 0) {
        free(diseaseReference->diseaseName);
        free(diseaseReference->diseaseDescription);
    }
    free(diseaseReference);
}

void deletePatientDiseaseList(patient *currentPatient) {
    diseaseListNode *diseaseListBeingRemoved =
            currentPatient->diseaseListHead->nextDisease;
    diseaseListNode *temporaryDiseaseList;

    // Frees diseaseStructure from patient's diseaseListHead one by one.
    while (diseaseListBeingRemoved != NULL) {
        temporaryDiseaseList = diseaseListBeingRemoved;
        decreaseCountAndFreeIfNotReferred(
                diseaseListBeingRemoved->diseaseReference);
        diseaseListBeingRemoved = diseaseListBeingRemoved->nextDisease;
        free(temporaryDiseaseList);
    }

    currentPatient->diseaseListLast = currentPatient->diseaseListHead;
    currentPatient->diseaseListHead = NULL;
}

void deletePatientData(patient *patientBeingRemoved) {
    deletePatientDiseaseList(patientBeingRemoved);
    // Frees dummy from head of the list.
    free(patientBeingRemoved->diseaseListHead);
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
        deletePatientData(temporaryPatient);
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
        newPatient->diseaseListLast->nextDisease = NULL;
        newPatient->nextPatient = NULL;
        newPatient->diseaseCount = 0; // NOT NEEDED
        newPatient->nextPatient = currentPatient->nextPatient;
        currentPatient->nextPatient = newPatient;
    }

    // Patient proceeding its preceding patient is that patient.
    return currentPatient->nextPatient;
}

diseaseStructure* createNewDiseaseStructure(char *diseaseName,
                                            char *diseaseDescription) {
    diseaseStructure *newDisease = malloc(sizeof(diseaseStructure));

    newDisease->diseaseName = diseaseName;
    newDisease->diseaseDescription = diseaseDescription;
    newDisease->referenceCount = 1;

    hospitalGlobalData.storedDiseasesCount++;

    return newDisease;
}

void createNewDiseaseListNode(patient *currentPatient,
                              char *diseaseName,
                              char *diseaseDescription) {
    // Allocates memory for diseaseListNode and diseaseStructure.
    diseaseListNode *newDiseaseNode = malloc(sizeof(diseaseListNode));
    diseaseStructure *newDisease = NULL;

    // Initializes diseaseStructure with arguments passed to the function.
    newDisease = createNewDiseaseStructure(diseaseName,
                                           diseaseDescription);

    // Initializes diseaseListNode with arguments passed to the function.
    newDiseaseNode->nextDisease = currentPatient->diseaseListLast->nextDisease;
    currentPatient->diseaseListLast->nextDisease = newDiseaseNode;
    currentPatient->diseaseListLast = newDiseaseNode;
    newDiseaseNode->diseaseReference = newDisease;



    // Updates currentPatient and global hospitalGlobalData structures.
    currentPatient->diseaseCount++; // NOT NEEDED
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
    createNewDiseaseListNode(currentPatient,
                             diseaseName,
                             diseaseDescription);
    printOKUponSucces();
}

/*
void addDiseaseToPatientList(patient *currentPatient,
                             diseaseStructure *diseaseAdded) {
    diseaseListNode *newDiseaseListNode = malloc(sizeof(diseaseListNode));

    newDiseaseListNode->nextDisease =
            currentPatient->diseaseListLast->nextDisease; // == NULL
    currentPatient->diseaseListLast->nextDisease = newDiseaseListNode;
    currentPatient->diseaseListLast = newDiseaseListNode;
    newDiseaseListNode->diseaseReference = diseaseAdded;
    diseaseAdded->referenceCount++;
}
*/

// Adds disease that currently exists.
void addDiseaseToListAfterListNode(diseaseListNode *precedingDiseaseListNode,
                                   diseaseStructure *diseaseAdded) {
    diseaseListNode *newDiseaseListNode = malloc(sizeof(diseaseListNode));

    newDiseaseListNode->nextDisease = precedingDiseaseListNode->nextDisease;
    precedingDiseaseListNode->nextDisease = newDiseaseListNode;
    newDiseaseListNode->diseaseReference = diseaseAdded;
    diseaseAdded->referenceCount++;
}

void copyLatestDisease(char *toPatientName,
                       char *fromPatientName) {
    patient *fromPatient = NULL;
    patient *toPatient = NULL;

    patient *patientPrecedingFromPatient = NULL;
    patient *patientPrecedingToPatient = NULL;

    diseaseStructure *diseaseCopied = NULL;

    patientPrecedingFromPatient = findPatientPrecedingGivenName(fromPatientName);
    fromPatient = patientPrecedingFromPatient->nextPatient;

    if (fromPatient == NULL || // Lazy evaluation.
            fromPatient->diseaseListHead == fromPatient->diseaseListLast) {
        // If diseaseListHead equals diseaseListLast then our list of
        // diseases is empty (we keep dummy ahead that list).
        printIgnoredUponFailure();
        free(toPatientName);
    } else {
        patientPrecedingToPatient = findPatientPrecedingGivenName(toPatientName);
        toPatient = getPatientPointerAllocateIfNull(toPatientName,
                                                    patientPrecedingToPatient);
        diseaseCopied = fromPatient->diseaseListLast->diseaseReference;

        addDiseaseToListAfterListNode(toPatient->diseaseListLast,
                                      diseaseCopied);
        toPatient->diseaseListLast = toPatient->diseaseListLast->nextDisease;
        printOKUponSucces();
    }

    free(fromPatient);
}

// Returns NULL when diseaseListNode was not found.
diseaseListNode* findDiseaseListNode (patient *currentPatient,
                                      int diseaseID) {
    diseaseListNode* diseaseListNodeToReturn = NULL;
    diseaseListNode* currentDiseaseListNode = currentPatient->diseaseListHead;

    int diseaseCount;

    for (diseaseCount = 0; diseaseCount < diseaseID &&
            currentDiseaseListNode != NULL; diseaseCount++) {
        currentDiseaseListNode = currentDiseaseListNode->nextDisease;
    }

    if (diseaseCount == diseaseID) {
        diseaseListNodeToReturn = currentDiseaseListNode;
    }

    return diseaseListNodeToReturn;
}

void changePatientDiseaseDescription(char *patientName,
                                     int diseaseID,
                                     char *diseaseName,
                                     char *diseaseDescription) {
    patient *currentPatient = NULL;
    patient *patientPrecedingCurrentPatient = NULL;

    diseaseListNode *diseaseListNodeToModify = NULL;
    diseaseStructure *diseaseToModify = NULL;
    diseaseStructure *newDisease = NULL;


    patientPrecedingCurrentPatient = findPatientPrecedingGivenName(patientName);
    currentPatient = patientPrecedingCurrentPatient->nextPatient;

    if (currentPatient == NULL || diseaseID < 1) {
        // Patient was not found in database or
        // tried referring to disease with wrong ID.
        printIgnoredUponFailure();
        free(diseaseName);
        free(diseaseDescription);
    } else {
        diseaseListNodeToModify = findDiseaseListNode(currentPatient,
                                                      diseaseID);
        diseaseToModify = diseaseListNodeToModify->diseaseReference;
        decreaseCountAndFreeIfNotReferred(diseaseToModify);
        newDisease = createNewDiseaseStructure(diseaseName,
                                               diseaseDescription);
        diseaseListNodeToModify->diseaseReference = newDisease;
        printOKUponSucces();
    }

    free(patientName);
}

void printDescription (diseaseStructure *diseaseToPrint) {
    printf("%s", diseaseToPrint->diseaseDescription);
}

void printDiseaseDescription(char *patientName,
                              int diseaseID) {
    patient *currentPatient = NULL;
    patient *patientPrecedingCurrentPatient = NULL;

    diseaseListNode *diseaseNodeToPrint = NULL;

    patientPrecedingCurrentPatient = findPatientPrecedingGivenName(patientName);
    currentPatient = patientPrecedingCurrentPatient->nextPatient;

    if (currentPatient == NULL || diseaseID < 1) {
        // Patient was not found in database or
        // tried referring to disease with wrong ID.
        printIgnoredUponFailure();
    } else {
        diseaseNodeToPrint = findDiseaseListNode(currentPatient,
                                                 diseaseID);
        if (diseaseNodeToPrint == NULL) {
            printIgnoredUponFailure();
        } else {
            printDescription(diseaseNodeToPrint->diseaseReference);
        }
    }

    free(patientName);
}

void deletePatientDiseaseData(char *patientName) {
    patient *currentPatient = NULL;
    patient *patientPrecedingCurrentPatient = NULL;

    patientPrecedingCurrentPatient = findPatientPrecedingGivenName(patientName);
    currentPatient = patientPrecedingCurrentPatient->nextPatient;

    if (currentPatient == NULL) {
        // Patient was not found in database.
        printIgnoredUponFailure();
    } else {
        deletePatientDiseaseList(currentPatient);
        printOKUponSucces();
    }

    free(patientName);
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
    fprintf(stderr,
            DESCRIPTION_MESSAGE,
            hospitalGlobalData.storedDiseasesCount);
}
