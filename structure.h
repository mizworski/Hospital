typedef struct patient patient;
typedef struct diseaseStructure diseaseStructure;
typedef struct diseaseListNode diseaseListNode;

struct diseaseStructure {
    char *diseaseName;
    char *diseaseDescription;
    int referenceCount;
};

struct diseaseListNode {
    diseaseListNode *nextDisease;
    diseaseStructure *diseaseReference; // Something is wrong with typedef.
};

struct patient {
    char *patientName;
    diseaseListNode *diseaseListHead;
    patient *nextPatient;
    int diseaseCount;
};

void initializeHospitalGlobalData(void);

void printIgnoredUponFailure(void);

void decreaseCountAndFreeIfNotReferred(diseaseStructure *diseaseReference);

void deletePatientData(patient *patientBeingRemoved);

void clearAllocatedMemory(void);

patient* findPatientPrecedingGivenName(char *patientName);

patient* getPatientPointerAllocateIfNull(char *patientName,
                                         patient *currentPatient);

void createNewDiseaseListNode(patient *currentPatient,
                              char *diseaseName,
                              char *diseaseDescription);

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

void deletePatientDiseaseData (char *patientName);

void performOperation(int operationCode,
                      int *integerArgument,
                      char **stringArgument1,
                      char **stringArgument2,
                      char **stringArgument3);

void debugModePrintDescriptions();

