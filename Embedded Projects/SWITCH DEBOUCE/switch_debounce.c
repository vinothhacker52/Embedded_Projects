#include<lpc21xx.h>
#include "E:\V23CE6V2\EMBEDDED PROJECTS\LCD\lcdheader.h"
#define SW 15

int main(){
	int count = 0;
	LCD_INIT();
	LCD_STR("SWITCH COUNT :");
    while(1){
 	if(((IOPIN0 >> SW) & 1) == 0){
	delay(250);
	count++;
	LCD_COMMAND(0xC0);
	LCD_INTEGER(count);
	while(((IOPIN0 >> SW) & 1)== 0);
	}
  }
}
