#include <lpc21xx.h>

#define LED0 (1 << 17)

void __attribute__((interrupt("FIQ"))) FIQ_Handler(void) {
    int i;
    EXTINT = (1 << 0); // Clear the interrupt flag in EXTINT
    IOSET0 = LED0;
    for (i = 0; i < 12000000; i++); // Delay loop (consider using a more efficient delay method)
    VICVectAddr = 0; // Clear the VICVectAddr register
}

int main() {
    int count = 0;

    // Configure LED pin as output
    PINSEL1 = 0x00000001; // Clear bits 2:3 to select GPIO mode for P0.17
    IODIR0 |= LED0; // Set P0.17 as output

    // Configure VIC for FIQ
    VICIntSelect &= ~(1 << 14); // Select FIQ for EINT0 (assuming EINT0 corresponds to interrupt 14)
    VICVectAddr3 = (unsigned long)FIQ_Handler;

    // Configure external interrupt 0 (EINT0)
    EXTMODE = (0 << 0); // Edge-sensitive mode
    EXTPOLAR = (0 << 0); // Falling edge polarity

    // Enable FIQ interrupt for EINT0
    VICIntEnable |= (1 << 14);

    while (1) {
        count++;
    }

    return 0;
}
