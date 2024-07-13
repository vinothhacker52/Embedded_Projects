#define C0 (IOPIN0 & (1 << 10))
#define C1 (IOPIN0 & (1 << 11))
#define C2 (IOPIN0 & (1 << 12))
#define C3 (IOPIN0 & (1 << 13))

#define R0 (IOPIN0 & (1 << 14))
#define R1 (IOPIN0 & (1 << 15))
#define R2 (IOPIN0 & (1 << 16))
#define R3 (IOPIN0 & (1 << 17))

u32 key_lut[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

u32 key_scan(void){
	u8 row_val, col_val;
	PINSEL0 |= 0x00000000;
	IODIR0 |= R0|R1|R2|R3;
	while(1){
  IOCLR0 = R0|R1|R2|R3;
	IOSET0 = C0|C1|C2|C3;
	while((C0 && C1 && C2 && C3) == 1);
	
	IOCLR0 = R0;
	IOSET0 = R1 | R2 | R3;
	if((C0 && C1 && C2 && C3) == 0){
  row_val = 0;
	break;
  }
  
	IOCLR0 = R1;
	IOSET0 = R0 | R2 | R3;
	if((C0 && C1 && C2 && C3) == 0){
  row_val = 1;
	break;
  }
	
	IOCLR0 = R2;
	IOSET0 = R0 | R1 | R3;
	if((C0 && C1 && C2 && C3) == 0){
  row_val = 2;
	break;
  }
	
	IOCLR0 = R3;
	IOSET0 = R0 | R1 | R2;
	if((C0 && C1 && C2 && C3) == 0){
  row_val = 3;
	break;
  }
  }
	if(C0 == 0)
		col_val = 0;
	else if(C1 == 0)
		col_val = 1;
	else if(C2 == 0)
		col_val = 2;
	else
		col_val = 3;
	
	return key_lut[row_val][col_val];
}

u32 ASK_PASSWORD(u32 *pwd){
	 u8 i;
	 LCD_COMMAND(0X01);
   LCD_STR_DISPLAY("ENTER THE PWD", "");
	 for(i = 0; i < 4; i++){
			 LCD_COMMAND(0XC0);
		   *pwd = ((*pwd) * 10) + key_scan();
		   LCD_INTEGER(*pwd);
   }
	 return *pwd;
}

u32 ASK_OTP(u32 *pwd){
	 u8 i;
	 LCD_COMMAND(0X01);
   LCD_STR_DISPLAY("ENTER THE OTP", "");
	 LCD_COMMAND(0XC0);
	 for(i = 0; i < 4; i++){
		   *pwd = ((*pwd) * 10) + key_scan();
		   LCD_DATA('*');
   }
	 return *pwd;
}

