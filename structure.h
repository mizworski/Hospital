#ifndef IPP_1_STRUCTURE_H
#define IPP_1_STRUCTURE_H

#endif //IPP_1_STRUCTURE_H

typedef struct patient patient;
typedef struct diseaseObject diseaseReference;
typedef struct diseaseListNode diseaseListNode;

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

void initializeHospitalGlobalData(void);

void clearAllocatedMemory(void);

patient* findPatientPrecedingGivenName(char *patientName);

patient* getPatientPointer(char *patientName,
                           patient *currentPatient);

diseaseListNode* findDiseasePrecedingGivenDisease(char *diseaseName,
                                                  diseaseListNode
                                                  *diseaseList);

void createDiseaseRegistry(patient* currentPatient,
                           diseaseListNode* precedingDisease,
                           char *diseaseName,
                           char *diseaseDescription);

void addNewPatient(char *patientName);

void addNewDisease(char *patientName,
                   char *diseaseName,
                   char *diseaseDescription);

void copyLatestDisease(char *fromPatientName,
                       char *toPatientName);

void changePatientDiseaseDescription(char *patientName,
                                     int diseaseID,
                                     char *diseaseName,
                                     char *diseaseDescription);

void printDiseaseDescription (char *patientName,
                              int diseaseID);

void printIgnoredUponFailure(void);

void deletePatientDiseaseData (char *patientName);

void performOperation(int operationCode,
                      int *integerArgument,
                      char **stringArgument1,
                      char **stringArgument2,
                      char **stringArgument3);

