#include<lpc21xx.h>
typedef int U32;

typedef struct CAN2{
U32 id;
U32 rtr;
U32 dlc;
U32 ByteA;
U32 ByteB;
} CAN_MSG;


void CAN_INIT(){
PINSEL1 |= 0x00014000;	  //SELECTING PIN FUNCTIONALITY
VPBDIV	 = 1;	         //PCLK = 60HZ
C2MOD    = 0X1;	         //CAN TO RESET MODE
AFMR     = 0X2;			// NO ACCEPTANCE FILTER
C2BTR    = 0x001C001D; //B125Kbps @ PLCK=60MHz(BRP=Pclk/bit rate*16)
C2MOD    = 0X0;        //CAN TO NORMAL MODE
}

void CAN_TX(CAN_MSG m){
C2TID1 = m.id;
C2TFI1 = (m.dlc << 16);
if(m.rtr == 0){   //if data frame
  C2TFI1 &= ~(1 << 30);
	C2TDA1  = m.ByteA;
	C2TDB1  = m.ByteB;
}
else{
	C2TFI1 |= (1<<30);
}
C2CMR = (1<<0)|(1<<5);
while((C2GSR&(1<<3))==0);
}

void CAN_RX(CAN_MSG *m){
	while((C2GSR & 1) == 0);
	m->id  = C2RID;
	m->dlc = (C2RFS >> 16) & 0xf;
	m->rtr = (C2RFS >> 30) & 1;
	if(m->rtr == 0){
	m->ByteA = C2RDA;
	m->ByteB = C2RDB;
}
	C2CMR = (1 << 2);
}
