#include<lpc21xx.h>
#include"timer.c"
#define SW1 14
#define SW2 15
#define SW3 16
#define LED1 17
#define LED2 18
#define LED3 19
int main(){
	IODIR0 = 1<<LED1 | 1<<LED2 | 1<<LED3;
while(1){
  /*if(((IOPIN0 >> SW1) & 1) == 0)
		IOCLR0 = 1<<LED1 | 1<<LED2 | 1<<LED3;
	else 
		IOSET0 = 1<<LED1 | 1<<LED2 | 1<<LED3;
	*/
	
	/*if(((IOPIN0 >> SW1) & 1) == 0){
   IOCLR0 = 1<<LED1;
   }
  else if(((IOPIN0 >> SW2) & 1) == 0){
    IOCLR0 = 1<<LED2;
  }
  else if(((IOPIN0 >> SW3) & 1) == 0){
    IOCLR0 = 1<<LED3;
  }	
	else{
     IOSET0 = 1<<LED1 | 1<<LED2 | 1<<LED3;
  }*/
	
	 if(((IOPIN0 >> SW1) & 1) == 0){
		IOCLR0 = 1<<LED1 | 1<<LED2 | 1<<LED3;
    delay(1);
		IOSET0 =  1<<LED1 | 1<<LED2 | 1<<LED3;
    }
	else 
		IOSET0 = 1<<LED1 | 1<<LED2 | 1<<LED3;
	
}
}
