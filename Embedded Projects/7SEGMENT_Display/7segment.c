#include<LPC21xx.h>
#include"E:\v23ce6v2\Embedded Projects\7SEGMENT_Display\delay.h"
#define SEG_D 0xff
#define SEG_1 1<<8
#define SEG_2 1<<9
#define SEG_3 1<<10
#define SEG_4 1<<11
void TWO_DIGIT_INTEGER(int);
void FOUR_DIGIT_INTEGER(int);
void FLOAT_DISPLAY(float);
void TWO_DIGIT_TIMER(void);
void FOUR_DIGIT_TIMER(void);
void TWO_DIGIT_INTEGER_HELPER(int, int);
void FOUR_DIGIT_INT(int);
void FOUR_D_TIMER(void);

unsigned char num[]	= {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
int dp1=0,dp2 = 0,dp3=0,dp4=0;

int main() {
while(1){
FOUR_D_TIMER(); 
}
}



void FOUR_DIGIT_TIMER(){
unsigned char i,j;
for(i = 0; i < 60; i++){
    TWO_DIGIT_INTEGER_HELPER(i,0);
	for(j = 0; j < 60; j++){
		TWO_DIGIT_INTEGER_HELPER(i,j);
        }
    }
}

void FOUR_D_TIMER(void){
unsigned char i,j,k;
dp2 = 0x80;
for(i = 0; i < 60; i++){
    for(j = 0; j < 60; j++){
	   for(k = 0; k < 50; k++){
	   FOUR_DIGIT_INTEGER(i * 100 + j);
	   }
	}
  }
}

void TWO_DIGIT_TIMER(void){
unsigned char i = 0;
while(i < 60){
TWO_DIGIT_INTEGER_HELPER(0,i++);
	}
}

void TWO_DIGIT_INTEGER_HELPER(int n1,int n2){
char j;
for(j = 0; j < 50; j++){
dp2 = 0x80;
IODIR0 = SEG_D | SEG_1 | SEG_2 | SEG_3 | SEG_4;
IOCLR0 = SEG_D;
IOSET0 = num[n1/10];
IOCLR0 = SEG_1;
delay(5);
IOSET0 = SEG_1;

IOCLR0 = SEG_D;
IOSET0 = num[n1%10] ^ dp2;
IOCLR0 = SEG_2;
delay(5);
IOSET0 = SEG_2;


IODIR0 = SEG_D | SEG_1 | SEG_2 | SEG_3 | SEG_4;
IOCLR0 = SEG_D;
IOSET0 = num[n2/10];
IOCLR0 = SEG_3;
delay(5);
IOSET0 = SEG_3;

IOCLR0 = SEG_D;
IOSET0 = num[n2%10];
IOCLR0 = SEG_4;
delay(5);
IOSET0 = SEG_4;
	}
}

void TWO_DIGIT_INTEGER(int n){
IODIR0 = SEG_D | SEG_1 | SEG_2;
IOCLR0 = SEG_D;
IOSET0 = num[n/10];
IOCLR0 = SEG_1;
delay(5);
IOSET0 = SEG_1;

IOCLR0 = SEG_D;
IOSET0 = num[n%10];
IOCLR0 = SEG_2;
delay(5);
IOSET0 = SEG_2;
}


void FOUR_DIGIT_INT(int n){
int i;
unsigned char j = 3;
int arr[] = {SEG_1, SEG_2, SEG_3, SEG_4};
IODIR0 = SEG_D | SEG_1 | SEG_2 | SEG_3 | SEG_4;
for(i = n; i > 0; i /= 10){
IOCLR0 = SEG_D;
IOSET0 = num[i % 10];
IOCLR0 = arr[j];
delay(5);
IOSET0 = arr[j--];
   }
}

void FOUR_DIGIT_INTEGER(int n){
IODIR0 = SEG_D | SEG_1 | SEG_2 | SEG_3 | SEG_4;

IOCLR0 = SEG_D;
IOSET0 = num[n/1000] ^ dp1;
IOCLR0 = SEG_1;
delay(5);
IOSET0 = SEG_1;

IOCLR0 = SEG_D;
IOSET0 = num[(n/100) % 10] ^ dp2;
IOCLR0 = SEG_2;
delay(5);
IOSET0 = SEG_2;

IOCLR0 = SEG_D;
IOSET0 = num[(n/10) % 10] ^ dp3;
IOCLR0 = SEG_3;
delay(5);
IOSET0 = SEG_3;

IOCLR0 = SEG_D;
IOSET0 = num[n%10] ^ dp4;
IOCLR0 = SEG_4;
delay(5);
IOSET0 = SEG_4;
}

void FLOAT_DISPLAY(float f){
int t;
IODIR0 = SEG_D | SEG_1 | SEG_2 | SEG_3 | SEG_4;
if(f < 10.0){
dp1 = 0x80;
t = f * 1000;
	}
else if(f > 10.0 && f < 100.0){
dp2 = 0x80;
t = f * 100;
	}
else if(f > 100.0 && f < 1000.0){
dp3 = 0x80;
t = f * 10; 
	}
else{
dp4 = 0x80;
t = f;
	}
FOUR_DIGIT_INTEGER(t);
}







