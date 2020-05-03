#define assert(__e) ((void)0)
#include <stdint.h>
#include <stdlib.h>

void *
memcpy (void *dest, const void *src, size_t len)
{
  char *d = dest;
  const char *s = src;
  while (len--)
    *d++ = *s++;
  return dest;
}
int
memcmp (const void *str1, const void *str2, size_t count)
{
  const unsigned char *s1 = str1;
  const unsigned char *s2 = str2;

  while (count-- > 0)
    {
      if (*s1++ != *s2++)
	  return s1[-1] < s2[-1] ? -1 : 1;
    }
  return 0;
}
void *
memset (void *dest, int val, size_t len)
{
  unsigned char *ptr = dest;
  while (len-- > 0)
    *ptr++ = val;
  return dest;
}


#include "murax.h"
#include "drysponge.h"
//#include "bytes_utils.h"

void nibble_to_hexstr(uint8_t*str,unsigned int n){
	n = n & 0xF;
	if(n<10) str[0] = '0'+n;
	else str[0] = 'A'-10+n;
}
void u8_to_hexstr(uint8_t*str,uint8_t b){
	nibble_to_hexstr(str,b>>4);
	nibble_to_hexstr(str+1,b);
}
void bin_to_hexstr(uint8_t*str,const uint8_t *const buf, size_t len){
	for(size_t i=0;i<len;i++){
		u8_to_hexstr(str+2*i,buf[i]);
	}
}
void u32_to_hexstr(uint8_t*str,uint32_t b){
	u8_to_hexstr(str+0,b>>24);
	u8_to_hexstr(str+2,b>>16);
	u8_to_hexstr(str+4,b>> 8);
	u8_to_hexstr(str+6,b);
}

static void uart_read(Uart_Reg *reg, uint8_t *data){
	while(uart_readOccupancy(reg) == 0);
	*data = reg->DATA;
}

uint32_t min_time=0xFFFFFFFF;
uint32_t max_time=0;
uint64_t io[96/8]= {0};
void benchmark(void (*fun_ptr)(void)){
	for(unsigned int i = 0;i<16;i++){
		//__disable_irq();
		TIMER_A->VALUE=0;
		uint32_t start = TIMER_A->VALUE;
		uint32_t end = TIMER_A->VALUE;
		const uint32_t overhead=end-start;
		memset(io,0,sizeof(io));
		TIMER_A->VALUE=0;
		start = TIMER_A->VALUE;
		fun_ptr();
		end = TIMER_A->VALUE;
		//__enable_irq();
		uint32_t exec_time = (end-start)-overhead;
		if(exec_time<min_time) min_time = exec_time;
		if(exec_time>max_time) max_time = exec_time;
	}
}

size_t clen;

uint64_t drygascon128_state[5+4+2];
uint8_t *drygascon128_state8 = (uint8_t*)drygascon128_state;
uint32_t*drygascon128_state32 = (uint32_t*)drygascon128_state;

void drygascon128_g(uint64_t* x, unsigned int rounds);
void drygascon128_f(uint64_t* x, const uint32_t*const in, uint32_t ds, unsigned int rounds);

const uint8_t drygascon128_key_state[]={//c r x
	0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,0x13,0x19,0x8A,0x2E,0x03,0x70,0x73,0x44,0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,0x13,0x19,0x8A,0x2E,0x03,0x70,0x73,0x44,0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,
	0xE0,0xC2,0xC2,0x97,0x2E,0x2E,0xAB,0x02,0xA6,0x0B,0xAD,0x89,0xE2,0xDF,0xFE,0xD1,//nonce in place of r
	0xA4,0x09,0x38,0x22,0x29,0x9F,0x31,0xD0,0x08,0x2E,0xFA,0x98,0xEC,0x4E,0x6C,0x89,
	};

const uint8_t drygascon128_key[]={//c r x
	0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,0x13,0x19,0x8A,0x2E,0x03,0x70,0x73,0x44,0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,0x13,0x19,0x8A,0x2E,0x03,0x70,0x73,0x44,0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,
	0xA4,0x09,0x38,0x22,0x29,0x9F,0x31,0xD0,0x08,0x2E,0xFA,0x98,0xEC,0x4E,0x6C,0x89,
	};

const uint8_t drygascon128_nonce[]={//c r x
	0xE0,0xC2,0xC2,0x97,0x2E,0x2E,0xAB,0x02,0xA6,0x0B,0xAD,0x89,0xE2,0xDF,0xFE,0xD1,
	};
void drygascon128_benchmark(void){
	//drygascon128_g(drygascon128_state,7);
	//drygascon128_mix128(drygascon128_state,drygascon128_state+DRYSPONGE_CAPACITYSIZE64,0);
	//drygascon128_f(drygascon128_state,(const uint32_t*const)(drygascon128_state+DRYSPONGE_CAPACITYSIZE64),0,7);
	drygascon128hw_f(DRYGASCON128,(uint32_t*const)(drygascon128_state+DRYSPONGE_CAPACITYSIZE64),(const uint32_t*const)(drygascon128_state+DRYSPONGE_CAPACITYSIZE64),0,7);
	//set key
	//DRYSPONGE_enc(drygascon128_key,DRYSPONGE_KEYMAXSIZE,drygascon128_nonce,io,0,0,0,io,&clen);
	/*
	memcpy(drygascon128_state,drygascon128_key,DRYSPONGE_CAPACITYSIZE);
	unsigned int ds=DRYSPONGE_DSINFO(0, DRYSPONGE_DD, 0);
	//process nonce
	drygascon128_f(drygascon128_state,(uint32_t*)(drygascon128_key+DRYSPONGE_CAPACITYSIZE),ds,11);
	ds=0;
	//process nblocks
	unsigned int nblocks = 5;
	for(unsigned int i=0;i<nblocks;i++){
		uint64_t *r = drygascon128_state+DRYSPONGE_CAPACITYSIZE64;
		uint64_t *p = io+i*2;
		uint64_t *c = p;
		DRYSPONGE_xor64(r,p,c);

		if(i+1==nblocks) ds = DRYSPONGE_DSINFO(0, DRYSPONGE_DM, 1);
		drygascon128_f(drygascon128_state,(uint32_t*)(io+(i+1)*2),ds,7);
	}
	memcpy(io+nblocks*2,drygascon128_state+DRYSPONGE_CAPACITYSIZE64,DRYSPONGE_BLOCKSIZE);*/
}
const uint8_t drygascon128_benchmark5_expected[] = {0x44,0x14,0x80,0x5A,0xCC,0x22,0xCD,0xC1,0xDA,0x2D,0xAA,0xD4,0x05,0x4F,0xBE,0x1F,0x9D,0x8B,0x9E,0xD1,0x5D,0xB0,0xDA,0xAB,0x2C,0xCC,0x5F,0xB0,0xF0,0x27,0x1A,0xF7,0x30,0x7C,0x0E,0xB6,0x52,0x7E,0x40,0x13,0xBE,0xE1,0x4D,0xB8,0xD3,0x84,0x58,0xDB,0xE8,0xC1,0x3C,0x2C,0x65,0x08,0x15,0xA3,0x8C,0x6E,0xED,0xCF,0x51,0x47,0x13,0x05,0xAC,0x15,0x79,0x5F,0x6C,0xDC,0xAB,0xF9,0x0F,0x79,0x82,0x51,0x6C,0xD8,0x91,0xE6,0x80,0x4A,0x41,0xD5,0x12,0x17,0x89,0x87,0xB5,0x07,0xDD,0xC2,0x63,0xFE,0x49,0x5E};


static void drygascon128_g_ref(uint64_t* x, unsigned int rounds) {
    uint64_t t[5];
    for(unsigned int j=0;j<rounds;j++){
    	gascon_permutation_round(x, j);
    	uint32_t*r32 = (uint32_t*)(x+DRYSPONGE_CAPACITYSIZE64);
		for(unsigned int k=0;k<DRYSPONGE_ACCUMULATE_FACTOR;k++){
			uint32_t *cpart = ((uint32_t*)x)+k*DRYSPONGE_BLOCKSIZE32;
			for(unsigned int i=0;i<DRYSPONGE_BLOCKSIZE32;i++){
				r32[i]^=cpart[(i+k)%DRYSPONGE_BLOCKSIZE32];
			}
		}
    }
}

//#define DRYSPONGE_REF
#define DRYSPONGE_HW
void test_drygascon128_g(void){
	const uint8_t s[]={//c r x
	0x82,0x51,0x8E,0xD0,0x15,0x2D,0x17,0xA0,0x72,0xBB,0x94,0x1E,0x48,0xA9,0x0F,0x17,
	0x4D,0xFF,0x6B,0xD6,0xA9,0xBA,0xE4,0x4C,0x19,0xA1,0xB5,0x6D,0xFA,0x9B,0x82,0x72,
	0xC3,0x37,0x7D,0xD6,0x7C,0xC7,0x1C,0x86,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xA4,0x09,0x38,0x22,0x29,0x9F,0x31,0xD0,0x08,0x2E,0xFA,0x98,0xEC,0x4E,0x6C,0x89
	};
	const uint8_t expected[] = {
	0x34,0x46,0x16,0xA2,0xDC,0x4B,0x29,0xB8,0xE1,0xF7,0x5F,0x43,0xB1,0x38,0xAC,0x80,
	0x16,0x73,0xD4,0xA1,0x62,0x06,0x66,0xC2,0xAC,0x3D,0x27,0x71,0xA2,0xBD,0x48,0x04,
	0xED,0x99,0x8E,0xAB,0xD7,0x1F,0x84,0x92,
	0xCD,0xE2,0xDE,0xE0,0x23,0x53,0x45,0xCB,0xFA,0x51,0xEC,0x2C,0xE5,0x74,0x35,0x71,
	0xA4,0x09,0x38,0x22,0x29,0x9F,0x31,0xD0,0x08,0x2E,0xFA,0x98,0xEC,0x4E,0x6C,0x89
	};
	memcpy(drygascon128_state,s,sizeof(s));
#ifdef DRYSPONGE_REF
	drygascon128_g_ref(drygascon128_state,7);
#else
#ifdef DRYSPONGE_HW
	drygascon128hw_set_c(DRYGASCON128,drygascon128_state32);
	drygascon128hw_set_x(DRYGASCON128,drygascon128_state32+10+4);
	drygascon128hw_g(DRYGASCON128,drygascon128_state32+10,7);
	drygascon128hw_get_c(DRYGASCON128,drygascon128_state32);
#else
	drygascon128_g(drygascon128_state,7);
#endif
#endif
	if( memcmp(drygascon128_state,expected,DRYSPONGE_CAPACITYSIZE+DRYSPONGE_BLOCKSIZE)){
        while(1);
    }
}

void test_drygascon128_f(void){
	const uint8_t s[]={//c r x
	0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,0x13,0x19,0x8A,0x2E,0x03,0x70,0x73,0x44,0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,0x13,0x19,0x8A,0x2E,0x03,0x70,0x73,0x44,0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xA4,0x09,0x38,0x22,0x29,0x9F,0x31,0xD0,0x08,0x2E,0xFA,0x98,0xEC,0x4E,0x6C,0x89,
	};
    const uint8_t in[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint32_t ds = 0xb;
    const uint8_t expected[] = {
    	0x34,0x46,0x16,0xA2,0xDC,0x4B,0x29,0xB8,0xE1,0xF7,0x5F,0x43,0xB1,0x38,0xAC,0x80,0x16,0x73,0xD4,0xA1,0x62,0x06,0x66,0xC2,0xAC,0x3D,0x27,0x71,0xA2,0xBD,0x48,0x04,0xED,0x99,0x8E,0xAB,0xD7,0x1F,0x84,0x92,
    	0xCD,0xE2,0xDE,0xE0,0x23,0x53,0x45,0xCB,0xFA,0x51,0xEC,0x2C,0xE5,0x74,0x35,0x71,
    	0xA4,0x09,0x38,0x22,0x29,0x9F,0x31,0xD0,0x08,0x2E,0xFA,0x98,0xEC,0x4E,0x6C,0x89
    	};
	memcpy(drygascon128_state,s,sizeof(s));
#ifdef DRYSPONGE_REF
	DRYSPONGE_t ctx;
	ctx.ext = ds;
	ctx.ext = ctx.ext<<((DRYSPONGE_BLOCKSIZE*8)%DRYSPONGE_MPR_INPUT_WIDTH);
	ctx.rounds=7;
	memcpy(ctx.c,drygascon128_state,DRYSPONGE_CAPACITYSIZE);
	memcpy(ctx.x,drygascon128_state+DRYSPONGE_CAPACITYSIZE64+DRYSPONGE_BLOCKSIZE64,16);
	DRYSPONGE_f(&ctx,in);
	memcpy(drygascon128_state,ctx.c,DRYSPONGE_CAPACITYSIZE);
#else
#ifdef DRYSPONGE_HW
	drygascon128hw_set_c(DRYGASCON128,drygascon128_state32);
	drygascon128hw_set_x(DRYGASCON128,drygascon128_state32+10+4);
	drygascon128hw_set_io(DRYGASCON128,drygascon128_state32+10);
	drygascon128hw_f(DRYGASCON128,drygascon128_state32+10,(const uint32_t*const)in,ds,7);
	drygascon128hw_get_c(DRYGASCON128,drygascon128_state32);
#else
	drygascon128_f(drygascon128_state,(const uint32_t*const)in,ds,7);
#endif
#endif
	if( memcmp(drygascon128_state,expected,DRYSPONGE_CAPACITYSIZE)){
        while(1);
    }
}

void main() {
	volatile uint32_t a = 1, b = 2, c = 3;
	uint32_t result = 0;
	uint32_t t0,t1,tref;
	char buf[10] = {0};

	interruptCtrl_init(TIMER_INTERRUPT);
	prescaler_init(TIMER_PRESCALER);
	timer_init(TIMER_A);

	TIMER_PRESCALER->LIMIT = 0;

	TIMER_A->LIMIT = 0xFFFFFFFF;
	TIMER_A->CLEARS_TICKS = 1;//bypass prescaler, no auto-clear

	GPIO_A->OUTPUT_ENABLE = 0x000000FF;
	GPIO_A->OUTPUT = 0x000000F0;

	UART->DATA = 'B';
	uint32_t res = drygascon128hw_test_ctrl(DRYGASCON128);
	u32_to_hexstr(buf,res);
	for(unsigned int i=0;i<8;i++){
		uart_write(UART,buf[i]);
	}
	uart_write(UART,'\n');
	test_drygascon128_g();
	test_drygascon128_f();
	uart_write(UART,'\n');
	uart_write(UART,'O');
	uart_write(UART,'K');
	uart_write(UART,'\n');

	for(unsigned int i=0;i<3;i++){
		GPIO_A->OUTPUT = ((GPIO_A->OUTPUT + 1) & 0xFF);  //Counter on LED[7:0]
		a++;

		min_time=0xFFFFFFFF;
		max_time=0;
		benchmark(drygascon128_benchmark);
		u32_to_hexstr(buf,min_time);
		for(unsigned int i=0;i<8;i++){
			uart_write(UART,buf[i]);
		}
		uart_write(UART,' ');
		u32_to_hexstr(buf,max_time);
		for(unsigned int i=0;i<8;i++){
			uart_write(UART,buf[i]);
		}
		uart_write(UART,'\n');
	}

	while(1){//attack target loop: c and x fixed (and assumed to be secret), attacker control/observe i and r of F function (7 rounds)
		const uint8_t s[]={//c r x
			0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,0x13,0x19,0x8A,0x2E,0x03,0x70,0x73,0x44,0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,0x13,0x19,0x8A,0x2E,0x03,0x70,0x73,0x44,0x24,0x3F,0x6A,0x88,0x85,0xA3,0x08,0xD3,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0xA4,0x09,0x38,0x22,0x29,0x9F,0x31,0xD0,0x08,0x2E,0xFA,0x98,0xEC,0x4E,0x6C,0x89,
			};
		memcpy(drygascon128_state,s,sizeof(s));
		for(unsigned int i=0;i<16;i++){
			uart_read(UART,drygascon128_state8+40+i);
			GPIO_A->OUTPUT = ((GPIO_A->OUTPUT + 1) & 0xFF);  //Counter on LED[7:0]
			a++;
		}
		uint8_t ds=0;
		uart_read(UART,&ds);
		GPIO_A->OUTPUT = ((GPIO_A->OUTPUT + 1) & 0xFF);  //Counter on LED[7:0]
		a++;
		drygascon128hw_set_c(DRYGASCON128,drygascon128_state32);
		drygascon128hw_set_x(DRYGASCON128,drygascon128_state32+10+4);
		drygascon128hw_set_io(DRYGASCON128,drygascon128_state32+10);
        if(ds & 0xF0){
			//invalid domain separator, go to transmission less mode
			break;
		}
		drygascon128hw_f(DRYGASCON128,drygascon128_state32+10,drygascon128_state32+10,ds,7);
		drygascon128hw_get_c(DRYGASCON128,drygascon128_state32);
		for(unsigned int i=0;i<16;i++){
			uart_write(UART,drygascon128_state8[40+i]);
		}
	}
	uint32_t leds=0;
	while(1){//transmission less attack loop: next input = F(input) (DS=0, rounds=7)
		//initial condition: default state, ds=0, input=0
		GPIO_A->OUTPUT = 1|((leds>>6) & 0xFF);//force lsb to 1 to have clean trigger
		drygascon128hw_f(DRYGASCON128,drygascon128_state32+10,drygascon128_state32+10,0,7);
		GPIO_A->OUTPUT = 0;
		leds++;
	}
}

void irqCallback(){
}
