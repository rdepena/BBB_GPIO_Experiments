#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "bbbgpio.h"

static int writeValueToFile(char* path, char* value);

int digitalWrite(int pin, int value) {
    char buffer[256];
    char valBuffer[256];

    sprintf(buffer, "%s%d/value", GPIO_BASE_PATH, pin);
    sprintf(valBuffer, "%d", value);

    return writeValueToFile(buffer, valBuffer);
}

int digitalRead(int pin) {
    char buffer[256];
    sprintf(buffer, "%s%d/value", GPIO_BASE_PATH, pin);

    FILE* file = fopen(buffer, "r");
    if(!file) {
        perror("digitalRead()");
        return EXIT_FAILURE;
    }
    int val = 0;

    fscanf(file, "%d", &val);
    fclose (file);

    return val;
}

int analogRead(int pin) {
    char buffer[256];
    sprintf(buffer, "%s/in_voltage%d_raw", AIN_BASE_PATH, pin);
    FILE* file = fopen(buffer, "r");
    if(!file) {
        puts(buffer);
        perror("analogRead()");
        return EXIT_FAILURE;
    }
    int val = 0;

    fscanf(file, "%d", &val);
    fclose (file);

    return val;
}

int exportPin(int pin) {
    char str[256];
    sprintf(str, "%d", pin);

    return writeValueToFile(EXPORT_PATH, str);
}

int unExportPin(int pin) {
    char str[256];
    sprintf(str, "%d", pin);

    return writeValueToFile(UNEXPORT_PATH, str);
}

int setDirection(int pin, char* mode) {
    char buffer[256];
    sprintf(buffer, "%s%d/direction", GPIO_BASE_PATH, pin);

    return writeValueToFile(buffer, mode);
}

int loadADC() {
    puts(SLOTS);
    return writeValueToFile(SLOTS, "BB-ADC");
}

static int writeValueToFile(char* path, char* value) {
    FILE *file;
    file = fopen(path, "w");
    if(!file) {
        //perror("writeValueToFile() file open");
        return EXIT_FAILURE;
    }
    int results = fputs(value, file);
    fclose(file);
    if(!results) {
       //perror("writeValueToFile() write");
       return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
