//
// Created by michal on 19.03.16.
//

typedef struct patient patient;

typedef struct diseaseObject diseaseObject;

typedef struct diseaseListNode diseaseListNode;

typedef struct diseaseListNode *diseaseListNodePointer;

struct patientsList {

};

struct diseaseListNode {
    diseaseListNode *nextDisease;
    diseaseObject *disease;
};

struct patient {
    char **patientName;
    diseaseListNode *diseaseList;
    patient *nextPatient;
};

struct diseaseObject {
    char **diseaseName;
    char **diseaseDescription;
    int referenceCount;
};

void addNewPatientToList(char *patientName, char *diseaseName, char
*diseaseDescription) {

}

void copyLatestDisease(char *fromPatientName, char *toPatientName) {

}

