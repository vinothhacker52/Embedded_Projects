#include<lpc21xx.h>
#include<string.h>
#define LCD_D 0xf << 20
#define RS 1<<17
#define rw 1<<18
#define E 1<<19
void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char*);
void LCD_TWO_INTEGER(int);
void LCD_INTEGER(int);
void LCD_FLOAT(float );
void STR_ROTATE(unsigned char *);


void delay(int d){
  T0PR = 15000 - 1; 
	T0TCR = 0x01;
	while(T0TC < d);
	T0TCR = 0x03;
	T0TCR = 0x00;
}
 

void STR_ROTATE(unsigned char *s){
	int l;
	int i;
	while(1){
	l = strlen((char *)s);
	for(i = 0; i < 16; i++){
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x80 + i);
	LCD_STR(s);
	if(i >= (16 - l)){
	LCD_COMMAND(0x80);
	LCD_STR(s + (l--));
	}
	delay(200);
	}
	}
}

void CG_WRITE(unsigned char n, unsigned char lut[]){
  unsigned char i;
	LCD_COMMAND(0x40);
	for(i = 0; i < n;i++)
	  {
			LCD_DATA(lut[i]);
    }
}

void LCD_FLOAT(float f){
     int temp = f;
	 LCD_INTEGER(temp);
	 LCD_DATA('.');
	 temp = (f - temp) * 1000;
	 LCD_INTEGER(temp);
}

void LCD_INTEGER(int n){
   char arr[10];
   signed char i = 0;
   if(n==0){
     LCD_DATA('0');
	 }
   else{
     if(n<0){
	 LCD_DATA('-');
	 n = -n;
	 }
	 while(n>0){
	 arr[i++] = n%10 + '0';
	 n = n /10;
	 }
	 for(--i; i >=0; i--){
	 LCD_DATA(arr[i]);
	 }
   }
}

void LCD_TWO_INTEGER(int n){
    LCD_DATA((n/10) + 48);
	LCD_DATA((n%10) + 48);
}
void LCD_STR(unsigned char *s){
	int pos = 0;
	while(*s){
	   pos++;
	   if(pos == 16){
	   LCD_COMMAND(0xC0);
	   }
	   LCD_DATA(*s++);
	}   
}

void LCD_INIT(){
IODIR1 = LCD_D | RS | E|rw;
IOCLR1 = rw;
LCD_COMMAND(0x01);
LCD_COMMAND(0x02);
LCD_COMMAND(0x0C);
LCD_COMMAND(0x28);
LCD_COMMAND(0x80);
}
void LCD_COMMAND(unsigned char cmd){
IOCLR1 = LCD_D;
IOSET1 = (cmd & 0xf0) << 16;
IOCLR1 = RS;
IOSET1 = E;
delay(2);
IOCLR1 = E;

IOCLR1 = LCD_D;
IOSET1 = (cmd & 0x0f) << 20;
IOCLR1 = RS;
IOSET1 = E;
delay(2);
IOCLR1 = E;
}

void LCD_DATA(unsigned char d){
IOCLR1 = LCD_D;
IOSET1 = (d & 0xf0) << 16;
IOSET1 = RS;
IOSET1 = E;
delay(2);
IOCLR1 = E;
	
IOCLR1 = LCD_D;
IOSET1 = (d & 0x0f) << 20;
IOSET1 = RS;
IOSET1 = E;
delay(2);
IOCLR1 = E;
}
