 #include<lpc21xx.h>
 #define LED0 1<<16
 #define LED1 1<<17
 #define SW 14
 int flag = 0;
 void LED_Interrupt(void) __irq{
 T0IR = 0x01;
 if(flag == 0){
 IOCLR0 = LED0;
 flag = 1;
 }
 else{
 IOSET0 = LED0;
 flag = 0;
 }
 VICVectAddr = 0;
 }
 int main(){
 IODIR0 = LED0 | LED1;

 VICIntSelect = 0;
 VICVectCntl0 = (0x20) | 4;
 VICVectAddr0 = (int)LED_Interrupt;
 T0MCR = 0x03;
 T0MR0 = 7500000-1;

 VICIntEnable = 1<<4;
 T0TCR = 0x01;
 while(1){
 if(((IOPIN0 >> SW)&1) == 0)
 	IOCLR0 = LED1;
 else
    IOSET0 = LED1;
 }
 }
