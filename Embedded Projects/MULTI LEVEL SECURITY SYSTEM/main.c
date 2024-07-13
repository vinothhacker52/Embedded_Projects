#include<lpc21xx.h>
#include <stdlib.h>
#include "LCD_Header.h"
#include "I2C_Driver.h"
#include "Keypad_Driver.h"
#include "GSM_Header.h"


u8 pwd[5];
u32 usr_pwd;
u32 ran_otp;
u32 usr_otp;
u8 otp_count = 0;
int main(){

while(1){
	  TITLE_DISPLAY();
      I2C_PASSWORD_READ(pwd);
	  ASK_PASSWORD(&usr_pwd);
	  
	    if(atoi((const char*)pwd) == usr_pwd){
        LCD_COMMAND(0X01);
		LCD_STR_DISPLAY("    PASSWORD", "   IS CORRECT");
		delay_s(2);
		GENERATE_OTP(&ran_otp);
		LCD_COMMAND(0X01);
		LCD_STR_DISPLAY("OTP IS GENERATED", "ENTER THE OTP");
		delay_s(2);
		LCD_COMMAND(0X01);
		LCD_INTEGER(ran_otp);

	   	while(otp_count++ < 3)
     	{ 
		ASK_OTP(&usr_otp);
		if(usr_otp == ran_otp){
        LCD_COMMAND(0X01);
		LCD_STR_DISPLAY("OTP IS MATCHED" , "WELCOME HOME");
		MOTOR_ON();
        }
		else{
        LCD_STR_DISPLAY("WRONG OTP", "TRY AGAIN");
		delay_s(2);	
		if(otp_count == 3){
		LCD_COMMAND(0X01);
		LCD_STR_DISPLAY("YOU EXCEEDED", "LIMIT");
		//SEND_ALERT()
		//BUZZER_ON()
	    //DISPLAY_ALERT ON LCD
		}
    }
        }    
}
		
		else{
        LCD_COMMAND(0X01);
		LCD_STR_DISPLAY("    PASSWORD", "  IS INCORRECT");
		delay_s(2);
    }
  }
}

