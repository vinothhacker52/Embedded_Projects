#ifndef __BIT_DEFINES_H__
#define __BIT_DEFINES_H__

#define SBIT(WORDVAR,BITPOS)       (WORDVAR|=1<<BITPOS)
#define CBIT(WORDVAR,BITPOS)       (WORDVAR&=~(1<<BITPOS))
#define TBIT(WORDVAR,BITPOS)       (WORDVAR=(WORDVAR^(1<<BITPOS)))
#define WBIT(WORDVAR,BITPOS,BIT)   (BIT ? SBIT(WORDVAR,BITPOS): CBIT(WORDVAR,BITPOS))
#define RBIT(WORDVAR,BITPOS)       ((WORDVAR>>BITPOS)&1)
#define WBYTE(WORDVAR,BITPOS,BYTE) (WORDVAR=((WORDVAR&(~(0xFF<<BITPOS)))|(BYTE<<BITPOS)))
#define RBYTE(WORDVAR,BITPOS,BYTE) (WORDVAR>>BITPOS)&0x000000FF)

#endif