#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "bbgpio.h"

#define buffSize 256

static int writeValueToFile(char* path, char* value);

static int getCapemgrIndex(char* cape);

int digitalWrite(int pin, int value) {
    char buffer[buffSize];
    char valBuffer[buffSize];

    sprintf(buffer, "%s%d/value", GPIO_BASE_PATH, pin);
    sprintf(valBuffer, "%d", value);

    return writeValueToFile(buffer, valBuffer);
}

int digitalRead(int pin) {
    char buffer[buffSize];
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
    char buffer[buffSize];
    sprintf(buffer, "%s/in_voltage%d_raw", AIN_BASE_PATH, pin);
    FILE* file = fopen(buffer, "r");
    if(!file) {
        perror("analogRead()");
        return EXIT_FAILURE;
    }
    int val = 0;

    fscanf(file, "%d", &val);
    //fclose (file);

    return val;
}

int exportPin(int pin) {
    char str[buffSize];
    sprintf(str, "%d", pin);

    return writeValueToFile(EXPORT_PATH, str);
}

int unExportPin(int pin) {
    char str[buffSize];
    sprintf(str, "%d", pin);

    return writeValueToFile(UNEXPORT_PATH, str);
}

int setDirection(int pin, char* mode) {
    char buffer[buffSize];
    sprintf(buffer, "%s%d/direction", GPIO_BASE_PATH, pin);

    return writeValueToFile(buffer, mode);
}

int loadADC() {
    return writeValueToFile(SLOTS, ADC);
}

int unLoadADC() {
    char buffer[buffSize];
    int position = getCapemgrIndex(ADC);
    sprintf(buffer, "-%d", position);
    return writeValueToFile(SLOTS, buffer);
}

static int writeValueToFile(char* path, char* value) {
    FILE *file;
    file = fopen(path, "w");
    if(!file) {
        perror("writeValueToFile() file open");
        return EXIT_FAILURE;
    }
    int results = fputs(value, file);
    fclose(file);
    if(!results) {
       perror("writeValueToFile() write");
       return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static int getCapemgrIndex(char* cape) {
    char* buffer = malloc(buffSize);
    int c;
    int i = 0;


    FILE *fp = fopen(SLOTS, "r");
    if (!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    while ((c =fgetc(fp)) != EOF) {
        if (c == '\n') {
            i = 0;
            char* pos = strstr(buffer, cape);
            if (pos) {
                return atoi(&buffer[1]);
            }
        } else {
            buffer[i] = c;
            i++;
        }

    }

    return 0;
}
