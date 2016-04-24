#include <stdio.h>
#include <stdlib.h>
#include "src/bbgpio.h"


#define blueLed 60
#define whiteLed 66
#define buttonPin 44

int pinValue = 0,
    result = 0;

int setup();
void loop();

int main(void) {

    result = setup();
    if (result != 0) {
        return 1;
    }

    while (1) {
        loop();
    }

    unExportPin(blueLed);
    unExportPin(buttonPin);

    return 0;
}

int setup() {

    result = exportPin(blueLed);
    if (result) {
        perror("blueLed export failed");
        return EXIT_FAILURE;
    }

    result = setDirection(blueLed, OUTPUT);
    if (result) {
        perror("blueLed set direction failed");
        return EXIT_FAILURE;
    }

    result = exportPin(buttonPin);
    if (result) {
        perror("buttonPin export failed");
        return EXIT_FAILURE;
    }

    result = setDirection(buttonPin, INPUT);
    if (result) {
        perror("buttonPin set direction failed");
        return EXIT_FAILURE;
    }
    return 0;
}

void loop() {
    if (digitalRead(buttonPin) == 1) {
        digitalWrite(blueLed, HIGH);
    }
    else {
        digitalWrite(blueLed, LOW);
    }
}
