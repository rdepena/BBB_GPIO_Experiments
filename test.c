#include <stdio.h>
#include "src/bbbgpio.h"

#define blueLed 60
#define whiteLed 66
#define buttonPin 44

int main(void) {

    int pinValue = 0,
        buttonValue = 0;

    pinMode(blueLed, OUTPUT);
    pinMode(whiteLed, OUTPUT);
    pinMode(buttonPin, INPUT);


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

}
