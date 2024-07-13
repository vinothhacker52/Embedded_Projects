#include <lpc21xx.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"

#define LCD_D (0xF << 20)
#define RS    (1 << 17)
#define RW    (1 << 18)
#define E     (1 << 19)


typedef unsigned char U8;
typedef const char CC;
void LCD_INIT(void);
void LCD_COMMAND(U8);
void LCD_DATA(U8);
void LCD_STR(U8*);
void LCD_TWO_INTEGER(int);
void LCD_INTEGER(int);
void LCD_FLOAT(float);
void LCD_STR_DISPLAY(U8*, U8*);
void TITLE_DISPLAY(void);
void LCD_TOTAL_DISPLAY(U8*, int);
void LCD_FINAL_BILL(void);
extern U8 *pen;
extern U8 *book;
extern int price;

void LCD_FINAL_BILL(void){
LCD_INIT();
LCD_STR("YOUR TOTAL BILL");
LCD_COMMAND(0XC0);
LCD_STR(" AMOUNT IS : ");
LCD_INTEGER(price);
delay_s(5);
LCD_STR_DISPLAY("  THANK YOUU!", " VISIT AGAIN :)");
}
void LCD_TOTAL_DISPLAY(U8* s, int price) {
    U8 temp[20] = {0}; 
    U8 p[10]; 
    sprintf((char*)p, "%d", price);
    if(strcmp((char*)s, (CC*)pen) == 0) {
        strcpy((char*)temp, "Pen: Rs "); 
    }
    if(strcmp((char*)s, (CC*)book) == 0) {
        strcpy((char*)temp, "Book: Rs "); 
    }
    strcat((char*)temp, (char*)p); 
    LCD_STR_DISPLAY("YOUR PRODUCT", (U8*)temp); 
    delay_s(1);
}



void TITLE_DISPLAY(void) {
    LCD_STR_DISPLAY(" SMART TROLLEY", "   USING RFID");
    delay_s(3);
    LCD_STR_DISPLAY(" HI WELCOME TO", "OUR SUPERMARKET");
    delay_s(2);
    LCD_STR_DISPLAY("  HAVE A GREAT ", "   EXPERIENCE!");
    delay_s(2);
}

void LCD_STR_DISPLAY(U8* t, U8 *b) {
    LCD_INIT();
    LCD_STR(t);
    LCD_COMMAND(0xC0);
    LCD_STR(b);
}

void LCD_FLOAT(float f) {
    int temp = f;
    LCD_INTEGER(temp);
    LCD_DATA('.');
    temp = (f - temp) * 1000;
    LCD_INTEGER(temp);
}

void LCD_INTEGER(int n) {
    char arr[10];
    signed char i = 0;
    
    if (n == 0) {
        LCD_DATA('0');
    } else {
        if (n < 0) {
            LCD_DATA('-');
            n = -n;
        }
        while (n > 0) {
            arr[i++] = n % 10 + '0';
            n = n / 10;
        }
        for (--i; i >= 0; i--) {
            LCD_DATA(arr[i]);
        }
    }
}

void LCD_STR(U8 *s) {
    char pos = 0;
    while (*s) {
        pos++;
        if (pos == 16) {
            LCD_COMMAND(0xC0);
        }
        LCD_DATA(*s++);
    }   
}

void LCD_INIT() {
    IODIR1 = LCD_D | RS | E | RW;
    IOCLR1 = RW;
    LCD_COMMAND(0x01);
    LCD_COMMAND(0x02);
    LCD_COMMAND(0x0C);
    LCD_COMMAND(0x28);
    LCD_COMMAND(0x80);
}

void LCD_COMMAND(U8 cmd) {
    IOCLR1 = LCD_D;
    IOSET1 = (cmd & 0xF0) << 16;
    IOCLR1 = RS;
    IOSET1 = E;
    delay_ms(2);
    IOCLR1 = E;
    IOCLR1 = LCD_D;
    IOSET1 = (cmd & 0x0F) << 20;
    IOCLR1 = RS;
    IOSET1 = E;
    delay_ms(2);
    IOCLR1 = E;
}

void LCD_DATA(U8 d) {
    IOCLR1 = LCD_D;
    IOSET1 = (d & 0xF0) << 16;
    IOSET1 = RS;
    IOSET1 = E;
    delay_ms(2);
    IOCLR1 = E;
    IOCLR1 = LCD_D;
    IOSET1 = (d & 0x0F) << 20;
    IOSET1 = RS;
    IOSET1 = E;
    delay_ms(2);
    IOCLR1 = E;
}
