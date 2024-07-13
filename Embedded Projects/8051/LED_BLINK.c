#include<reg51.h>
#include "delay.h"
#define LEDS P1


void main(){
	while(1){
	char i,j;
	for(i = 0,j = 7;i <= 3; i++,j--){
		LEDS  = ((1<<i)^0x0f);
		LEDS |= ((1<<j));
		delay_ms(500);
	}
	for(i = 3,j = 4;i >= 0; i--,j++){
		LEDS  = ((1<<i)^0x0f);
		LEDS |= ((1<<j));
		delay_ms(500);
	}	 
	}
}

