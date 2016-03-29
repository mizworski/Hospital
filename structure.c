typedef struct patient patient;
typedef struct diseaseObject diseaseObject;
typedef struct diseaseListNode diseaseListNode;

struct patientsList {

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

void addNewPatientToList(char *patientName,
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