#include <stdio.h>
#include <stdlib.h>
#include "src/bbbgpio.h"


#define blueLed 60
#define whiteLed 66
#define buttonPin 44

int main(void) {

    int pinValue = 0,
        buttonValue = 0,
        result = 0;

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

    result = exportPin(whiteLed);
    if (result) {
        perror("whiteLed export failed");
        return EXIT_FAILURE;
    }

    result = setDirection(whiteLed, OUTPUT);
    if (result) {
        perror("whiteLed set direction failed");
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

    digitalRead(blueLed);
    if (pinValue == HIGH) {
        printf("pin value at HIGH\n");
    }


    while((buttonValue = digitalRead(buttonPin)) == 0) {
        digitalWrite(blueLed, LOW);
        digitalWrite(whiteLed, HIGH);
    }

    printf("button value: %d\n", buttonValue);

    digitalWrite(blueLed, HIGH);
    digitalWrite(whiteLed, LOW);

    printf("turn it off\n");
    getchar();

    digitalWrite(blueLed, LOW);
    digitalWrite(whiteLed, LOW);

    pinValue = digitalRead(blueLed);
    if (pinValue == LOW) {
        printf("pin value at LOW\n");
    }

    unExportPin(blueLed);
    unExportPin(whiteLed);

    return 0;
}
