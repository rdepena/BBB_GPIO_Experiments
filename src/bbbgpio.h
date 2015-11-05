#define HIGH 1
#define LOW 0

#define INPUT "in"
#define OUTPUT "out"

#define EXPORT_PATH "/sys/class/gpio/export"
#define UNEXPORT_PATH "/sys/class/gpio/unexport"
#define GPIO_BASE_PATH "/sys/class/gpio/gpio"

// #define EXPORT_PATH "gpio/export"
// #define UNEXPORT_PATH "gpio/unexport"
// #define GPIO_BASE_PATH "gpio/gpio"


void pinMode(int pin, char* mode);

void unExportPin(int pin);

void exportPin(int pin);

void setDirection(int pin, char* mode);

void digitalWrite(int pin, int value);

int digitalRead(int pin);
