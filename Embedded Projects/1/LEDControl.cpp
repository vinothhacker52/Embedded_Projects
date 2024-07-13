#include "LEDControl.hpp"
#include "LPC21xx.h"

LEDControl::LEDControl(unsigned int pin) : pin(pin) {}

void LEDControl::init() {
    configurePin();
}

void LEDControl::on() {
    IOSET0 = (1 << pin);
}

void LEDControl::off() {
    IOCLR0 = (1 << pin);
}

void LEDControl::toggle() {
    if (IOPIN0 & (1 << pin)) {
        off();
    } else {
        on();
    }
}

void LEDControl::configurePin() {
    IODIR0 |= (1 << pin); // Set the pin as output
}
