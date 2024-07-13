#include <LPC21xx.h>
#include "spi_defines.h"
#include "SPI_header.h"
#include "lcd.h"

main()
{
	f32 f;
	Init_SPI0(); //hw SPI initialisation
	lcd_init();	
	str("MCP3204--");
	IOPIN0 |= 1<<7;
  while(1)
  {
   f=Read_ADC_MCP3204(0);
   lcd_cmd(0xc0);
   Float_display(f);
	}	
}
