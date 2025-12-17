#ifndef PATIENT_H
#define PATIENT_H
 
#include "global_helpers.h"

//Patient
void patientMenu(Patient patients[], int* count, int* nextID);
void addPatient(Patient patients[], int* count, int* nextID);
void viewPatients(Patient patients[], int count);
void updatePatient(Patient patients[], int count);
void deletePatient(Patient patients[], int* count);
void printPatientDetails(const Patient* p);

//Search
void searchPatientMenu(Patient patients[], int count);
void searchByID(Patient patients[], int count);
void searchByName(Patient patients[], int count);
void searchByAgeRange(Patient patients[], int count);
void searchByRoom(Patient patients[], int count);
void searchByDisease(Patient patients[], int count);
void displayPatientSummary(Patient patients[], int count, int nextID);

//Save and Load
void savePatientsToFile(Patient patients[], int count);
void loadPatientsFromFile(Patient patients[], int* count, int* nextID);

#endif