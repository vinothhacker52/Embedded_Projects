#define SW1 14
#define  MOTOR_POSITIVE	   1 << 20
#define  MOTOR_NEGATIVE	   1 << 21

void GENERATE_OTP(u32 *r_num){
	  *r_num = 1000;
	  while(*r_num < 10000){
	  if((IOPIN0 >> SW1 & 1) == 1)
	  break;
	  if(*r_num == 9999)
	  *r_num = 1000;
	  }
}
				  
void MOTOR_ON(){
	  LCD_COMMAND(0X01);
	  LCD_STR("DOOR IS OPENED");
	  IODIR0 |= MOTOR_POSITIVE | MOTOR_NEGATIVE;

	  IOSET0 = MOTOR_POSITIVE;
	  IOCLR0 = MOTOR_NEGATIVE;
	  delay_s(3);
	  IOSET0 = MOTOR_NEGATIVE;
	  IOCLR0 = MOTOR_POSITIVE;
    
	  IOSET0 = MOTOR_NEGATIVE;
	  IOSET0 = MOTOR_POSITIVE;
	  LCD_COMMAND(0X01);
	  LCD_STR("DOOR IS CLOSED");
}
