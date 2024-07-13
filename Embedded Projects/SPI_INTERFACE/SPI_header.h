void Init_SPI0(void);
u8 SPI0(u8);
f32 Read_ADC_MCP3204(u8 channelNo);


f32 Read_ADC_MCP3204(u8 channelNo)
{
  u8 hByte,lByte;
  u32 adcVal=0;
  //select/activate chip 
  CLRBIT(IOPIN0,CS);
	//delay_ms(100);
  SPI0(0x06);
  hByte = SPI0(channelNo<<6);
  lByte = SPI0(0x00);
  //de-select/de-activate chp
  SETBIT(IOSET0,CS);
  //delay_ms(100);
  adcVal=((hByte&0x0f)<<8)|lByte;
  return ((adcVal*3.3)/4096);
}


void Init_SPI0(void)

{
	PINSEL0 |=0X00001500;
    //S0SPCCR = SPI_RATE;       // cfg bit clock rate 
    S0SPCCR  = 150;            // to set 100kbps(The SPI rate may be 
	                         //calculated as: PCLK rate / SPI_RATE
                           	//S0SPCCR  = 60;// To set 250kbps
	S0SPCR  = (1<<MSTR_BIT|Mode_3); //spi module in master mode,
                                  //CPOL =1,CCPHA = 1. MSB first
	//SETBIT(IODIR0,CS);
	//SETBIT(IOPIN0,CS);
	IODIR0 = 1<<7;
}


u8 SPI0(u8 data)
{
   u8 stat;
   stat = S0SPSR;    //clear SPIF 
   S0SPDR = data;   // load spi tx reg
   while(READBIT(S0SPSR,SPIF_BIT)==0); // wait for transmission to complete
   return S0SPDR;    // read data from SPI data reg, place into buffer 
}

