#include<lpc21xx.h>
#define LCD_DPINS 0x0f << 20
#define RS 1 << 17
#define RW 1 << 18
#define E  1 << 19

void LCD_INIT(void);
void delay_ms(int);
void LCD_COMMAND(unsigned char cmd);
void LCD_DATA(unsigned char data);
void LCD_STR(unsigned char*);

void LCD_INIT(void){
	IODIR1 = LCD_DPINS | RS | E | RW;
	IOCLR1 = RW;
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X02);
	LCD_COMMAND(0X0C);
	LCD_COMMAND(0X28);
	LCD_COMMAND(0X80);
}
void LCD_STR(unsigned char* s){
int pos = 0;
	while(*s){
	   pos++;
	   if(pos == 16){
	   LCD_COMMAND(0xC0);
	   }
	   LCD_DATA(*s++);
	}   
}
void LCD_COMMAND(unsigned char cmd){
	IOCLR1 = LCD_DPINS;
	IOSET1 = (cmd & 0xf0) << 16;
	IOCLR1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
	
	IOCLR1 = LCD_DPINS;
	IOSET1 = (cmd & 0x0f) << 20;
	IOCLR1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
}
void LCD_DATA(unsigned char d){
	IOCLR1 = LCD_DPINS;
	IOSET1 = (d & 0xf0) << 16;
	IOSET1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
	
	IOCLR1 = LCD_DPINS;
	IOSET1 = (d & 0x0f) << 20;
	IOSET1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
}
void delay_ms(int n){
	T0PR = 15000-1;
	T0TCR = 0X01;
	while(T0TC < n);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
