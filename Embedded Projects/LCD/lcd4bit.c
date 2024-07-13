#include<lpc21xx.h>
#define lcdd 0xf0<<16
#define rs 1<<17
#define rw 1<<18
#define E 1<<19
typedef unsigned char U8;
void delaym(int msec);
void lcdcmd(U8);
void lcddata(U8);
void lcdconf(void);
void lcdstring(char*);
void meter(void);
void cg(U8);
void lcdint(int);
void lcdfloat(float);
U8 cgram[]={0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x00,
						0x00,0x00,0x00,0x00,0x00,0x1f,0x1f,0x00,
						0x00,0x00,0x00,0X00,0x1F,0x1f,0x1f,0x00,
						0x00,0x00,0x00,0x1F,0x1F,0x1f,0x1f,0x00,
						0x00,0x00,0x1F,0x1F,0x1F,0x1f,0x1f,0x00,
						0x00,0x1f,0x1F,0x1F,0x1F,0x1f,0x1f,0x00,
						0x1f,0x1F,0x1F,0x1F,0x1F,0x1f,0x1f,0x00};
void meter(void)
{
	int i=0;
	lcdconf();
	cg(56);
	while(1)
	{
	IOPIN1=(IOPIN1&0XFF00FFFF);
	lcdcmd(0xc0);
	lcddata('E');
	lcdcmd(0xc7);
	lcddata('F');
	lcdcmd(0x80);
	while(i<7)
	{
		lcddata(i++);
		delaym(500);
	}
	lcdcmd(0x01);
			}
		}
void lcdconf(void)
{
	IODIR1=lcdd|rs|rw|E;
	lcdcmd(0x01);
	lcdcmd(0x02);
	lcdcmd(0x0c);
	lcdcmd(0x28);
	lcdcmd(0x80);
}
void lcdcmd(U8 n)
{
	IOPIN1=(IOPIN1&0XFF00FFFF)|((n&0XF0)<<16);
	IOCLR1=rs;
	IOCLR1=rw;
	IOSET1=E;
	delaym(2);
	IOCLR1=E;                                                           
	delaym(2);
	IOPIN1=(IOPIN1&0XFF00FFFF)|(n&0X0F)<<20;
	IOCLR1=rs;
	IOCLR1=rw;
	IOSET1=E;
	delaym(2);
	IOCLR1=E; 
	}
void lcddata(U8 n)
{
	IOPIN1=(IOPIN1&0XFF00FFFF)|(n&0XF0)<<16;
	IOSET1=rs;
	IOCLR1=rw;
	IOSET1=E;
	delaym(2);
	IOCLR1=E;
	delaym(2);
	IOPIN1=(IOPIN1&0XFF00FFFF)|(n&0X0f)<<20;
	IOSET1=rs;
	IOCLR1=rw;
	IOSET1=E;
	delaym(2);
	IOCLR1=E;
}

void delaym(int msec)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<msec);
	T0TCR=0X03;
	T0TCR=0X02;
}
void lcdstring(char* S)
{
	U8 i;
	for(i=0; S[i]; i++)
	lcddata(S[i]);
}

void cg(U8 n)
{
	int i;
	lcdcmd(0x40);
	for(i=0; i<n; i++)
	{
		lcddata(cgram[i]);
	}
}
void lcdint(int n)
{
	int i,a[10];
	if(n==0)
		lcddata('0');
	else
	{
		if(n<0)
		{
			lcddata('-');
			n=-n;
		}
		for(i=0; n!=0; n=n/10,i++)
		a[i]=n%10;
		for(i--; i>=0; i--)
		lcddata(a[i]+48);
	}
}
void lcdfloat(float f)
{
	int x=f;
	lcdint(x);
	lcddata('.');
	f=(f-x)*1000;
	lcdint(f);
}
