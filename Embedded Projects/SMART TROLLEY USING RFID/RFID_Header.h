#include"UART0_Header.h"
void EM4095_Configure(void);

void EM4095_Configure() {
	  UART0_INIT();
    UART0_STR("SC modulation_freq=125kHz gain=high filters=enabled\r\n");
	
}
