#include <stdio.h>
#include <string.h>

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
    hospitalGlobalData.firstPatient = NULL;
    hospitalGlobalData.firstDisease = NULL;
}

void addNewPatient(char *patientName) {
    patient nextPatient = hospitalGlobalData.firstPatient;

    while (nextPatient != NULL &&
            strcmp(nextPatient.patientName, patientName) < 0);
}

void addNewDisease(char *patientName,
                   char *diseaseName,
                   char *diseaseDescription) {

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