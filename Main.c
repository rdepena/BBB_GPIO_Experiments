#include <stdio.h>
#include "src/bbbgpio.h"

int main(void) {

    int ledPin = 60;

    pinMode(ledPin, OUTPUT);

    digitalWrite(ledPin, HIGH);

    puts("turn it off");
    getchar();

    digitalWrite(ledPin, LOW);
}
