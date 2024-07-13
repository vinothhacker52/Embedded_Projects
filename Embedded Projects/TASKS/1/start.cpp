#include "MyLEDControl.h"
#include "myLed.h"

MyLEDControl led(10); // Example using P0.10

extern "C" void startup() {
    led.init();
    led.start();
    while (1) {
        // Main loop
    }
}
