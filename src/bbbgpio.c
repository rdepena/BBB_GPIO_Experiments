#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HIGH 1
#define LOW 0

#define INPUT "in"
#define OUTPUT "out"

#define EXPORT_PATH "/sys/class/gpio/export"
#define GPIO_BASE_PATH "/sys/class/gpio/gpio"

// #define EXPORT_PATH "gpio/export"
// #define GPIO_BASE_PATH "gpio/gpio"

static void registerPin (int pin);

static void setDirection (int pin, char* mode);

static int writeValueToFile(char* path, char* value);

void pinMode(int pin, char* mode) {
    registerPin(pin);
    setDirection(pin, mode);
}

void digitalWrite(int pin, int value) {
    char buffer[256];
    char valBuffer[256];

    sprintf(buffer, "%s%d/value", GPIO_BASE_PATH, pin);
    sprintf(valBuffer, "%d", value);

    writeValueToFile(buffer, valBuffer);
}

static void registerPin (int pin) {
    char str[256];
    sprintf(str, "%d", pin);

    writeValueToFile(EXPORT_PATH, str);
}

static void setDirection(int pin, char* mode) {
    char buffer[256];
    sprintf(buffer, "%s%d/direction", GPIO_BASE_PATH, pin);

    writeValueToFile(buffer, mode);
}

static int writeValueToFile(char* path, char* value) {
    FILE *file;
    file = fopen(path, "w");
    int results = fputs(value, file);
    fclose(file);

    return results;
}
