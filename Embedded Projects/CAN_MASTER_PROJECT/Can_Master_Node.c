#include "Can_Driver.h"
#include "LCD.h"

#define SW1 14
#define SW2 15
#define SW3 16


U32 READ_SWITCH(void);
void SWITCH_INIT(void);
void LEFT_Indicator(void);
void RIGHT_Indicator(void);
void WIPER_On(void);

CAN_MSG LEFT_Ind;
CAN_MSG RIGHT_Ind;
CAN_MSG WIPER;


int main() {
    U32 keyPress = 0;
    LCD_INIT();
	  TITLE_DISPLAY();
    while (1) {
			  SWITCH_INIT();
        keyPress = READ_SWITCH();
			  CAN_INIT();
        LCD_COMMAND(0x01);
        switch(keyPress){
				case 1:
					LEFT_Indicator();
				  break;
				case 2:
					RIGHT_Indicator();
				  break;
				case 3:
					WIPER_On();
				  break;
				default:
					LCD_STR("INVALID KEY");
				  break;
				}
        delay_ms(1000);
    }
}

void LEFT_Indicator(void){

	 LCD_INIT();
	 LCD_STR_DISPLAY("LEFT INDICATOR", "    <-");
   LEFT_Ind.id = 1;
	 LEFT_Ind.rtr = 0;
	 LEFT_Ind.dlc = 4;
	 LEFT_Ind.ByteA = 1;
	 LEFT_Ind.ByteB = 0;
	 CAN_TX(LEFT_Ind);


}
void RIGHT_Indicator(void){

	 LCD_INIT();
	 LCD_STR_DISPLAY("RIGHT INDICATOR", "    ->");
   RIGHT_Ind.id = 2;
	 RIGHT_Ind.rtr = 0;
	 RIGHT_Ind.dlc = 4;
	 RIGHT_Ind.ByteA = 2;
	 RIGHT_Ind.ByteB = 0;
	 CAN_TX(RIGHT_Ind);

}
void WIPER_On(void){

	 LCD_INIT();
	 LCD_STR_DISPLAY("    WIPER ", "    |/");
   WIPER.id = 3;
	 WIPER.rtr = 0;
	 WIPER.dlc = 4;
	 WIPER.ByteA = 3;
	 WIPER.ByteB = 0;
	 CAN_TX(WIPER);

}

U32 READ_SWITCH(void) {
    U32 switchNo;
    
    while (((IOPIN0 >> SW1) & 1) && ((IOPIN0 >> SW2) & 1) && ((IOPIN0 >> SW3) & 1));
    
    if (((IOPIN0 >> SW1) & 1) == 0) {
        switchNo = 1;
        delay_ms(300);
    } else if (((IOPIN0 >> SW2) & 1) == 0) {
        switchNo = 2;
        delay_ms(300);
    } else {
        switchNo = 3;
        delay_ms(300);
    }

    while (((IOPIN0 >> SW1) & 1 == 0) || ((IOPIN0 >> SW2) & 1 == 0) || ((IOPIN0 >> SW3) & 1 == 0));
    
    return switchNo;
}

void SWITCH_INIT(void){
    PINSEL1 = 0X00000000;
}

