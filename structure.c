#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct hospitalData hospitalData;
typedef struct patient patient;
typedef struct diseaseObject diseaseObject;
typedef struct diseaseListNode diseaseListNode;

struct hospitalData {
    patient *firstPatient;
    diseaseListNode *firstDisease;
};

struct diseaseListNode {
    diseaseListNode *nextDisease;
    diseaseObject *disease;
};

struct patient {
    char *patientName;
    diseaseListNode *diseaseList;
    patient *nextPatient;
    int diseaseCount;
};

struct diseaseObject {
    char *diseaseName;
    char *diseaseDescription;
    int referenceCount;
};

hospitalData hospitalGlobalData;

void initializeHospitalGlobalData(void) {
    // Initialize global structure with dummy ahead list.
    hospitalGlobalData.firstPatient = malloc(sizeof(patient));
    hospitalGlobalData.firstDisease = malloc(sizeof(diseaseListNode));
}

void clearAllocatedMemory(void) {

}

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

void addNewDisease(char *patientName,
                   char *diseaseName,
                   char *diseaseDescription) {
    patient *currentPatient = hospitalGlobalData.firstPatient;

    // Insert patient into descending list sorted by patientName field.
    while (currentPatient->nextPatient != NULL &&
           strcmp(currentPatient->patientName, patientName) > 0) {
        currentPatient = currentPatient->nextPatient;
    }

    // Checks whether patient with patientName value exists in hospitalData
    // if not, allocates memory for new patient and initializes its structure.
    if (strcmp(currentPatient->patientName, patientName) < 0) {
        patient *newPatient = malloc(sizeof(patient));

        newPatient->patientName = patientName;
        newPatient->diseaseList = malloc(sizeof(diseaseListNode));
        newPatient->nextPatient = NULL;
        newPatient->diseaseCount = 0;
        newPatient->nextPatient = currentPatient->nextPatient;
        currentPatient->nextPatient = newPatient;
    }

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