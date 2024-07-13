typedef unsigned char u8;
typedef signed char   s8;
typedef unsigned short int  u16;
typedef signed short   int  s16;
typedef unsigned int  u32;
typedef signed   int  s32;
typedef float f32;
typedef double f64;

/*defines for clock /baudrate
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define SPCCR_VAL 60
#define SPI_RATE (u8)(PCLK/SPCCR_VAL)
SPCR Bits Setting  */

#define CS 7
#define Mode_0     0x00  // CPOL 0 CPHA 0
#define Mode_1     0x08  // CPOL 0 CPHA 1
#define Mode_2     0x10  // CPOL 1 CPHA 0
#define Mode_3     0x18  // CPOL 1 CPHA 1
#define MSTR_BIT   5     // SPI0 as Master 
#define LSBF_BIT   6     // default MSB first,if set LSB first
#define SPIE_BIT   7     //SPI Interrupt Enable Bit

// SPSR bits
#define SPIF_BIT   7    // Data Transfer Completion Flag
//SPINT bit

#define SPIINTF_BIT 0   //SPI Interrupt Flag Bit
#define SETBIT(WORD,BITPOS)         (WORD|=1<<BITPOS)
#define CLRBIT(WORD,BITPOS)         (WORD&=~(1<<BITPOS))
#define CPLBIT(WORD,BITPOS)         (WORD^=(1<<BITPOS))
#define WRITEBIT(WORD,BITPOS,BIT)   (BIT ? SETBIT(WORD,BITPOS): CLRBIT(WORD,BITPOS))
#define READBIT(WORD,BITPOS)        ((WORD>>BITPOS)&1)
