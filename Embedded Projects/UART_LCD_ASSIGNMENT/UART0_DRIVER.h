#include<lpc21xx.h>
void UART0_INIT(void);
void UART0_TX(unsigned char);
void UART0_STR(unsigned char*);
unsigned char UART0_RX(void);
unsigned char* UART0_LCD(unsigned char* p);


void UART0_INIT(void){
	PINSEL0 = 0X00000005;
	U0LCR = 0X83;
	U0DLL = 97;
	U0LCR = 0X03;
}
unsigned char* UART0_LCD(unsigned char* p){
    unsigned char i = 0;
    unsigned char c = UART0_RX();
    while(c != '\n'){
        p[i++] = c;
        c = UART0_RX();		
    }
    p[--i] = '\0';
    return p;	
}

void UART0_STR(unsigned char* s){
while(*s)
UART0_TX(*s++);
}

void UART0_TX(unsigned char c){
while(((U0LSR >> 5) & 1) == 0);
U0THR = c;
}

unsigned char UART0_RX(void){
while((U0LSR & 1) == 0);
return U0RBR;
}
