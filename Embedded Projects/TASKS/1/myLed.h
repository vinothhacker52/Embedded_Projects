#include "MyLEDControl.h"
#include <cstddef>
MyLEDControl* MyLEDControl::instance = NULL;

MyLEDControl::MyLEDControl(unsigned int pin) : pin(pin) {
    instance = this;
}

void MyLEDControl::init() {
    // GPIO initialization
    IODIR0 |= (1 << pin); // Set pin as output

    // Timer configuration
    configure_timer();
}

void MyLEDControl::configure_timer() {
    // Timer initialization code
    T0PR = 14999; // Prescaler to get 1ms tick (assuming 15MHz PCLK)
    T0MR0 = 375;  // Match value for 0.375s
    T0MCR = 3;    // Interrupt and reset on MR0
    T0TCR = 1;    // Enable timer

    // Enable Timer 0 interrupt
    VICIntEnable |= (1 << 4);
    VICVectAddr4 = (unsigned long)timer_callback;
    VICVectCntl4 = 0x20 | 4;
}

void MyLEDControl::start() {
    T0TCR = 1; // Start Timer 0
}

void MyLEDControl::timer_callback() {
    static bool led_on = false;

    if (led_on) {
        IOCLR0 = (1 << instance->pin); // Turn off LED
        T0MR0 = 125; // Set match value for 0.125s
    } else {
        IOSET0 = (1 << instance->pin); // Turn on LED
        T0MR0 = 375; // Set match value for 0.375s
    }

    led_on = !led_on;

    T0IR = 1; // Clear interrupt flag
    VICVectAddr = 0; // Acknowledge interrupt
}
