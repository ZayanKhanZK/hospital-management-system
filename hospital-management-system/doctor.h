#ifndef DOCTOR_H
#define DOCTOR_H

#include "global_helpers.h"

//Management
void doctorMenu(Doctor doctors[], int* count, int* nextID);
void addDoctor(Doctor doctors[], int* count, int* nextID);
void viewDoctors(Doctor doctors[], int count);
void updateDoctor(Doctor doctors[], int count);
void deleteDoctor(Doctor doctors[], int* count);

//Search
void searchDoctorMenu(Doctor doctors[], int count);
void searchDoctorByID(Doctor doctors[], int count);
void searchDoctorByName(Doctor doctors[], int count);
void searchDoctorBySpecialization(Doctor doctors[], int count);
void displayDoctorSummary(Doctor doctors[], int count, int nextID);

//Save and Load
void saveDoctorsToFile(Doctor doctors[], int count);
void loadDoctorsFromFile(Doctor doctors[], int* count, int* nextID);

#endif













