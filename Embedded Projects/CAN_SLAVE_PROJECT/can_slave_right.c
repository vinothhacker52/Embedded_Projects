#include "Can_Driver.h"
#include "lcd.h"
#define LED2 1 << 18

char flag;
CAN_MSG m;
void blink_led(void);


int main(){
LCD_INIT();
LCD_STR_DISPLAY(" NODE IS READY", " TO COMMUNICATE");
CAN_INIT();
while(1){
flag = 0;
CAN_RX(&m);
if((m.id == 2) && (flag == 0)){
LCD_INIT();
LCD_STR_DISPLAY(" A MESSAGE IS ", "   RECEIVED...");
delay_s(2);
LCD_INIT();
LCD_STR_DISPLAY("RIGHT INDICATOR", "IS TURNED ON->");
IODIR0 = LED2;

blink:
blink_led();
CAN_RX(&m);
if(m.id == 2){
flag = 1;
}
else{
goto blink;
}
}

if((m.id == 2) && (flag == 1)){
LCD_INIT();
LCD_STR_DISPLAY("RIGHT INDICATOR", "IS TURNED OFF->");
flag = 0;
}
else if(m.id == 2){
goto blink;
}
}
}

void blink_led(void) {
while(((C2GSR & 1) == 0)){
IOCLR0 = LED2;
delay_ms(500);
IOSET0 = LED2;
delay_ms(500);
}
}