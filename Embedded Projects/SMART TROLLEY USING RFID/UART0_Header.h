#include <lpc21xx.h>
typedef unsigned char U8;
typedef const char CC;
void UART0_INIT(void);
void UART0_TX(U8);
U8 UART0_RX(void);
void UART0_STR(U8*);
U8* RFID_SEARCH(U8 *, U8 *);

U8* RFID_SEARCH(U8 *p1, U8 *p2) {
    U8 current_product[9] = {0};  
	  char i,j;
	  LCD_STR_DISPLAY("   Product is ", " Being  Scanned");
    while(1) {
	  for(i=0,j=0;i<9;i++)
		{
			if(j==0)
			{
				UART0_RX();
				j++;
			}
			current_product[i]=UART0_RX();
		}
    current_product[--i] = '\0'; 
	 if((strcmp((char*) p1,(CC*) current_product)) == 0){
   return p1;
   }
	 if((strcmp((char*) p2, (CC*) current_product)) == 0){
   return p2;
   }
   } 
}

void UART0_INIT() {
    PINSEL0 |= 0X00000005;
    U0LCR = 0X83;
    U0DLL = 97;
    U0LCR = 0X03;
}

void UART0_TX(U8 C) {
    while (((U0LSR >> 5) & 1) == 0);
    U0THR = C;
}

U8 UART0_RX(void) {
    while ((U0LSR & 1) == 0);
    return U0RBR;
}

void UART0_STR(U8* p) {
    while (*p) {
        UART0_TX(*p++);
    }
}
