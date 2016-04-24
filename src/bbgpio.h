#define HIGH 1
#define LOW 0

#define INPUT "in"
#define OUTPUT "out"

#define EXPORT_PATH "/sys/class/gpio/export"
#define UNEXPORT_PATH "/sys/class/gpio/unexport"
#define GPIO_BASE_PATH "/sys/class/gpio/gpio"
#define SLOTS "/sys/devices/platform/bone_capemgr/slots"
#define AIN_BASE_PATH "/sys/bus/iio/devices/iio:device0"
#define ADC "BB-ADC"

// #define EXPORT_PATH "gpio/export"
// #define UNEXPORT_PATH "gpio/unexport"
// #define GPIO_BASE_PATH "gpio/gpio"

int unExportPin(int pin);

int exportPin(int pin);

int setDirection(int pin, char* mode);

int digitalWrite(int pin, int value);

int digitalRead(int pin);

int loadADC();

int unLoadADC();

int analogRead(int pin);
