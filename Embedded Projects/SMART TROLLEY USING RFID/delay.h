#include <lpc21xx.h>

void delay_s(int);
void delay_ms(int);

void delay_s(int n) {
    T0PR = 15000000 - 1;
    T0TCR = 0x01;
    while (T0TC < n);
    T0TCR = 0x03;
    T0TCR = 0x00;
}

void delay_ms(int d) {
    T0PR = 15000 - 1; 
    T0TCR = 0x01;
    while (T0TC < d);
    T0TCR = 0x03;
    T0TCR = 0x00;
}
