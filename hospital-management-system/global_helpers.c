#define _CRT_SECURE_NO_WARNINGS
#include "global_helpers.h"

//Universal functions used by both doctor and patient files

void clear_input_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void read_string(char* buf, int size) {
    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') buf[len - 1] = '\0';
}

void toLowerStr(const char* src, char* dst) {
    while (*src) {
        *dst++ = (char)tolower((unsigned char)*src++);
    }
    *dst = '\0';
}

void clearScreen(void) {
    system("cls");
}
const char* getGenderString(int code) {
    switch (code) {
    case 1: return "Male";
    case 2: return "Female";
    case 3: return "Rather not say";
    default: return "INVALID";
    }
}

const char* getRoomTypeString(int code) {
    switch (code) {
    case 1: return "Private";
    case 2: return "Public";
    default: return "INVALID";
    }
}