#include <stdio.h>
#include "src/bbbgpio.h"

#define ledPin 60

int main(void) {

    pinMode(ledPin, OUTPUT);

    digitalWrite(ledPin, HIGH);

    int pinValue = digitalRead(ledPin);
    if (pinValue == HIGH) {
        printf("pin value at HIGH\n");
    }


    printf("turn it off\n");
    getchar();

    digitalWrite(ledPin, LOW);

    pinValue = digitalRead(ledPin);
    if (pinValue == LOW) {
        printf("pin value at LOW\n");
    }

    unExportPin(ledPin);
}
