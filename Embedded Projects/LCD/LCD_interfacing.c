#include<lpc21xx.h>
#define LCD_D 0xff
#define RS 1<<8
#define E 1<<9

void delay(int d){
  T0PR = 15000 - 1; 
	T0TCR = 0x01;
	while(T0TC < d);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);

/*int main(){
	 LCD_INIT();
	 LCD_DATA('A');
} */

void LCD_INIT(){
IODIR0 = LCD_D | RS | E;
IOCLR0 = LCD_D;
LCD_COMMAND(0x01);
LCD_COMMAND(0x02);
LCD_COMMAND(0x0C);
LCD_COMMAND(0x38);
LCD_COMMAND(0x80);
}
void LCD_COMMAND(unsigned char cmd){
IOCLR0 = LCD_D;
IOSET0 = cmd;
IOCLR0 = RS;
IOSET0 = E;
delay(2);
IOCLR0 = E;
}

void LCD_DATA(unsigned char d){
IOCLR0 = LCD_D;
IOSET0 = d;
IOSET0 = RS;
IOSET0 = E;
delay(2);
IOCLR0 = E;
}
