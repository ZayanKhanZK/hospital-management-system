#define _CRT_SECURE_NO_WARNINGS
#include "patient.h"
#include "doctor.h"

int main() {
    //Patient
    Patient patients[MAX_RECORDS];
    int patient_count = 0;
    int patient_nextID = 1;

    //Doctor
    Doctor doctors[MAX_RECORDS];
    int doctor_count = 0;
    int doctor_nextID = 1;

    int choice;

    //Active
    for (int i = 0; i < MAX_RECORDS; i++) {
        patients[i].active = 0;
        doctors[i].active = 0;
    }

    loadPatientsFromFile(patients, &patient_count, &patient_nextID);
    loadDoctorsFromFile(doctors, &doctor_count, &doctor_nextID);
    clearScreen();
    printf("Welcome to the Hospital Management System!\n");
    printf("Data loaded successfully.\n");

    while (1) {
        printf("\n=== Main Application Menu ===\n");
        printf("1. Manage Patient Records\n");
        printf("2. Manage Doctor Records\n");
        printf("3. Save All Data and Exit\n");
        printf("-----------------------------\n");
        printf("Enter your choice (1-3): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_line();
            continue;
        }
        clear_input_line();

        clearScreen();

        switch (choice) {
        case 1:
            patientMenu(patients, &patient_count, &patient_nextID);
            break;
        case 2:
            doctorMenu(doctors, &doctor_count, &doctor_nextID);
            break;
        case 3:
            savePatientsToFile(patients, patient_count);
            saveDoctorsToFile(doctors, doctor_count);
            printf("Exiting. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Please choose 1-3.\n");
        }

        if (choice != 3) {
            printf("\nPress Enter to return to the Main Menu...");
            clear_input_line();
            clearScreen();
        }
    }
    return 0;
}