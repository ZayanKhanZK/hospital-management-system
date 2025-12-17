#define _CRT_SECURE_NO_WARNINGS
#include "doctor.h" 

//Check if record is here
static int findDoctorIndexByID(Doctor doctors[], int count, int id) {
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (doctors[i].active && doctors[i].id == id) return i;
    }
    return -1;
}

//Print for new doctor
static void printDoctorDetails(const Doctor* d) {
    printf("----------------------------------------\n");
    printf("  ID: %d\n", d->id);
    printf("  Name: %s\n", d->name);
    printf("  Specialization: %s\n", d->specialization);
    printf("  Contact: %s\n", d->contact);
    printf("  Availability: %s\n", d->availability);
    printf("----------------------------------------\n");
}

//Search
void searchDoctorMenu(Doctor doctors[], int count) {
    int choice;

    while (1) {
        printf("\n=== Doctor Search & Filter ===\n");
        printf("1. Search by ID\n");
        printf("2. Search by Name (partial match)\n");
        printf("3. Search by Specialization\n");
        printf("4. Back to Doctor Menu\n");
        printf("-------------------------------\n");
        printf("Enter your choice (1-4): ");

        if (scanf("%d", &choice) != 1) {
            clear_input_line();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        clear_input_line();
        clearScreen();

        switch (choice) {
        case 1: searchDoctorByID(doctors, count); break;
        case 2: searchDoctorByName(doctors, count); break;
        case 3: searchDoctorBySpecialization(doctors, count); break;
        case 4: return;
        default: printf("Invalid choice. Please choose 1-4.\n");
        }
        if (choice != 4) {
            printf("\nPress Enter to return to the search menu...");
            clear_input_line();
            clearScreen();
        }
    }
}

//Main menu
void doctorMenu(Doctor doctors[], int* count, int* nextID) {
    int choice;
    while (1) {
        printf("\n=== Doctor Management Menu ===\n");
        printf("1. Add new doctor record\n");
        printf("2. View all doctor records\n");
        printf("3. Search/Filter doctors\n");
        printf("4. Update doctor record\n");
        printf("5. Delete doctor record (Retirement/Transfer)\n");
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
        case 1: addDoctor(doctors, count, nextID); break;
        case 2: viewDoctors(doctors, *count); break;
        case 3: searchDoctorMenu(doctors, *count); break;
        case 4: updateDoctor(doctors, *count); break;
        case 5: deleteDoctor(doctors, count); break;
        case 6: displayDoctorSummary(doctors, *count, *nextID); break;
        case 7: return;
        default: printf("Invalid choice. Please choose 1-7.\n");
        }
        if (choice != 7) {
            printf("\nPress Enter to return to the menu...");
            clear_input_line();
            clearScreen();
        }
    }
}

//Doctor add
void addDoctor(Doctor doctors[], int* count, int* nextID) {
    if (*count >= MAX_RECORDS) {
        printf("Doctor database full (max %d).\n", MAX_RECORDS);
        return;
    }

    int index = -1;
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (!doctors[i].active) { index = i; break; }
    }

    if (index == -1) {
        printf("Error: Database count is wrong. No free slot found.\n");
        return;
    }

    Doctor d;
    d.id = (*nextID)++;
    d.active = 1;

//Name
    while (1) {
        printf("Enter Doctor name: ");
        read_string(d.name, STRLEN);
        if (strlen(d.name) == 0) {
            printf("Name cannot be blank. Please try again.\n");
        }
        else {
            break;
        }
    }

//Specialization
    while (1) {
        printf("Enter Specialization (e.g., Cardiology): ");
        read_string(d.specialization, STRLEN);
        if (strlen(d.specialization) == 0) {
            printf("Specialization cannot be blank. Please try again.\n");
        }
        else {
            break;
        }
    }

//Contact ( optional )
    printf("Enter Contact (Phone/Email) [Optional]: ");
    read_string(d.contact, STRLEN);

//Available
    printf("Enter Availability (e.g., MWF, Tue/Thu 9-5) [Optional]: ");
    read_string(d.availability, STRLEN);

    doctors[index] = d;
    (*count)++;

    printf("Doctor added successfully! Assigned ID: %d\n", d.id);
}

//View doctors
void viewDoctors(Doctor doctors[], int count) {
    printf("\n--- Doctor Records (%d) ---\n", count);
    if (count == 0) {
        printf("No active doctor records to show.\n");
        return;
    }

    printf("ID   | Name                 | Specialization       | Contact              | Availability\n");
    printf("-----|----------------------|----------------------|----------------------|----------------------\n");
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (doctors[i].active) {
            printf("%-4d | %-20s | %-20s | %-20s | %-20s\n",
                doctors[i].id, doctors[i].name, doctors[i].specialization, doctors[i].contact, doctors[i].availability);
        }
    }
}

//View doctor field
void updateDoctor(Doctor doctors[], int count) {
    int id;
    printf("Enter doctor ID to update: ");
    if (scanf("%d", &id) != 1) { clear_input_line(); printf("Invalid input.\n"); return; }
    clear_input_line();

    int idx = findDoctorIndexByID(doctors, count, id);
    if (idx == -1) { printf("Doctor with ID %d not found.\n", id); return; }

    Doctor* d = &doctors[idx];
    printf("Updating Doctor (ID %d). Leave blank to keep current value.\n", d->id);

    char buf[STRLEN];

    printf("Current name: %s\nNew name: ", d->name);
    read_string(buf, STRLEN);
    if (strlen(buf) > 0) strncpy(d->name, buf, STRLEN - 1);

    printf("Current specialization: %s\nNew specialization: ", d->specialization);
    read_string(buf, STRLEN);
    if (strlen(buf) > 0) strncpy(d->specialization, buf, STRLEN - 1);

    printf("Current contact: %s\nNew contact (Phone/Email): ", d->contact);
    read_string(buf, STRLEN);
    if (strlen(buf) > 0) strncpy(d->contact, buf, STRLEN - 1);

    printf("Current availability: %s\nNew availability: ", d->availability);
    read_string(buf, STRLEN);
    if (strlen(buf) > 0) strncpy(d->availability, buf, STRLEN - 1);

    printf("Doctor updated successfully.\n");
}

//Doctor avability
void deleteDoctor(Doctor doctors[], int* count) {
    int id;
    char confirm[4];

    printf("Enter doctor ID to DELETE: ");
    if (scanf("%d", &id) != 1) { clear_input_line(); printf("Invalid input.\n"); return; }
    clear_input_line();

    int idx = findDoctorIndexByID(doctors, *count, id);
    if (idx == -1) { printf("Doctor with ID %d not found.\n", id); return; }

    printf("\nWARNING: You are about to delete the record for:\n");
    printDoctorDetails(&doctors[idx]);
    printf("Are you sure you want to proceed? (yes/no): ");
    read_string(confirm, 4);

    if (strcmp("yes", confirm) == 0 || strcmp("YES", confirm) == 0 || strcmp("y", confirm) == 0) {
        doctors[idx].active = 0;
        (*count)--;
        printf("Doctor with ID %d successfully deleted (record removed).\n", id);
    }
    else {
        printf("Deletion cancelled. Doctor record remains active.\n");
    }
}

//Search by ID
void searchDoctorByID(Doctor doctors[], int count) {
    int id;
    printf("Enter doctor ID to search: ");
    if (scanf("%d", &id) != 1) { clear_input_line(); printf("Invalid input.\n"); return; }
    clear_input_line();

    int idx = findDoctorIndexByID(doctors, count, id);
    if (idx == -1) { printf("Doctor with ID %d not found.\n", id); }
    else {
        printf("\n--- Detailed Search Result ---\n");
        printDoctorDetails(&doctors[idx]);
    }
}

//Search by name
void searchDoctorByName(Doctor doctors[], int count) {
    char query[STRLEN];
    printf("Enter name (or part of name) to search: ");
    read_string(query, STRLEN);

    if (strlen(query) == 0) return;

    char qlow[STRLEN];
    toLowerStr(query, qlow);

    int found = 0;
    printf("\n--- Search Results for Doctor Name containing '%s' ---\n", query);
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (doctors[i].active) {
            char nameLow[STRLEN];
            toLowerStr(doctors[i].name, nameLow);
            if (strstr(nameLow, qlow) != NULL) {
                printDoctorDetails(&doctors[i]);
                found = 1;
            }
        }
    }
    if (!found) printf("No doctors matched the name '%s'.\n", query);
}

//Search by specializtion
void searchDoctorBySpecialization(Doctor doctors[], int count) {
    char query[STRLEN];
    printf("Enter specialization (or part of specialization) to search: ");
    read_string(query, STRLEN);

    if (strlen(query) == 0) return;

    char qlow[STRLEN];
    toLowerStr(query, qlow);

    int found = 0;
    printf("\n--- Search Results for Specialization containing '%s' ---\n", query);
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (doctors[i].active) {
            char specLow[STRLEN];
            toLowerStr(doctors[i].specialization, specLow);
            if (strstr(specLow, qlow) != NULL) {
                printDoctorDetails(&doctors[i]);
                found = 1;
            }
        }
    }
    if (!found) printf("No doctors matched the specialization '%s'.\n", query);
}


//DB Summary
void displayDoctorSummary(Doctor doctors[], int count, int nextID) {
    printf("\n=== Doctor Database Summary ===\n");
    printf("Total Active Doctors: %d / %d (Max Capacity)\n", count, MAX_RECORDS);
    printf("Next Assigned Doctor ID: %d\n", nextID);
    printf("--------------------------\n");
}


//Save
void saveDoctorsToFile(Doctor doctors[], int count) {
    FILE* file = fopen(DOCTOR_FILENAME, "wb");
    if (file == NULL) {
        printf("Error: Could not save data to %s.\n", DOCTOR_FILENAME);
        return;
    }

    int active_count = 0;
    for (int i = 0; i < MAX_RECORDS; i++) {
        if (doctors[i].active) {
            fwrite(&doctors[i], sizeof(Doctor), 1, file);
            active_count++;
        }
    }

    fclose(file);
    printf("Successfully saved %d doctor records to %s.\n", active_count, DOCTOR_FILENAME);
}

//Load
void loadDoctorsFromFile(Doctor doctors[], int* count, int* nextID) {
    FILE* file = fopen(DOCTOR_FILENAME, "rb");
    if (file == NULL) {
        printf("No existing doctor data found (%s). Starting new database.\n", DOCTOR_FILENAME);
        return;
    }

    *count = 0;
    int maxID = 0;
    Doctor temp;

    while (fread(&temp, sizeof(Doctor), 1, file) == 1) {
        if (*count < MAX_RECORDS) {
            doctors[*count] = temp;
            if (temp.id > maxID) maxID = temp.id;
            doctors[*count].active = 1;
            (*count)++;
        }
        else {
            printf("Warning: Doctor file contains more than %d records. Only loading first %d.\n", MAX_RECORDS, MAX_RECORDS);
            break;
        }
    }

    fclose(file);
    *nextID = maxID + 1;
    printf("Loaded %d doctor records from %s.\n", *count, DOCTOR_FILENAME);
}



