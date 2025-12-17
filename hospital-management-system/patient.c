#define _CRT_SECURE_NO_WARNINGS
#include "patient.h"


//Check if record is here
static int findPatientIndexByID(Patient patients[], int count, int id) {
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (patients[i].active && patients[i].id == id) return i;
    }
    return -1;
}

//Print for new patient
void printPatientDetails(const Patient* p) {
    printf("----------------------------------------\n");
    printf("  ID: %d\n", p->id);
    printf("  Name: %s\n", p->name);
    printf("  Age: %d | Gender: %s\n", p->age, getGenderString(p->genderCode));
    printf("  Disease/Complaint: %s\n", p->disease);
    printf("  Room Number: %d (%s)\n", p->room, getRoomTypeString(p->roomType));
    printf("----------------------------------------\n");
}

//Print for main menu
void patientMenu(Patient patients[], int* count, int* nextID) {
    int choice;
    while (1) {
        printf("\n=== Patient Management Menu ===\n");
        printf("1. Add new patient record\n");
        printf("2. View all patient records (Summary)\n");
        printf("3. Search/Filter patients\n");
        printf("4. Update patient record\n");
        printf("5. Discharge (Delete) patient record\n");
        printf("6. Database Summary\n");
        printf("7. Back to Main Application Menu\n");
        printf("------------------------------------\n");
        printf("Enter your choice (1-7): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_line();
            continue;
        }
        clear_input_line();
        clearScreen();

        switch (choice) {
        case 1: addPatient(patients, count, nextID); break;
        case 2: viewPatients(patients, *count); break;
        case 3: searchPatientMenu(patients, *count); break;
        case 4: updatePatient(patients, *count); break;
        case 5: deletePatient(patients, count); break;
        case 6: displayPatientSummary(patients, *count, *nextID); break;
        case 7: return;
        default: printf("Invalid choice. Please choose 1-7.\n");
        }
        if (choice != 7) {
            printf("\nPress Enter to return to the patient menu...");
            clear_input_line();
            clearScreen();
        }
    }
}

//Add patient
void addPatient(Patient patients[], int* count, int* nextID) {
    if (*count >= MAX_RECORDS) {
        printf("Patient database full (max %d).\n", MAX_RECORDS);
        return;
    }

    int index = -1;
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (!patients[i].active) { index = i; break; }
    }

    if (index == -1) {
        printf("Error: Database count is wrong. No free slot found.\n");
        return;
    }
    Patient p;
    p.id = (*nextID)++;
    p.active = 1;
    while (1) {
        printf("Enter patient name: ");
        read_string(p.name, STRLEN);
        if (strlen(p.name) == 0) {
            printf("Name cannot be blank. Please try again.\n");
        }
        else {
            break;
        }
    }

    printf("Enter age: ");
    while (scanf("%d", &p.age) != 1 || p.age < 0 || p.age > 120) {
        printf("Invalid input. Enter an age between 0 and 120: "); clear_input_line();
    }
    clear_input_line();

    printf("Enter gender (1:Male, 2:Female, 3:Rather not say): ");
    while (scanf("%d", &p.genderCode) != 1 || p.genderCode < 1 || p.genderCode > 3) {
        printf("Invalid input. Enter 1, 2, or 3: "); clear_input_line();
    }
    clear_input_line();

    while (1) {
        printf("Enter disease/complaint: ");
        read_string(p.disease, STRLEN);
        if (strlen(p.disease) == 0) {
            printf("Disease/complaint cannot be blank. Please try again.\n");
        }
        else {
            break;
        }
    }

    int roomOK = 0;
    int desiredRoom;
    int desiredType;
    //Private room = 1 patient , Public room = 4 patient
    printf("Enter room type (1:Private, 2:Public): ");
    while (scanf("%d", &desiredType) != 1 || (desiredType != 1 && desiredType != 2)) {
        printf("Invalid input. Enter 1 or 2: "); clear_input_line();
    }
    clear_input_line();
    int maxOccupancy = (desiredType == 1) ? 1 : 4;

    while (!roomOK) {
        printf("Enter room number for %s room: ", getRoomTypeString(desiredType));
        if (scanf("%d", &desiredRoom) != 1 || desiredRoom <= 0) {
            printf("Invalid room number. Enter a positive number: ");
            clear_input_line();
            continue;
        }
        clear_input_line();

        int existingRoomType = 0;
        int currentOccupancy = 0;
        for (int i = 0; i < MAX_RECORDS; i++) {
            if (patients[i].active && patients[i].room == desiredRoom) {
                currentOccupancy++;
                existingRoomType = patients[i].roomType;
            }
        }

        if (existingRoomType == 0) {
            printf("Room %d assigned as %s. (Current: 0/%d)\n",
                desiredRoom, getRoomTypeString(desiredType), maxOccupancy);
            p.room = desiredRoom;
            p.roomType = desiredType;
            roomOK = 1;
        }
        else if (existingRoomType != desiredType) {
            printf("Error: Room %d is already assigned as a %s room.\n",
                desiredRoom, getRoomTypeString(existingRoomType));
        }
        else {
            if (currentOccupancy >= maxOccupancy) {
                printf("Error: Room %d (%s) is full. (Current: %d/%d)\n",
                    desiredRoom, getRoomTypeString(desiredType), currentOccupancy, maxOccupancy);
            }
            else {
                printf("Room %d (%s) is available. (Current: %d/%d)\n",
                    desiredRoom, getRoomTypeString(desiredType), currentOccupancy, maxOccupancy);
                p.room = desiredRoom;
                p.roomType = desiredType;
                roomOK = 1;
            }
        }
    }

    patients[index] = p;
    (*count)++;

    printf("Patient added successfully! Assigned ID: %d\n", p.id);
}

//Patient records
void viewPatients(Patient patients[], int count) {
    printf("\n--- Patient Records (%d) ---\n", count);
    if (count == 0) {
        printf("No active patient records to show.\n");
        return;
    }

    printf("ID   | Name                 | Age | Gender      | Disease              | Room | Type\n");
    printf("-----|----------------------|-----|-------------|----------------------|------|---------\n");
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (patients[i].active) {
            printf("%-4d | %-20s | %-3d | %-11s | %-20s | %-4d | %-7s\n",
                patients[i].id, patients[i].name, patients[i].age,
                getGenderString(patients[i].genderCode),
                patients[i].disease, patients[i].room, getRoomTypeString(patients[i].roomType));
        }
    }
}

//Search
void searchPatientMenu(Patient patients[], int count) {
    int choice;

    while (1) {
        printf("\n=== Patient Search & Filter ===\n");
        printf("1. Search by ID\n");
        printf("2. Search by Name (partial match)\n");
        printf("3. Search by Disease/Complaint\n");
        printf("4. Search by Room Number\n");
        printf("5. Search by Age Range\n");
        printf("6. Back to Patient Menu\n");
        printf("-------------------------------\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) { clear_input_line(); printf("Invalid input. Please enter a number.\n"); continue; }
        clear_input_line();
        clearScreen();

        switch (choice) {
        case 1: searchByID(patients, count); break;
        case 2: searchByName(patients, count); break;
        case 3: searchByDisease(patients, count); break;
        case 4: searchByRoom(patients, count); break;
        case 5: searchByAgeRange(patients, count); break;
        case 6: return;
        default: printf("Invalid choice. Please choose 1-6.\n");
        }

        if (choice != 6) {
            printf("\nPress Enter to return to the search menu...");
            clear_input_line();
            clearScreen();
        }
    }
}

void searchByID(Patient patients[], int count) {
    int id;
    printf("Enter patient ID to search: ");
    if (scanf("%d", &id) != 1) { clear_input_line(); printf("Invalid input.\n"); return; }
    clear_input_line();

    int idx = findPatientIndexByID(patients, count, id);
    if (idx == -1) { printf("Patient with ID %d not found.\n", id); }
    else {
        printf("\n--- Detailed Search Result ---\n");
        printPatientDetails(&patients[idx]);
    }
}

void searchByName(Patient patients[], int count) {
    char query[STRLEN];
    printf("Enter name (or part of name) to search: "); read_string(query, STRLEN);
    if (strlen(query) == 0) return;

    char qlow[STRLEN]; toLowerStr(query, qlow);

    int found = 0;
    printf("\n--- Search Results for Name containing '%s' ---\n", query);
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (patients[i].active) {
            char nameLow[STRLEN];
            toLowerStr(patients[i].name, nameLow);
            if (strstr(nameLow, qlow) != NULL) {
                printPatientDetails(&patients[i]); found = 1;
            }
        }
    }
    if (!found) printf("No patients matched the name '%s'.\n", query);
}

void searchByAgeRange(Patient patients[], int count) {
    int minAge, maxAge;
    printf("Enter minimum age: ");
    if (scanf("%d", &minAge) != 1 || minAge < 0) { clear_input_line(); printf("Invalid minimum age.\n"); return; }
    printf("Enter maximum age: ");
    if (scanf("%d", &maxAge) != 1 || maxAge > 120 || maxAge < minAge) { clear_input_line(); printf("Invalid maximum age or range.\n"); return; }
    clear_input_line();

    int found = 0;
    printf("\n--- Patients Aged %d to %d ---\n", minAge, maxAge);
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (patients[i].active && patients[i].age >= minAge && patients[i].age <= maxAge) {
            printPatientDetails(&patients[i]); found = 1;
        }
    }
    if (!found) printf("No patients found in the age range %d-%d.\n", minAge, maxAge);
}

void searchByRoom(Patient patients[], int count) {
    int room;
    printf("Enter room number to search: ");
    if (scanf("%d", &room) != 1 || room <= 0) { clear_input_line(); printf("Invalid room number.\n"); return; }
    clear_input_line();

    int found = 0;
    printf("\n--- Patients in Room %d ---\n", room);
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (patients[i].active && patients[i].room == room) {
            printPatientDetails(&patients[i]); found = 1;
        }
    }
    if (!found) printf("No active patients found in room %d.\n", room);
}

void searchByDisease(Patient patients[], int count) {
    char query[STRLEN];
    printf("Enter disease (or part of disease) to search: "); read_string(query, STRLEN);
    if (strlen(query) == 0) return;

    char qlow[STRLEN]; toLowerStr(query, qlow);

    int found = 0;
    printf("\n--- Search Results for Disease containing '%s' ---\n", query);
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (patients[i].active) {
            char diseaseLow[STRLEN];
            toLowerStr(patients[i].disease, diseaseLow);
            if (strstr(diseaseLow, qlow) != NULL) {
                printPatientDetails(&patients[i]); found = 1;
            }
        }
    }
    if (!found) printf("No patients matched the disease '%s'.\n", query);
}

void updatePatient(Patient patients[], int count) {
    int id;
    printf("Enter patient ID to update: ");
    if (scanf("%d", &id) != 1) { clear_input_line(); printf("Invalid input.\n"); return; }
    clear_input_line();

    int idx = findPatientIndexByID(patients, count, id);
    if (idx == -1) { printf("Patient with ID %d not found.\n", id); return; }

    Patient* p = &patients[idx];
    printf("Updating patient (ID %d). Enter 0/Leave blank to keep current value.\n", p->id);

    char buf[STRLEN];
    int newNum;

    printf("Current name: %s\nNew name: ", p->name); read_string(buf, STRLEN);
    if (strlen(buf) > 0) strncpy(p->name, buf, STRLEN - 1);

    printf("Current age: %d\nNew age (0-120, 0 to keep): ", p->age);
    if (scanf("%d", &newNum) == 1) {
        if (newNum > 0 && newNum <= 120) p->age = newNum;
    }
    clear_input_line();

    printf("Current gender: %s\nNew gender (1:Male, 2:Female, 3:Unspecified, 0 to keep): ", getGenderString(p->genderCode));
    if (scanf("%d", &newNum) == 1) {
        if (newNum >= 1 && newNum <= 3) p->genderCode = newNum;
    }
    clear_input_line();

    printf("Current disease: %s\nNew disease: ", p->disease); read_string(buf, STRLEN);
    if (strlen(buf) > 0) strncpy(p->disease, buf, STRLEN - 1);

    //New room
    char changeRoom[4];
    printf("Current room: %d (%s)\n", p->room, getRoomTypeString(p->roomType));
    printf("Do you want to change the room assignment? (yes/no): ");
    read_string(changeRoom, 4);

    if (strcmp("yes", changeRoom) == 0 || strcmp("y", changeRoom) == 0) {
        int roomOK = 0;
        int desiredRoom;
        int desiredType;

        printf("Enter new room type (1:Private, 2:Public): ");
        while (scanf("%d", &desiredType) != 1 || (desiredType != 1 && desiredType != 2)) {
            printf("Invalid input. Enter 1 or 2: "); clear_input_line();
        }
        clear_input_line();
        int maxOccupancy = (desiredType == 1) ? 1 : 4;

        while (!roomOK) {
            printf("Enter new room number for %s room: ", getRoomTypeString(desiredType));
            if (scanf("%d", &desiredRoom) != 1 || desiredRoom <= 0) {
                printf("Invalid room number. Enter a positive integer: ");
                clear_input_line();
                continue;
            }
            clear_input_line();

            int existingRoomType = 0;
            int currentOccupancy = 0;
            for (int i = 0; i < MAX_RECORDS; i++) {
                if (patients[i].active && patients[i].id != p->id && patients[i].room == desiredRoom) {
                    currentOccupancy++;
                    existingRoomType = patients[i].roomType;
                }
            }

            if (existingRoomType == 0) {
                printf("Room %d assigned as %s. (Current: 0/%d)\n",
                    desiredRoom, getRoomTypeString(desiredType), maxOccupancy);
                p->room = desiredRoom;
                p->roomType = desiredType;
                roomOK = 1;
            }
            else if (existingRoomType != desiredType) {
                printf("Error: Room %d is already assigned as a %s room.\n",
                    desiredRoom, getRoomTypeString(existingRoomType));
            }
            else {
                if (currentOccupancy >= maxOccupancy) {
                    printf("Error: Room %d (%s) is full. (Current: %d/%d)\n",
                        desiredRoom, getRoomTypeString(desiredType), currentOccupancy, maxOccupancy);
                }
                else {
                    printf("Room %d (%s) is available. (Current: %d/%d)\n",
                        desiredRoom, getRoomTypeString(desiredType), currentOccupancy, maxOccupancy);
                    p->room = desiredRoom;
                    p->roomType = desiredType;
                    roomOK = 1;
                }
            }
        }
    }
    printf("Patient updated successfully.\n");
}

//Delete patient
void deletePatient(Patient patients[], int* count) {
    int id;
    char confirm[4];

    printf("Enter patient ID to DELETE/DISCHARGE: ");
    if (scanf("%d", &id) != 1) { clear_input_line(); printf("Invalid input.\n"); return; }
    clear_input_line();

    int idx = findPatientIndexByID(patients, *count, id);
    if (idx == -1) { printf("Patient with ID %d not found.\n", id); return; }

    printf("\nWARNING: You are about to discharge/delete the record for:\n");
    printPatientDetails(&patients[idx]);
    printf("Are you sure you want to proceed? (yes/no): "); read_string(confirm, 4);

    if (strcmp("yes", confirm) == 0 || strcmp("YES", confirm) == 0 || strcmp("y", confirm) == 0) {
        patients[idx].active = 0; // Soft delete
        (*count)--;
        printf("Patient with ID %d successfully discharged (record removed).\n", id);
    }
    else {
        printf("Deletion cancelled. Patient record remains active.\n");
    }
}

//Summary
void displayPatientSummary(Patient patients[], int count, int nextID) {
    printf("\n=== Patient Database Summary ===\n");
    printf("Total Active Patients: %d / %d (Max Capacity)\n", count, MAX_RECORDS);
    printf("Next Assigned Patient ID: %d\n", nextID);
    printf("--------------------------\n");
}


//Save
void savePatientsToFile(Patient patients[], int count) {
    FILE* file = fopen(PATIENT_FILENAME, "wb");
    if (file == NULL) {
        printf("Error: Could not save data to %s.\n", PATIENT_FILENAME);
        return;
    }

    int active_count = 0;
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (patients[i].active) {
            fwrite(&patients[i], sizeof(Patient), 1, file);
            active_count++;
        }
    }

    fclose(file);
    printf("Successfully saved %d patient records to %s.\n", active_count, PATIENT_FILENAME);
}

//Load
void loadPatientsFromFile(Patient patients[], int* count, int* nextID) {
    FILE* file = fopen(PATIENT_FILENAME, "rb");
    if (file == NULL) {
        printf("No existing patient data found (%s). Starting new database.\n", PATIENT_FILENAME);
        return;
    }

    *count = 0;
    int maxID = 0;
    Patient temp;

    while (fread(&temp, sizeof(Patient), 1, file) == 1) {
        if (*count < MAX_RECORDS) {
            patients[*count] = temp;
            if (temp.id > maxID) maxID = temp.id;
            patients[*count].active = 1;
            (*count)++;
        }
        else {
            printf("Warning: Patient file contains more than %d records. Only loading first %d.\n", MAX_RECORDS, MAX_RECORDS);
            break;
        }
    }

    fclose(file);
    *nextID = maxID + 1;
    printf("Loaded %d patient records from %s.\n", *count, PATIENT_FILENAME);
}