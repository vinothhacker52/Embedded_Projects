#include "LEDControl.hpp"
#include "LEDControl.cpp"
#include "LPC21xx.h"

extern "C" void cpp_main();
void Timer0_ISR(void) __irq;

#define LED_PIN 10

LEDControl led(LED_PIN);

// Variables to manage duty cycle
volatile bool led_on = false;
const unsigned int delay_on = 750000;  // 75% of 1s (1s / 2Hz)
const unsigned int delay_off = 250000; // 25% of 1s (1s / 2Hz)

// Timer0 ISR
void Timer0_ISR(void) __irq {
    if (led_on) {
        led.off();
        T0MR0 = delay_off;  // Set delay for off period
    } else {
        led.on();
        T0MR0 = delay_on;   // Set delay for on period
    }
    led_on = !led_on;

    T0IR = 1;             // Clear interrupt flag
    VICVectAddr = 0;      // Update interrupt priority hardware
}

void setupTimer0() {
    T0MR0 = delay_on;     // Initial delay for on period
    T0MCR = 3;            // Interrupt and reset on match
    T0TCR = 1;            // Enable Timer0
    VICVectAddr0 = (unsigned long)Timer0_ISR; // Set ISR address
    VICVectCntl0 = 0x20 | 4;  // Enable Timer0 interrupt
    VICIntEnable = 1 << 4;    // Enable Timer0 interrupt
}

extern "C" void cpp_main() {
    led.init();
    setupTimer0();

    while (true) {
        // Main loop can perform other tasks or enter low-power mode
    }
}
