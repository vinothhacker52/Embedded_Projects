#include "Can_Driver.h"
#include "lcd.h"
#define MOTOR_POSITIVE 1 << 22
#define MOTOR_NEGATIVE 1 << 23

char flag;
CAN_MSG m;
void wiper_on(void);


int main(){
LCD_INIT();
LCD_STR_DISPLAY(" NODE IS READY", " TO COMMUNICATE");
CAN_INIT();
while(1){
flag = 0;
CAN_RX(&m);
if((m.id == 3) && (flag == 0)){
LCD_INIT();
LCD_STR_DISPLAY(" A MESSAGE IS ", "   RECEIVED...");
delay_s(2);
LCD_INIT();
LCD_STR_DISPLAY("     WIPER", "IS TURNED ON->");
	
IODIR0 |= MOTOR_POSITIVE | MOTOR_NEGATIVE;

wiper:
wiper_on();
CAN_RX(&m);
if(m.id == 3){
flag = 1;
}
else{
goto wiper;
}
}

if((m.id == 3) && (flag == 1)){
LCD_INIT();
LCD_STR_DISPLAY("     WIPER", "IS TURNED OFF<-");
flag = 0;
IOCLR0 = MOTOR_POSITIVE;
IOCLR0 = MOTOR_NEGATIVE;
}
else if(m.id == 3){
goto wiper;
}
}
}

void wiper_on(void) {
	
while(((C2GSR & 1) == 0)){

IOSET0 = MOTOR_POSITIVE;
IOCLR0 = MOTOR_NEGATIVE;
delay_s(3);
IOSET0 = MOTOR_NEGATIVE;
IOCLR0 = MOTOR_POSITIVE;
}
}
