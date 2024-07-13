#include<lpc21xx.h>

void delay(int d){
  T0PR = 15000 - 1; 
	T0TCR = 0x01;
	while(T0TC < d);
	T0TCR = 0x03;
	T0TCR = 0x00;
}
