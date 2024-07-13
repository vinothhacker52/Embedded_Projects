#include<lpc21xx.h>
#include<string.h>
#define LCD_D 0xff << 2
#define RS 1<<12
#define E 1<<15
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



int main(){
     //unsigned char s[50] = "Vinoth Kumar KUMAR ASHFSA";
	 LCD_INIT();
     //LCD_FLOAT(3.14);	
	 STR_ROTATE("VINOTH KUMAR"); 

} 

void STR_ROTATE(unsigned char *s){
	int l;
	int i;
	while(1){
	l = strlen(s);
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
IODIR0 = LCD_D | RS | E;
LCD_COMMAND(0x01);
LCD_COMMAND(0x02);
LCD_COMMAND(0x0C);
LCD_COMMAND(0x38);
LCD_COMMAND(0x80);
}
void LCD_COMMAND(unsigned char cmd){
IOCLR0 = LCD_D;
IOSET0 = cmd << 2;
IOCLR0 = RS;
IOSET0 = E;
delay(2);
IOCLR0 = E;
}

void LCD_DATA(unsigned char d){
IOCLR0 = LCD_D;
IOSET0 = d << 2;
IOSET0 = RS;
IOSET0 = E;
delay(2);
IOCLR0 = E;
}
