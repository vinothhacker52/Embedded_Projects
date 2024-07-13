#include <lpc21xx.h>

#define BUZZER_PIN (1 << 21)

// Function to provide delay
void delay(unsigned int d) {
    unsigned int i, j;
    for (i = 0; i < d; i++)
        for (j = 0; j < 5000; j++); // Adjust this loop to control delay length
}

// Function to play a note of a given frequency for a given duration
void playTone(unsigned int frequency, unsigned int duration) {
    unsigned int i;
    unsigned int period = 1000000 / frequency; // Calculate the period of the note
    unsigned int halfPeriod = period / 2; // Half period for toggling the buzzer
    unsigned int cycles = duration * frequency / 1000; // Calculate the number of cycles to generate for the given duration
	
    for (i = 0; i < cycles; i++) {
        IOCLR0 = BUZZER_PIN; // Make pin LOW (buzzer ON)
        delay(halfPeriod);   // Delay for half the period
        IOSET0 = BUZZER_PIN; // Make pin HIGH (buzzer OFF)
        delay(halfPeriod);   // Delay for half the period
    }
}

int main() {
	int i;
    unsigned int kgfNotes[] = {523, 587, 659, 698, 784, 880, 987};
    unsigned int durations[] = {200, 200, 200, 300, 300, 300, 600};
    PINSEL0 = 0; // Set all pins as GPIO
    IODIR0 |= BUZZER_PIN; // Set pin P0.21 as output

    // Define notes and durations for the KGF theme
    

    // Play KGF theme
    for (i = 0; i < sizeof(kgfNotes) / sizeof(kgfNotes[0]); i++) {
        playTone(kgfNotes[i], durations[i]);
        delay(50); // Add a small pause between notes
    }

    return 0;
}
