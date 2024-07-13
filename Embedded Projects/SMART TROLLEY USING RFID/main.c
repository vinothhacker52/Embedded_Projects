#include"LCD_Header.h"
#include"UART0_Header.h"
#include"EXT_INT.h"
#include<string.h>
typedef unsigned char U8;
U8 *pen = "03063646";
U8 *book = "03115952";
int price = 0;
U8 *P = NULL;
int main(){
	UART0_INIT();
	SWITCH_INTERRUPT_INIT();
	TITLE_DISPLAY();
	
	while(1){
	while((P = RFID_SEARCH(pen, book)) != NULL){
	if((strcmp((char*)pen, (CC*)P)) == 0){
  price += 10;
  }
  if((strcmp((char*)book, (CC*)P)) == 0){
  price += 20;
  }	
	LCD_TOTAL_DISPLAY(P, price);
	delay_s(2);
	P = NULL;
  }	
}

}

