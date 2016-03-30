#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct hospitalData hospitalData;
typedef struct patient patient;
typedef struct diseaseReference diseaseReference;
typedef struct diseaseListNode diseaseListNode;

struct hospitalData {
    patient *firstPatient;
//    diseaseListNode *firstDisease;
    int storedDiseasesCount;
};

struct diseaseListNode {
    diseaseListNode *nextDisease;
    diseaseReference *diseaseReference;
};

struct patient {
    char *patientName;
    diseaseListNode *diseaseList;
    patient *nextPatient;
    int diseaseCount;
};

struct diseaseReference {
    char *diseaseName;
    char *diseaseDescription;
    int referenceCount;
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

    // Updates currentPatient and global hospitalGlobalData structures.
    currentPatient->diseaseCount += 1;
    hospitalGlobalData.storedDiseasesCount += 1;
}

void copyLatestDisease(char *fromPatientName,
                       char *toPatientName) {

}

void changePatientDiseaseDescription(char *patientName,
                                     int diseaseID,
                                     char *diseaseName,
                                     char *diseaseDescription) {

}

void printDiseaseDescription (char *patientName,
                              int diseaseID) {

}

void deletePatientDiseaseData (char *patientName) {

}