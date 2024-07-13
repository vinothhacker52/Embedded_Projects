#define SW1    14
#define SW2    15
extern U8 *P;
int flag;
void EXT0_ISR(void)  __irq{
EXTINT = 0X01;
LCD_FINAL_BILL();
delay_s(2);
VICVectAddr = 0;
}
void EXT1_ISR(void)  __irq{
flag = 1;
EXTINT = 0X02;
if(flag == 1){
P = NULL;
LCD_STR_DISPLAY("SCAN THE PRODUCT", "TO REMOVE");
delay_s(1);
while(((P = RFID_SEARCH(pen, book)) != NULL) && flag){
	if((strcmp((char*)pen, (CC*)P)) == 0){
  price -= 10;
  }
  if((strcmp((char*)book, (CC*)P)) == 0){
  price -= 20;
  }	
	LCD_TOTAL_DISPLAY(P, price);
	delay_s(2);
	flag = 0;
  }
}
	VICVectAddr = 0;
}
void SWITCH_INTERRUPT_INIT(void);

void SWITCH_INTERRUPT_INIT(void){
PINSEL1 |= 0X00000001; //EXT0
PINSEL0 |= 0X20000000; //EXT1

VICIntSelect = 0;
VICVectCntl0 = (0X20) | 14;
VICVectCntl1 = (0X20) | 15;
VICVectAddr0 = (int) EXT0_ISR;
VICVectAddr1 = (int) EXT1_ISR;
	
EXTMODE = 0X03;
EXTPOLAR = 0X00;
VICIntEnable = 1<<14 | 1<<15;
}

