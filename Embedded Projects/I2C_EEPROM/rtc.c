/******** DS1307 code ********/
#include <LPC21xx.h>
#include "types.h"
#include "i2c.h"
#include "i2c_eeprom.h"
#include "delay.h"
#include <string.h>
//#include "lcd.c"

int main()
{
	u8 min,sec,hr;
	lcd_init();
	init_i2c(); 
	lcd_cmd(0x80);
	str("RTC:");
	
	while(1)
	{
		 lcd_cmd(0xc0);
		 hr=i2c_eeprom_read(0X68,0X02);
		 lcd_data((hr/16)+48);
		 lcd_data((hr%16)+48);
		 lcd_data(':');
		 min=i2c_eeprom_read(0X68,0X01);
		 lcd_data((min/16)+48);
		 lcd_data((min%16)+48);
		 lcd_data(':');
	   sec=i2c_eeprom_read(0X68,0X00);
		 lcd_data((sec/16)+48);
		 lcd_data((sec%16)+48);
	}
}

