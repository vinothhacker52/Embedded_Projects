#include <lpc21xx.h>

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
void LCD_INTEGER(int);
void LCD_FLOAT(float);
void LCD_STR_DISPLAY(U8*, U8*);
void TITLE_DISPLAY(void);
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

void TITLE_DISPLAY(void) {
    LCD_STR_DISPLAY(" CAR DASHBOARD", "   USING CAN");
    delay_s(3);
    LCD_STR_DISPLAY("  PRESS 1  FOR", "LEFT INDICATOR");
    delay_s(2);
    LCD_STR_DISPLAY("  PRESS 2  FOR", "RIGHT INDICATOR");
    delay_s(2);
	  LCD_STR_DISPLAY("  PRESS 3 FOR", "      WIPER ");
    delay_s(2);
	  LCD_STR_DISPLAY(" CHOOSE BETWEEN ", "  1   2   3");
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
