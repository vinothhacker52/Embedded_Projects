#include<lpc21xx.h>
void UART0_INIT(void);
void UART0_TXD(unsigned char);
int main(){
PINSEL0 = 0x00000005;
UART0_INIT();
while(1)
UART0_TXD('A');
}
void UART0_INIT(void){
U0LCR = 0X83;
U0DLL = 97;
U0LCR = 0X03;
}
void UART0_TXD(unsigned char c){
while(((U0LSR >> 5) & 1) == 0);
U0THR = c;
}

