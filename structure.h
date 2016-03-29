#ifndef IPP_1_STRUCTURE_H
#define IPP_1_STRUCTURE_H

#endif //IPP_1_STRUCTURE_H

void initializeHospitalGlobalData(void);

void addNewPatient(char *patientName);

void addNewDisease(char *patientName,
                   char *diseaseName,
                   char *diseaseDescription) {

}

void copyLatestDisease(char *fromPatientName,
                       char *toPatientName);

void changePatientDiseaseDescription(char *patientName,
                                     int diseaseID,
                                     char *diseaseName,
                                     char *diseaseDescription);

void printDiseaseDescription (char *patientName,
                              int diseaseID);

void deletePatientDiseaseData (char *patientName);