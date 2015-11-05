#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bbbgpio.h"

static int writeValueToFile(char* path, char* value);

void pinMode(int pin, char* mode) {
    exportPin(pin);
    setDirection(pin, mode);
}

void digitalWrite(int pin, int value) {
    char buffer[256];
    char valBuffer[256];

    sprintf(buffer, "%s%d/value", GPIO_BASE_PATH, pin);
    sprintf(valBuffer, "%d", value);

    writeValueToFile(buffer, valBuffer);
}

int digitalRead(int pin) {
    char buffer[256];
    sprintf(buffer, "%s%d/value", GPIO_BASE_PATH, pin);

    FILE* file = fopen(buffer, "r");
    int val = 0;

    fscanf(file, "%d", &val);
    fclose (file);

    return val;
}

void exportPin(int pin) {
    char str[256];
    sprintf(str, "%d", pin);

    writeValueToFile(EXPORT_PATH, str);
}

void unExportPin(int pin) {
    char str[256];
    sprintf(str, "%d", pin);

    writeValueToFile(UNEXPORT_PATH, str);
}

void setDirection(int pin, char* mode) {
    char buffer[256];
    sprintf(buffer, "%s%d/direction", GPIO_BASE_PATH, pin);

    writeValueToFile(buffer, mode);
}



int writeValueToFile(char* path, char* value) {
    FILE *file;
    file = fopen(path, "w");
    int results = fputs(value, file);
    fclose(file);

    return results;
}
