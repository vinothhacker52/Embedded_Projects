#include "LPC21XX.h"  // Include LPC2129 specific register definitions

class LEDController {
public:
    LEDController() : pin(10) {
        initializeGPIO();
        initializeTimer();
    }

    void start() {
        while (1) {
            // Main loop - LED toggling happens in timer ISR
        }
    }

private:
    int pin;  // GPIO pin for LED

    void initializeGPIO() {
        // Configure GPIO pin for LED (P0.10 for LPC2129)
        PINSEL1 &= ~(0x3 << 20);  // Clear bits 20 and 21 to configure P0.10 as GPIO
        IO0DIR |= (1 << 10);      // Set P0.10 as output
    }

    void initializeTimer() {
        // Configure Timer 0 (Assuming Timer 0 for LPC2129) for 2Hz frequency
        T0PR = 0;            // Prescale value for timer 0 (no prescale)
        T0MR0 = 15000000;    // Match value for 2Hz frequency (assuming 15 MHz clock)

        // Configure match control register: generate interrupt on MR0 match
        T0MCR |= (1 << 0) | (1 << 1);  // Enable interrupt and reset on match MR0

        // Enable Timer 0 interrupt in VIC (Vector Interrupt Controller)
        VICVectAddr0 = timer0ISR; // Set interrupt vector address
        VICVectCntl0 = (1 << 5) | 4;              // Enable slot 0 and set Timer0 interrupt
        VICIntEnable |= (1 << 4);                 // Enable Timer 0 interrupt in VIC

        // Start Timer 0
        T0TCR = 1;  // Enable Timer 0
    }

    void toggleLED() {
        static int count = 0;
        if (count < 3) {
            IO0CLR = (1 << 10);  // Clear P0.10 (LED on)
        } else {
            IO0SET = (1 << 10);  // Set P0.10 (LED off)
        }
        count = (count + 1) % 4;  // 75% duty cycle (on 3 out of 4 cycles)
    }

    // Timer 0 Interrupt Service Routine (ISR)
    void timer0ISR() {
        // Clear interrupt flag
        T0IR = (1 << 0);

        // Toggle LED
        toggleLED();

        // End of interrupt (EOI) for VIC
        VICVectAddr = 0x00000000;
    }
};

int main() {
    // Initialize LED controller and start LED toggling
    LEDController controller;
    controller.start();

    return 0;
}
