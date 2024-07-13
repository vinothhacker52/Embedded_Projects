#include <LPC21xx.h>
#include "delay.h"
#include "i2c.h"
#include "i2c_eeprom.h"

#include <string.h>


//#define I2C_EEPROM_SA 0x50 //7Bit Slave Addr

#define gLED 1<<17 //P1.16
#define rLED 1<<18 //P1.17

//u8 p[9] __attribute__((at(0x40000040)))="";
	
int main()
{
	 u8 ch;
	 init_i2c();
	 IODIR0=gLED|rLED;
	 i2c_eeprom_write(0X50,0X00,'A');
	 ch=i2c_eeprom_read(0X50,0X00);
	 //i2c_eeprom_page_write(I2C_EEPROM_SA,0x00,"ABCDEFGH",8);
	 //i2c_eeprom_seq_read(I2C_EEPROM_SA,0x00,p,8);
	 delay_ms(100);
	 //if(strcmp(p,"ABCDEFGH")==0)
	 if(ch=='A')
	 {
		 IOCLR0 = gLED;
		 IOSET0 = rLED;
     }		
	 else
     {	 IOSET0 = gLED;
		 IOCLR0=rLED;
     } 
	 while(1);
}
