#ifndef GLOBAL_HELPERS_H
#define GLOBAL_HELPERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Macrios
#define MAX_RECORDS 100
#define STRLEN 100
#define PATIENT_FILENAME "patients.dat"
#define DOCTOR_FILENAME "doctors.dat"

//Patient Structure
typedef struct {
    int id;
    char name[STRLEN];
    int age;
    int genderCode; // 1=Male, 2=Female, 3=mix type shi
    char disease[STRLEN];
    int room;
    int roomType; // 1=Private, 2=Public
    int active;
} Patient;

//Doctor Structure
typedef struct {
    int id;
    char name[STRLEN];
    char specialization[STRLEN];
    char contact[STRLEN];
    char availability[STRLEN];
    int active;
} Doctor;

//Universal
void clear_input_line(void);
void read_string(char* buf, int size);
void toLowerStr(const char* src, char* dst);
void clearScreen(void);
const char* getGenderString(int code);
const char* getRoomTypeString(int code);

#endif