//#ifndef __TINY__
//#define __TINY__
//#endif
#include "start.h"
#include "hello7.h"
#include "embisr.h"

#define PROG_PU_M_MUX //101115 for test

/* port

	  

#ifndef __TINY__
#define __TINY__
#endif
#include "start.h"
////////////////////////////////////////////
////    ������ ��������� Emb-�������    ////
////////////////////////////////////////////
#define IncEmbRS232
//#define IncEmbRS485
#define IncEmbTimer
//#define IncEmbNMI
//#define IncEmbIndicator
//#define IncEmbSerialACT155
#define IncEmbSerialPU_M
////////////////////////////////////////////
#include "longtoa.cas"
#include "Ltoa1.c"
#include "stdlib.h"
//#include "command.h"
#include "embisr.cpp"
//#include "basic'.h"
//#include "basic'.cpp"


void ResetWatchDog()
{
	outport(wdtcon,0xAAAA);
	outport(wdtcon,0x5555);
	outportb(0x6FB,0x55);
};
 */


 /*
#ifdef USE_RS125
struct STCSR_M
{
unsigned char HEADER;	//1
unsigned char rez; //1 to do not have not divide to 2	   !!!! not have in real message
unsigned long MID;	//4
unsigned long MBS;	 //4 
unsigned long Offset;  //4
unsigned char RETS[REP_MAX_LEN];  //  280
unsigned char MCS;	  //1
};

union USTCSR_M
{
   STCSR_M stcsr_m;
   unsigned char byte[STCS_REP_LEN];
};



struct STCS_M										               
{
unsigned long MID;	//4
unsigned char Rez[6]; //6
unsigned short MBS;	 //2
unsigned long Offset;  //4
unsigned long BTR;	   //4
unsigned char MCS;	  //1
};

union USTCS_M
{
   STCS_M stcs_m;
   unsigned char byte[STCS_MES_LEN];
};

struct KEEP_ST
{
 unsigned long max_oct_res_sub;
 unsigned long min_oct_res_sub;
 unsigned long center_oct_res_sub;
 unsigned long max_oct_tr_sub;
 unsigned long min_oct_tr_sub;
 unsigned long center_oct_tr_sub;
 unsigned long max_oct_res_ser;
 unsigned long min_oct_res_ser;
 unsigned long center_oct_res_ser;
 unsigned long max_oct_tr_ser;
 unsigned long min_oct_tr_ser;
 unsigned long center_oct_tr_ser;
};


union UKEEP_ST
{
  KEEP_ST keep_st;
  unsigned char byte[MAX_MIN_CENTER_LEN];
};



unsigned long rs125_send_timer;
unsigned long im; //counter without rezerved bytes
unsigned long oct_res_sub[PERIOD_OF_KEEP], oct_tr_sub[PERIOD_OF_KEEP], oct_res_ser[PERIOD_OF_KEEP], oct_tr_ser[PERIOD_OF_KEEP];
unsigned long cnt_oct;
unsigned char parse_status; //need init globally !!!!!!!
unsigned char StatBuffer[REP_MAX_LEN];
//USTCS_M ustcs_m;
UKEEP_ST ukeep_st;

extern "C" void MakeStat()
{
  ukeep_st.keep_st.max_oct_res_sub = 0;
  ukeep_st.keep_st.min_oct_res_sub = 0;
  ukeep_st.keep_st.center_oct_res_sub = 0;
  ukeep_st.keep_st.max_oct_tr_sub = 0;
  ukeep_st.keep_st.min_oct_tr_sub = 0;
  ukeep_st.keep_st.center_oct_tr_sub = 0;

  ukeep_st.keep_st.max_oct_res_ser = 0;
  ukeep_st.keep_st.min_oct_res_ser = 0;
  ukeep_st.keep_st.center_oct_res_ser = 0;
  ukeep_st.keep_st.max_oct_tr_ser = 0;
  ukeep_st.keep_st.min_oct_tr_ser = 0;
  ukeep_st.keep_st.center_oct_tr_ser = 0;
 
  for(long i = 0; i < PERIOD_OF_KEEP; i++)
  {
   if(ukeep_st.keep_st.max_oct_res_sub < oct_res_sub[i]) ukeep_st.keep_st.max_oct_res_sub =  oct_res_sub[i];
   if(ukeep_st.keep_st.min_oct_res_sub > oct_res_sub[i]) ukeep_st.keep_st.min_oct_res_sub =  oct_res_sub[i];
   ukeep_st.keep_st.center_oct_res_sub += oct_res_sub[i];

   if(ukeep_st.keep_st.max_oct_tr_sub < oct_tr_sub[i]) ukeep_st.keep_st.max_oct_tr_sub =  oct_tr_sub[i];
   if(ukeep_st.keep_st.min_oct_tr_sub > oct_tr_sub[i]) ukeep_st.keep_st.min_oct_tr_sub =  oct_tr_sub[i];
   ukeep_st.keep_st.center_oct_tr_sub += oct_tr_sub[i];

   if(ukeep_st.keep_st.max_oct_res_ser < oct_res_ser[i]) ukeep_st.keep_st.max_oct_res_ser =  oct_res_ser[i];
   if(ukeep_st.keep_st.min_oct_res_ser > oct_res_ser[i]) ukeep_st.keep_st.min_oct_res_ser =  oct_res_ser[i];
   ukeep_st.keep_st.center_oct_res_ser += oct_res_ser[i];

   if(ukeep_st.keep_st.max_oct_tr_ser < oct_tr_ser[i]) ukeep_st.keep_st.max_oct_tr_ser =  oct_tr_ser[i];
   if(ukeep_st.keep_st.min_oct_tr_ser > oct_tr_ser[i]) ukeep_st.keep_st.min_oct_tr_ser =  oct_tr_ser[i];
   ukeep_st.keep_st.center_oct_tr_ser += oct_tr_ser[i];
  }

 ukeep_st.keep_st.center_oct_res_sub /= PERIOD_OF_KEEP;
 ukeep_st.keep_st.center_oct_tr_sub /= PERIOD_OF_KEEP;
 ukeep_st.keep_st.center_oct_res_ser /= PERIOD_OF_KEEP;
 ukeep_st.keep_st.center_oct_tr_ser /= PERIOD_OF_KEEP;
}

unsigned char IsNotRezerved(unsigned long i)
{
 if(i < 16) return 1;
 if(i < 24) return 0;
 if(i < 80) return 1;
 if(i < 84) return 0;
 if(i < 116) return 1;
 if(i < 140) return 0;
 if(i < 144) return 1;
 if(i < 152) return 0;
 if(i < 200) return 1;
 if(i < 204) return 0;
 if(i < 240) return 1;
 if(i < 264) return 0;
 if(i < 268) return 1;
 if(i < 276) return 0;
 return 1;
}






extern "C" SendPort(unsigned char * pMes, unsigned long len)
{
 while(len--)
 {
   ToPdcTu2(*pMes++);
 }
}


extern "C" void SendRequestStcs(unsigned long Offset, unsigned long BTR)
{
  USTCS_M UMes;
  UMes.stcs_m.MID = SEND_ID;
  UMes.stcs_m.Rez[0] = 0;
  UMes.stcs_m.Rez[1] = 0;
  UMes.stcs_m.Rez[2] = 0;
  UMes.stcs_m.Rez[3] = 0;
  UMes.stcs_m.Rez[4] = 0;
  UMes.stcs_m.Rez[5] = 0;
  UMes.stcs_m.MBS = 8;
  UMes.stcs_m.Offset = Offset;
  UMes.stcs_m.BTR = BTR;
  UMes.stcs_m.MCS = 0;
  for(long i = 0; i < (STCS_MES_LEN - 1); i++)
  {
	UMes.stcs_m.MCS ^= UMes.byte[i];
  }
//  printf(".");
SendPort((unsigned char *)UMes.byte,STCS_MES_LEN);
}




extern "C" void ReceiveReport(unsigned char rbyte)
{
static unsigned long mes_counter;
static	USTCSR_M URMes;
static unsigned long rets_cnt;
static unsigned char checksum;
unsigned long iw;

 if(!parse_status)
 {
  if(rbyte == REPORT_HEADER)
   {
     parse_status = 1;
     mes_counter = 1;
	 rets_cnt = 0;
	 checksum =  REPORT_HEADER;
   	for(long i = 0; i < STCS_REP_LEN; i++)
  	{
	URMes.byte[i] = 0;
  	}
	 URMes.stcsr_m.HEADER = REPORT_HEADER;
   }  //header
 }
 else
 {
    mes_counter++;
	switch(mes_counter)
	{
	case  2: URMes.stcsr_m.MID += rbyte << 24;  break;
	case  3: URMes.stcsr_m.MID += rbyte << 16;  break;
	case  4: URMes.stcsr_m.MID += rbyte << 8;  break;
	case  5: URMes.stcsr_m.MID += rbyte;  
			 if(URMes.stcsr_m.MID != REP_ID)
			 {
			  parse_status = 0;	//this is not report
			 }
			 break;
    case  6: URMes.stcsr_m.MBS += rbyte << 24;  break;
	case  7: URMes.stcsr_m.MBS += rbyte << 16;  break;
	case  8: URMes.stcsr_m.MBS += rbyte << 8;  break;
	case  9: URMes.stcsr_m.MBS += rbyte; 
	
//hier need add checking size	
			if(URMes.stcsr_m.MBS > (REP_MAX_LEN + OFFSET_SIZE))
			{
			 parse_status = 0;
			}
	
	 break;

	case  10 :	URMes.stcsr_m.Offset += rbyte << 24;  break;
	case  11 :	URMes.stcsr_m.Offset += rbyte << 16;  break;
	case  12 :	URMes.stcsr_m.Offset += rbyte << 8;  break;
	case  13 :	URMes.stcsr_m.Offset += rbyte;  
	
				//
				break;
	
	default :
				 if( (mes_counter - 13) <= (URMes.stcsr_m.MBS - OFFSET_SIZE))
				 {
				  URMes.stcsr_m.RETS[rets_cnt++] = rbyte;
				 }
				 else
				 {
				   URMes.stcsr_m.MCS = rbyte;
				 //temporary  if(CheckMCS())
				 //  CheckMCS(&URMes);
			  //need check	   if(checksum == URMes.stcsr_m.MCS)
				   if(1)
				   {
					 //hier fill statistics structs in ram for sending to request to host
					 for(iw = 0; iw < REP_MAX_LEN; iw++)
					 {
					  StatBuffer[iw] = URMes.stcsr_m.RETS[iw];
					 }


					   oct_res_sub[cnt_oct] =  (URMes.stcsr_m.RETS[0] << 24)	+ 
									  (URMes.stcsr_m.RETS[1] << 16)	+
									  (URMes.stcsr_m.RETS[2] << 8)	+
									   URMes.stcsr_m.RETS[3];
					   oct_tr_sub[cnt_oct]  =  (URMes.stcsr_m.RETS[4] << 24)	+ 
									  (URMes.stcsr_m.RETS[5] << 16)	+
									  (URMes.stcsr_m.RETS[6] << 8)	+
									   URMes.stcsr_m.RETS[7];
					   oct_res_ser[cnt_oct] =  (URMes.stcsr_m.RETS[8] << 24)	+ 
									  (URMes.stcsr_m.RETS[9] << 16)	+
									  (URMes.stcsr_m.RETS[10] << 8)	+
									   URMes.stcsr_m.RETS[11];
					   oct_tr_ser[cnt_oct]  =  (URMes.stcsr_m.RETS[12] << 24)	+ 
									  (URMes.stcsr_m.RETS[13] << 16)	+
									  (URMes.stcsr_m.RETS[14] << 8)	+
									   URMes.stcsr_m.RETS[15];
					  cnt_oct++;
					  if(cnt_oct >= PERIOD_OF_KEEP)
					  {
					   cnt_oct = 0;
					  }	


				   }
				   else
				   {
				   //	parse_status = 0;
				   }
				   parse_status = 0;

				 }
	} //switch
	checksum ^= rbyte;

 } //parse_status
} 










#endif // USE_RS125

   */



#include "embmsg485.cpp"
//msg485______________________
#define   EmbMsg485Buffer_Size (16)
struct EmbMsg485Buffer
{
    unsigned short BuffSize;
    unsigned short Head;
    unsigned short Tail;
  //  EmbMsg Buff[32];
   // EmbMsg Buff[16];
	  EmbMsg485 Buff[EmbMsg485Buffer_Size];
  public:
    void Init();
    void Add(EmbMsg485&);
    void Get(EmbMsg485&);
    unsigned short Used();
    unsigned short Free();
};

void EmbMsg485Buffer::Init()
{
  BuffSize = EmbMsg485Buffer_Size;
  Head = 0;
  Tail = 0;
}

void EmbMsg485Buffer::Add(EmbMsg485 &msg)
{
	for(int i=0; i<msg.FullSize(); i++) Buff[Head].body[i] = msg.body[i];
	Head++;
  if(Head == BuffSize)
  {
   
   Head = 0;
   }
}

void EmbMsg485Buffer::Get(EmbMsg485 &msg)
{
  if(++Tail < BuffSize) 
	{
		for(int i=0; i<msg.FullSize(); i++) msg.body[i] = Buff[Tail-1].body[i];
	}
	else
	{
		Tail = 0;
		for(int i=0; i<msg.FullSize(); i++) msg.body[i] = Buff[BuffSize-1].body[i];
	}
}

unsigned short EmbMsg485Buffer::Used()
{
  int n = Head - Tail;

  if( n >= 0 )
  {
 //  printEthLongHex(Head);
   return n;
   }
  else
  {	 
  if(n == (BuffSize - 1))  {
#ifdef	ETH_DEBUG_ENABLED	
 //  printEthLongHex(0x99);
#endif	//ETH_DEBUG_ENABLED
   	 }
  return n+BuffSize;
  }
}

unsigned short EmbMsg485Buffer::Free()
{
  int n = Tail - Head;
  if( n > 0 ) return n;
  else return n+BuffSize;
}
/////////////////////


//msg485______________________

EmbMsg485Buffer tBuffEmbMsg485Request_1;
EmbMsg485Buffer tBuffEmbMsg485Request_2;

unsigned char ascii[] = {
//0:
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xD5,0xDA,
0x20,0x20,0x32,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
//32:
0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x20,
//64:
0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x20,0x5d,0x5e,0x20,
//96
0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,
//
//128:
0x20,0x20,0x27,0x20,0xca,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0xca,0xcb,0xdf,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
//160:
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xfd,0xa2,0x20,0x20,0xc8,0x20,0x2d,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0xfe,0xdf,0xb5,0x20,0x20,0xc9,0x20,0x20,0x20,0x20,
//192:
0x41,0xa0,0x42,0xa1,0xe0,0x45,0xa3,0xa4,0xa5,0xa6,0x4b,0xa7,0x4d,0x48,0x4f,0xa8,
0x50,0x43,0x54,0xa9,0xaa,0x58,0xe1,0xab,0xac,0xe2,0xad,0xae,0x62,0xaf,0xb0,0xb1,
//224:
0x61,0xb2,0xb3,0xb4,0xe3,0x65,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0x6f,0xbe,
0x70,0x63,0xbf,0x79,0xe4,0x78,0xe5,0xc0,0xc1,0xe6,0xc2,0xc4,0x62,0xc5,0xc6,0xc7
//256
};
//port

void AsciiInit()
{
//0
for(int i = 0; i <= 14; i++)
{
 ascii[i] = 0x20;
}
ascii[15] = 0xD5;  ascii[16] = 0xDA; 

//16
ascii[17] = 0x20;	 ascii[18] = 0x20;	 ascii[19] = 0x32;
for(i = 20; i <= 33; i++)
{
 ascii[i] = 0x20;
}
for(i = 32; i <= 62; i++)
{
 ascii[i] = (i - 1);
}
 ascii[63] = 0x20;

for(i = 64; i <= 91; i++)
{
 ascii[i] = (i - 1);
}
ascii[92] = 0x20;	 ascii[93] = 0x5d;	 ascii[94] = 0x5e;	 ascii[95] = 0x20;
//96
for(i = 96; i <= 127; i++)
{
 ascii[i] = (i - 1);
}
//128
for(i = 128; i <= 129; i++)
{
 ascii[i] = 0x20;
}
ascii[130] = 0x27;	 ascii[131] = 0x20;	ascii[132] = 0xca;

for(i = 133; i <= 146; i++)
{
 ascii[i] = 0x20;
}

ascii[147] = 0xca; ascii[148] = 0xcb; ascii[149] = 0xdf;

for(i = 150; i <= 166; i++)
{
 ascii[i] = 0x20;
}

ascii[167] = 0xfd; ascii[168] = 0xa2;

for(i = 169; i <= 170; i++)
{
 ascii[i] = 0x20;
}
ascii[171] = 0xc8; ascii[172] = 0x20; ascii[173] = 0x2d;

for(i = 174; i <= 181; i++)
{
 ascii[i] = 0x20;
}

ascii[182] = 0xfe; ascii[183] = 0xdf; ascii[184] = 0xb5;

for(i = 185; i <= 186; i++)
{
 ascii[i] = 0x20;
}
ascii[187] = 0xc9;

for(i = 188; i <= 191; i++)
{
 ascii[i] = 0x20;
}
//192
ascii[192] = 0x41;	ascii[193] = 0xa0;	 ascii[194] = 0x42;	 ascii[195] = 0xa1;	
ascii[196] = 0xe0;	ascii[197] = 0x45;	 ascii[198] = 0xa3;	 ascii[199] = 0xc4;
ascii[200] = 0xa5;  ascii[201] = 0xa6;	 ascii[201] = 0x4b;	 ascii[203] = 0xa7;
ascii[204] = 0x4d;	ascii[205] = 0x48;	 ascii[206] = 0x4f;  ascii[207] = 0xa8;

ascii[208] = 0x50;	ascii[209] = 0x43;	 ascii[210] = 0x54;	 ascii[211] = 0xa9;
ascii[212] = 0xaa;	ascii[213] = 0x58;	 ascii[214] = 0xe1;	 ascii[215] = 0xab;
ascii[216] = 0xac;	ascii[217] = 0xe2;	 ascii[218] = 0xad;	 ascii[219] = 0xae;	 
ascii[220] = 0x62;	ascii[221] = 0xaf;	 ascii[222] = 0xb0;	 ascii[223] = 0xb1;
//224
ascii[224] = 0x61;	ascii[225] = 0xb2;	 ascii[226] = 0xb3;	 ascii[227] = 0xb4;
ascii[228] = 0xe3;  ascii[229] = 0x65;	 ascii[230] = 0xb6;	 ascii[231] = 0xb7;
ascii[232] = 0xb8;	ascii[233] = 0xb9;	 ascii[234] = 0xba;	 ascii[235] = 0xbb;
ascii[236] = 0xbc;	ascii[237] = 0xbd;	 ascii[238] = 0x6f;	 ascii[239] = 0xbe;

ascii[240] = 0x70;	ascii[241] = 0x63;	 ascii[242] = 0xbf;	 ascii[243] = 0x79;
ascii[244] = 0xe4;	ascii[245] = 0x78;	 ascii[246] = 0xe5;	 ascii[247] = 0xc0;
ascii[248] = 0xc1;	ascii[249] = 0xe6;	 ascii[250] = 0xc2;	 ascii[251] = 0xc4;	
ascii[252] = 0x62;	ascii[253] = 0xc5;	 ascii[254] = 0xc6;	 ascii[255] = 0xc7; 

}



union UL2UC
{
	unsigned long ul;
	unsigned char uc[4];
};

union UI2UC
{
	unsigned long ui;
 //	unsigned char uc[2];
	unsigned char uc[4];
};
/*
union u2uc
{
  unsigned u;
	unsigned char uc[2];
};
*/
unsigned char HexChar(unsigned char s)
{
  if(s<=9) return s + '0';
  if((s>=0x0A)&&(s<=0x0F)) return s + 'A' - 10;
	return 'x';
}

void ConvertToWin1251(char *str)
{
	int i=0;
	unsigned char ch;
  while(str[i])
	{
		ch=str[i];
		str[i]=ascii[ch];
		i++;
		if(i>=24)
		{
			str[i]=0; 
			return;
		}
	}
}
/*
unsigned SelfID() 
{ 
	unsigned far *ctrl = (unsigned far*)0xFFFF000A; 
	return ((*ctrl&0x00FF)<<8)+(((*ctrl)>>8)&0x00FF); 
}

unsigned SelfYear() 
{ 
	unsigned far *ctrl = (unsigned far*)0xFFFF0008; 
	return ((*ctrl&0x00FF)<<8)+(((*ctrl)>>8)&0x00FF);  
}

unsigned SelfVer1() 
{ 
	unsigned far *ctrl = (unsigned far*)0xFFFF000C; 
	return ((*ctrl&0x00FF)<<8)+(((*ctrl)>>8)&0x00FF);  
}

unsigned SelfVer2() 
{ 
	unsigned far *ctrl = (unsigned far*)0xFFFF000E; 
	return ((*ctrl&0x00FF)<<8)+(((*ctrl)>>8)&0x00FF);  
}
*/
unsigned char Modify5A(unsigned char byte)
{
	switch(byte)
	{
		case 0x00: return 0x5A;
		case 0x01: return 0x55; 
		case 0x02: return 0xA5; 
		case 0x03: return 0xAA; 
		default: return 0;
	}

}
// 	unsigned CRC() {	if(Length()<256) return body[Length()+12] + (body[Length()+11]<<8);	else return 0; }
 /*
struct EmbMsg485
{
	unsigned char readyToSend;
	unsigned short counter;
	unsigned char body[64];

	unsigned char Addr()	{	return body[0];	 }
	unsigned char Length() {	return body[1];	 }
	unsigned short CRC() {	return body[body[1]+2]+1; }
	unsigned char Body(int i) { return body[i+2]; }

	void SetAddr(unsigned char byte) { body[0]=byte|0x10; }
	void SetLength(unsigned char byte) { body[1]=byte;	}
	void SetBody(int i, unsigned char byte) { body[i+2]=byte; }

	void Init();
	unsigned short Add(unsigned char byte);
	unsigned short Used() { return counter; }
	unsigned short IsFree() { return 64-counter; }
	int short IsEnd();
	unsigned short ChkCRC();
	unsigned short CalcCRC();
	unsigned char IsReadyToSend() { return readyToSend; }	
	void SetReadyToSend() { readyToSend=1; }
};

void EmbMsg485::Init()
{
	counter=0;
	readyToSend=0;
  for(int i=0; i<64; i++) body[i]=0;
}

unsigned short EmbMsg485::Add(unsigned char byte)
{
  if(counter<64)
	{
		body[counter++]=byte;
	}
	else
	  return 0;
}

int short EmbMsg485::IsEnd()
{
  if(counter>2)
		if(counter==Length()+3)
			return 1;
	return 0;
} 

unsigned short EmbMsg485::ChkCRC()
{
	if(CRC()==CalcCRC()) return 1;
	else return 0;
}

unsigned short EmbMsg485::CalcCRC()
{
  int i;
	unsigned short c=0;
	if(Length()<64) 
	{
		for(i=0; i<Length()+2; i++) c += body[i];
		body[Length()+2]=c+1;
		return c+1;
	}
	else return 0;
} 

*/

// 	unsigned CRC() {	if(Length()<256) return body[Length()+12] + (body[Length()+11]<<8);	else return 0; }
struct MsgStatus
{
	unsigned readyToSend : 1;
	unsigned isRS232 : 1;
	unsigned isRS485 : 1;
	unsigned reserved : 5;
};

union UnMsgStatus
{
	MsgStatus msgStatus;
	unsigned char byte;
};

struct TOM // [TR�00MEK]
{
	int K : 1; // K - ������� ��������� ������ ���������, ��������������� � "1" ��� ��������� ������ ���������;
	int E : 1; // E - ��� ������ � CRC, ��������������� � "1" ���� �� �������� CRC;
	int M : 1; // M - ��� ��������, ��������������� � "1" ��� ������� ������ "��������� ��������";
	int reserved : 2;
	int C : 1; // R - ������� ��������� �� RS-485 (��� ������ �������)
	int R : 1; // C - ��������������� � "1" ���� ��� ������ ���������� ������������� � �������.
	int T : 1; // T - ��� �������; 
//	TOM() { reserved=0; T=R=C=M=E=K=0; }
};

union UnTOM
{
	unsigned char byte;
	TOM tom;
};
/*
struct EmbMsg
{
	unsigned char dir;
	UnMsgStatus readyToSend;
	unsigned counter;
	unsigned char body[270];
// Start/8	TOM/8	Cycle/8	AddrI/16	AddrS/16	Type/8	Length/16	 BODY/ Length	CRC/16	Blank/8
	unsigned char TOM()	{ return body[0]; }
	unsigned char Cycle()	{ return body[1]; }
	unsigned AddrI()	{	return body[3] + (body[2]<<8);	 }	// 2
	unsigned AddrS()	{	return body[5] + (body[4]<<8);	 }		// 2
	unsigned AddrR()	{	return body[10] + (body[9]<<8);	 }		// 2
	void SetAddrI(unsigned word) { body[3]=word&0xFF; body[2]=(word>>8)&0xFF;	}
	void SetAddrS(unsigned word) { body[5]=word&0xFF; body[4]=(word>>8)&0xFF;	}
	void SetAddrR(unsigned word) { body[10]=word&0xFF; body[9]=(word>>8)&0xFF;	}

	void SetRS485() { UnTOM unTOM; unTOM.byte = body[0]; unTOM.tom.R=1; body[0] = unTOM.byte; }
	unsigned char IsRS485() { UnTOM unTOM; unTOM.byte = body[0]; if(unTOM.tom.R) return 1; return 0; }

	void SetType(unsigned char byte) { body[6]=byte; }
	void SetLength(unsigned word) { if(IsRS485()) word+=2; body[8]=word&0xFF; body[7]=(word>>8)&0xFF;	}


	unsigned char Type()	{ return body[6]; }		// 1
	unsigned Length() {	return body[8] + (body[7]<<8);	 }			// 2
	unsigned FullSize(); 			// 2
//	unsigned CRC() {	if(Length()<256) return body[Length()+1] + (body[Length()]<<8);	else return 0; }
	unsigned CRC() {	if(Length()<256) return body[Length()+10] + (body[Length()+9]<<8);	else return 0; }
	unsigned char Body(int i) { if(IsRS485()) return body[i+11]; else return body[i+9]; }
	unsigned char BodyR(int i) { return body[i+11]; }

	void SetTOM(unsigned char byte) { body[0]=byte; }
	void SetCycle(unsigned char byte) { body[1]=byte; }


	void SetBody(int i, unsigned char byte) { if(IsRS485()) body[i+11]=byte; else body[i+9]=byte; }
	void SetBodyR(int i, unsigned char byte) { body[i+11]=byte; }

//	void SetCRC() { if(Length()<256) { body[Length()+1]=CalculateCRC()&0xFF; body[Length()]=(CalculateCRC()>>8)&0xFF; }

	void Init();
	unsigned Add(unsigned char byte);
	unsigned Used() { return counter; }
	unsigned IsFree() { return 270-counter; }
	int IsEnd();
	int IsEndOfHeader();
	unsigned ChkCRC();
	unsigned CalcCRC();
	unsigned ReCalcCRC();
	unsigned char IsReadyToSend() { return readyToSend.msgStatus.readyToSend; }	
	void SetReadyToSend(unsigned char i) { readyToSend.msgStatus.readyToSend=i; }
//	unsigned char IsRS485() { return readyToSend.msgStatus.isRS485; } 
//	void SetRS485(unsigned char i) { readyToSend.msgStatus.isRS485=i; } 
	unsigned char IsRS232() { return readyToSend.msgStatus.isRS232; } 
	void SetRS232(unsigned char i) { readyToSend.msgStatus.isRS232=i; } 
	unsigned char Dir() { return dir; }

	void SetDir(unsigned char d) { dir= d; } // dir = 1 ������ � West, dir=2 ������ � East

	void Copy(EmbMsg m);
};

void EmbMsg::Copy(EmbMsg m)
{
	for(int i=0; i<270; i++) body[i]=m.body[i];
} 

void EmbMsg::Init()
{
	counter=0;
  for(int i=0; i<270; i++) body[i]=0;
	readyToSend.msgStatus.readyToSend=0;
}

unsigned EmbMsg::FullSize() 
{	
	if(Length()<256) return Length() + 13;	 
	else return counter;
}

unsigned EmbMsg::Add(unsigned char byte)
{
  if(counter<270)
	{
		body[counter++]=byte;
		return 1;
	}
	else
	  return 0;
}

int EmbMsg::IsEnd()
{
	if(body[0])
		if(counter>10)
			if(counter==Length()+13)
				return 1;
	return 0;
}

int EmbMsg::IsEndOfHeader()
{
  if(counter==9) return 1;
	if(counter>9) return 2;
	return 0;
}

unsigned EmbMsg::ChkCRC()
{
	if(CRC()==CalcCRC()) return 1;
	else return 0;
}

unsigned EmbMsg::CalcCRC()
{
  int i;
	unsigned c=0;
	if(Length()<=256) 
	{
		for(i=0; i<Length()+11; i++) c += body[i];
		body[Length()+11]=(c>>8)&0xFF;
		body[Length()+12]=c&0xFF;
		return c;
	}
	else return 0;
} 
/////////////////////
struct EmbMsgBuffer
{
    unsigned BuffSize;
    unsigned Head;
    unsigned Tail;
    EmbMsg Buff[16];
  public:
    void Init();
    void Add(EmbMsg&);
    void Get(EmbMsg&);
    unsigned Used();
    unsigned Free();
};

void EmbMsgBuffer::Init()
{
  BuffSize = 16;
  Head = 0;
  Tail = 0;
}

void EmbMsgBuffer::Add(EmbMsg &msg)
{
	for(int i=0; i<msg.FullSize(); i++) Buff[Head].body[i] = msg.body[i];
	Head++;
  if(Head == BuffSize) Head = 0;
}

void EmbMsgBuffer::Get(EmbMsg &msg)
{
  if(++Tail < BuffSize) 
	{
		for(int i=0; i<msg.FullSize(); i++) msg.body[i] = Buff[Tail-1].body[i];
	}
	else
	{
		Tail = 0;
		for(int i=0; i<msg.FullSize(); i++) msg.body[i] = Buff[BuffSize-1].body[i];
	}
}

unsigned EmbMsgBuffer::Used()
{
  int n = Head - Tail;
  if( n >= 0 ) return n;
  else return n+BuffSize;
}

unsigned EmbMsgBuffer::Free()
{
  int n = Tail - Head;
  if( n > 0 ) return n;
  else return n+BuffSize;
}

*/

struct EmbMsg
{
	unsigned char dir;
	UnMsgStatus readyToSend;
	unsigned short counter;
	unsigned char body[270];
// Start/8	TOM/8	Cycle/8	AddrI/16	AddrS/16	Type/8	Length/16	 BODY/ Length	CRC/16	Blank/8
	unsigned char TOM()	{ return body[0]; }
	unsigned char Cycle()	{ return body[1]; }
	unsigned short AddrI()	{	return body[3] + (body[2]<<8);	 }	// 2
	unsigned short AddrS()	{	return body[5] + (body[4]<<8);	 }		// 2
	unsigned short AddrR()	{	return body[10] + (body[9]<<8);	 }		// 2
	void SetAddrI(unsigned short word) { body[3]=word&0xFF; body[2]=(word>>8)&0xFF;	}
	void SetAddrS(unsigned short word) { body[5]=word&0xFF; body[4]=(word>>8)&0xFF;	}
	void SetAddrR(unsigned short word) { body[10]=word&0xFF; body[9]=(word>>8)&0xFF;	}

	void SetRS485() { UnTOM unTOM; unTOM.byte = body[0]; unTOM.tom.R=1; body[0] = unTOM.byte; }
	unsigned char IsRS485() { UnTOM unTOM; unTOM.byte = body[0]; if(unTOM.tom.R) return 1; return 0; }
	void SetType(unsigned char byte) { body[6]=byte; }
	void SetLength(unsigned short word) { if(IsRS485()) word+=2; body[8]=word&0xFF; body[7]=(word>>8)&0xFF;	}


	unsigned char Type()	{ return body[6]; }		// 1
	unsigned short Length() {	return body[8] + (body[7]<<8);	 }			// 2
	unsigned short FullSize(); 			// 2
//	unsigned CRC() {	if(Length()<256) return body[Length()+1] + (body[Length()]<<8);	else return 0; }
	unsigned short CRC() {	if(Length()<256) return body[Length()+10] + (body[Length()+9]<<8);	else return 0; }
	unsigned char Body(int i) { if(IsRS485()) return body[i+11]; else return body[i+9]; }
	unsigned char BodyR(int i) { return body[i+11]; }

	void SetTOM(unsigned char byte) { body[0]=byte; }
	void SetCycle(unsigned char byte) { body[1]=byte; }


	void SetBody(int i, unsigned char byte) { if(IsRS485()) body[i+11]=byte; else body[i+9]=byte; }
	void SetBodyR(int i, unsigned char byte) { body[i+11]=byte; }

//	void SetCRC() { if(Length()<256) { body[Length()+1]=CalculateCRC()&0xFF; body[Length()]=(CalculateCRC()>>8)&0xFF; }

	void Init();
	unsigned short Add(unsigned char byte);
	unsigned short Used() { return counter; }
	unsigned short IsFree() { return 270-counter; }
	int short IsEnd();
	int short IsEndOfHeader();
	unsigned short ChkCRC();
	unsigned short CalcCRC();
	unsigned short ReCalcCRC();
	unsigned char IsReadyToSend() { return readyToSend.msgStatus.readyToSend; }	
	void SetReadyToSend(unsigned char i) { readyToSend.msgStatus.readyToSend=i; }
//	unsigned char IsRS485() { return readyToSend.msgStatus.isRS485; } 
//	void SetRS485(unsigned char i) { readyToSend.msgStatus.isRS485=i; } 
	unsigned char IsRS232() { return readyToSend.msgStatus.isRS232; } 
	void SetRS232(unsigned char i) { readyToSend.msgStatus.isRS232=i; } 
	unsigned char Dir() { return dir; }

	void SetDir(unsigned char d) { dir= d; } // dir = 1 ������ � West, dir=2 ������ � East

	void Copy(EmbMsg m);
};

void EmbMsg::Copy(EmbMsg m)
{
	for(int i=0; i<270; i++) body[i]=m.body[i];
} 

void EmbMsg::Init()
{
	counter=0;
  for(int i=0; i<270; i++) body[i]=0;
	readyToSend.msgStatus.readyToSend=0;
}

unsigned short EmbMsg::FullSize() 
{	
	if(Length()<256) return Length() + 13;	 
//101210	else return counter;
	else return 0; //101210 to do not resend bad messages
}

unsigned short EmbMsg::Add(unsigned char byte)
{
  if(counter<270)
	{
		body[counter++]=byte;
		return 1;
	}
	else
	  return 0;
}

int short EmbMsg::IsEnd()
{
	if(body[0])
		if(counter>10)
			if(counter==Length()+13)
				return 1;
	return 0;
}

int short EmbMsg::IsEndOfHeader()
{
  if(counter==9) return 1;
	if(counter>9) return 2;
	return 0;
}


//________________________
unsigned short EmbMsg::ChkCRC()
{
  int i;
	unsigned c=0, b=0;
  //	if(typeOfProtocol==2)
   //	{
		if(Length()<=256) 
		{
			for(i=0; i<Length()+11; i++) c += body[i];
			b = CRC();
 #ifdef DEBUG_LOOP_PRINT

			printfpd("\n\rc= %02X", c);	
			printfpd("b= %02X\n\r", b);	
 #endif
			if(b==c) return 1;
			else return 0;
		}
//	}
    return 1;
}

unsigned short EmbMsg::CalcCRC()
{
  int i;
	unsigned c=0;
 //	if(typeOfProtocol==2)
  //	{
		if(Length()<=256) 
		{
			for(i=0; i<Length()+11; i++) c += body[i];
			body[Length()+11]=(c>>8)&0xFF;
			body[Length()+12]=c&0xFF;
			return c;
		}
		else return 0;
  //	}
  //	else return 0;
} 

//______________________
  /*
unsigned short EmbMsg::ChkCRC()
{
	if(CRC()==CalcCRC()) return 1;
	else return 0;
}

unsigned short EmbMsg::CalcCRC()
{
  int i;
	unsigned short c=0;
	if(Length()<=256) 
	{
		for(i=0; i<Length()+11; i++) c += body[i];
		body[Length()+11]=(c>>8)&0xFF;
		body[Length()+12]=c&0xFF;
		return c;
	}
	else return 0;
} 
	 */
/////////////////////
struct EmbMsgBuffer
{
    unsigned short BuffSize;
    unsigned short Head;
    unsigned short Tail;
    EmbMsg Buff[16];
  public:
    void Init();
    void Add(EmbMsg&);
    void Get(EmbMsg&);
    unsigned short Used();
    unsigned short Free();
};

void EmbMsgBuffer::Init()
{
  BuffSize = 16;
  Head = 0;
  Tail = 0;
}

void EmbMsgBuffer::Add(EmbMsg &msg)
{
	for(int i=0; i<msg.FullSize(); i++) Buff[Head].body[i] = msg.body[i];
	Head++;
  if(Head == BuffSize) Head = 0;
}

void EmbMsgBuffer::Get(EmbMsg &msg)
{
  if(++Tail < BuffSize) 
	{
		for(int i=0; i<msg.FullSize(); i++) msg.body[i] = Buff[Tail-1].body[i];
	}
	else
	{
		Tail = 0;
		for(int i=0; i<msg.FullSize(); i++) msg.body[i] = Buff[BuffSize-1].body[i];
	}
}

unsigned short EmbMsgBuffer::Used()
{
  int short n = Head - Tail;
  if( n >= 0 ) return n;
  else return n+BuffSize;
}

unsigned short EmbMsgBuffer::Free()
{
  int n = Tail - Head;
  if( n > 0 ) return n;
  else return n+BuffSize;
}

/////////////////////


struct Emb2TypeVer
{
	unsigned short type;
	unsigned short softVer;
	unsigned short ctrlNumber;
	unsigned short ctrlYear;
	unsigned short ctrlVer1;
	unsigned short ctrlVer2;
	unsigned char signature_hardware[16];
	unsigned char signature_software[16];
};

union UnEmb2TypeVer
{
	Emb2TypeVer emb2TypeVer;
	unsigned char byte[44];
};

struct StateBMD155
{
	unsigned char state;  // ��� 0: "0" - ���������� ����� � ���1, "1" - �����
									// ��� 1: "0" - ���������� ����� � ���2, "1" - �����
									// ��� 1: "0" - ���������� ����� ��, "1" - �����
	unsigned char state2;  // ��������� ����� �����������
	unsigned char ppu1_bytes[16];
	unsigned char ppu2_bytes[16];														// 34
	unsigned long count_no_correct_block1;									// 42
	unsigned long count_no_correct_block2;									// 46
	unsigned long count_no_correct_result;									// 50
	unsigned long count_notRS1;															// 54
	unsigned long count_notRS2;															// 58
	unsigned long count_block;															// 62
	unsigned char mod; // ��������� ����� �����������       // 63
	unsigned char dem1; // ��������� ����� �����������      // 64
	unsigned char dem2; // ��������� ����� �����������      // 65
	unsigned char state_dem1; // ��������� ����� �����������// 66
	unsigned char state_dem2; // ��������� ����� �����������// 67
	unsigned char statePI; // ��������� ����� �����������		// 68	
	unsigned char loopPI; // ��������� �������							// 69
	unsigned char demPI; // ��������� �������������					// 70
};

union UnStateBMD155
{
	StateBMD155 stateBMD155;
	unsigned char byte[72];
};
	
struct StatePUM
{
	unsigned char ver;						// 1
	unsigned char reserv; 				// 2
	unsigned char reserv1;	 //my					// 1 //2
	unsigned char reserv2;	 //my						 //3
	unsigned long ulBlock;				// 6
	unsigned long ulErrOut;				// 10
	unsigned long ulErrAfterRS1;	// 14
	unsigned long ulErrAfterRS2;	// 18
	unsigned long ulErrBeforeRS1;	// 22
	unsigned long ulErrBeforeRS2;	// 26
	unsigned char state[16];			// 42
};

union UnStatePUM
{
	StatePUM statePUM;
	unsigned char byte[42];
};

struct StateRRL
{
	unsigned char ver;	
	unsigned char state;  // ��� 0: "0" - ���������� ����� � ���1, "1" - ����� ��� 1: "0" - ���������� ����� � ���2, 
  //	unsigned char ppu2_bytes[32]; //for test
	unsigned char ppu1_bytes[32];
 	unsigned char ppu2_bytes[32];
 //	unsigned long chok;	
 //	unsigned long chbad;
};

union UnStateRRL
{
	StateRRL stateRRL;
	unsigned char byte[66];
//   	unsigned char byte[74];
};

struct StateDev
{
   unsigned char byte[DEV_INFO_SIZE];
};

StateDev statedev[DEVCONFIG_QUANTITY];



//________________________________________________________new
//#ifdef PROG_PU_M_MUX

struct Emb2Mux34
{
	unsigned char type;
	unsigned char softVer;
	unsigned char numE1;
	unsigned char e3;
	unsigned short err_e3;
	unsigned char reserv[2];
	unsigned char state_e1[16];
	unsigned char ctrl_e1[16];
};

union UnEmb2Mux34
{
	Emb2Mux34 emb2Mux34;
	unsigned char byte[40];
};

//#endif //PROG_PU_M_MUX

//________________________________________________________________<< new
struct Command
{
	unsigned char chan;
	unsigned char command;
	unsigned char par;
	unsigned char done;
};

struct Emb2NetStat
{
	unsigned long selfPacketSend; // 4
	unsigned long selfPacketRecv; // 4
	unsigned long allPacketRecv;  // 4
	unsigned short requestMarker; // 2
	unsigned short genMarker;     // 2
	unsigned short highID;        // 2
	unsigned short buffModPd;        // 2
	unsigned short buffModPm;        // 2
	unsigned short buffTransPd;        // 2
	unsigned short buffTransPm;        // 2
	unsigned short buff232Pd;        // 2
	unsigned short buff232Pm;        // 2
	unsigned short markerTime; //2 
	unsigned char ready_transit; //1 
	unsigned char ready_mod; //1 
};

union UnEmb2NetStat
{
	Emb2NetStat emb2NetStat;
	unsigned char byte[32];
};


struct Emb4PUMFabInfo
{
 unsigned char errUp1;
 unsigned char errDown1;
 unsigned char errUp2;
 unsigned char errDown2;
 unsigned char rezerv[28]

};

union uEmb4PUMFabInfo
{
 Emb4PUMFabInfo   emb4pumfabinfo;
 unsigned char byte[32];
};


/////////////////////

//	EmbIndicator embIndicator;
////////////////////////
	EmbTimer embTimer;
////////////////////////

uEmb4PUMFabInfo	 uemb4pumfabinfo;

#ifdef RS485_MSG_BUFF

	   EmbMsgBuffer tBuffRS485;
	   unsigned long time_lastsend_rs485;
	   unsigned char flag_wait_rs485;
#endif



//___________________________________________________________________need init!!!
unsigned long time1=0,time2=0,time3=0,time4=0,time5=60;
unsigned char flagADUC1=0, flagADUC2=0;

//______________________________________________________________added of  me
 UL2UC ul2uc;
 UI2UC ui2uc;
 unsigned short temp_crc;
// unsigned char * addrRAM;
 unsigned long shift;
 unsigned long len;

//____________________________________________________________<< added of me

void Callback0()
{
  time1++;
  time2++;
  time3++;
  time4++;
  time5++;
}

//--------------------------------------------------
	EmbTimerCallback embTimerCallback0;

	EmbMsgBuffer rBuffEmbMsg;	
	EmbMsgBuffer tBuffEmbMsgWest;
	EmbMsgBuffer tBuffEmbMsgEast;

	EmbMsg embMsg;
	EmbMsg embMsgWest;
	EmbMsg embMsgEast;
	EmbMsg embMsgAns;
//	EmbMsg embMsgTemp;

	EmbMsg485 embMsg485_1;
	EmbMsg485 embMsg485_2;
	EmbMsg485 embMsg485Request_1;
	EmbMsg485 embMsg485Request_2;

//________________________________________101108   need init
    EmbMsg485 embMsg485;
	EmbMsg485 embMsg485Request;
//  	unsigned ans1=0, ans2=0;
//	unsigned char addr485=1;
	unsigned char ss=0;
	UnStateRRL unStateRRL;
unsigned long send41, send42, received1, received2, good1, good2, bad1, bad2;		//t
//_________________________________________101108

//	EmbMsgCover embMsgCoverRequest;
	EmbMsg *embMsgRequest;

	EmbRS232 embRS232;
	EmbRS485 embRS485;
	
//t101115    EmbMsg embMsg485;	 //101115
	EmbMsg embMsg232;	 //added 090406
 //	EmbMsg embMsg232E;	 //added 090406
 	EmbMsg embMsg485E;	  //added 090406

    EmbSerialPU_M embSerialACT155;


//-------------------------------------------------

	unsigned short aI, aS, aR;	  //added 090406

	unsigned char mode5A232E = 0;   //added 090406
	unsigned char mode5A485E = 0;	 //added 090406
	unsigned char mode5A485 = 0;    //added 090406




		
//	EmbSerialACT155 embSerialACT155;
  
	UL2UC ul2uc;
	UI2UC ui2uc;

	unsigned char  * addrRAM;

//	unsigned shift;
 //	unsigned len;
 //	unsigned temp_crc;

	char ch;
	long f_len;

//___________________________________________________________________need init!!!!
	unsigned char flagRequest=0;
	unsigned char stemp, serr=0xFF, crc_temp=0;
	unsigned long i=0;
	unsigned long time1old=0, time2old=0;
	unsigned char flagsend; //101203
	unsigned long time1old485;
	unsigned char request1=0, request2=0;
	unsigned long time3Marker=0, time3BlankTransit=0, time3BlankMod=0;
	unsigned char powerInFar[9];
	unsigned char flag_start_power = 0, powerInBuff[4];
	unsigned char markerWest=0, markerEast=0, ready_transit=0, ready_mod=0, dir=0; // 0 - "Transit->Mod", 1 - "Mod->Transit"
	unsigned char old_ready_transit=0, old_ready_mod=0; // 0 - "Transit->Mod", 1 - "Mod->Transit"
	unsigned char delete_msgWest=0, delete_msgEast=0, recieveWest=0, recieveEast=0;
	unsigned countSend=0, countRecv=0;
	unsigned long time3highID=0;
	char s1[25],s2[25];

	unsigned char send1[16];
	unsigned char send2[16];
	unsigned char err_ppu1, tst_ppu1; 
	unsigned char err_ppu2, tst_ppu2; 
	unsigned char byte, westByte, eastByte; 
	unsigned char mode5A=0, mode5AWest=0, mode5AUp1=0, mode5AUp2=0, mode5AEast=0; 
	unsigned char cycle=0;
	unsigned char i232=0, iTrans=0, iMod=0;
	unsigned char ans1=0, ans2=0, addr485=0;
	unsigned char cur_req_pointer;
	unsigned char cur_req_addr;
	unsigned char cur_ans_pointer;
	unsigned char cur_rem_pointer;

	unsigned char cur_req_quantity;
	unsigned char devans[DEVCONFIG_QUANTITY];
	unsigned char devstate[DEVCONFIG_QUANTITY];

	UnStateBMD155 unStateBMD155;
	UnEmb2TypeVer unEmb2TypeVer; 
	UnEmb2NetStat unEmb2NetStat;
	UnStateRRL unStateRRL;
	UnStatePUM unStatePUM;

//#ifdef PROG_PU_M_MUX
 	UnEmb2Mux34 unEmb2Mux34;
//#endif // PROG_PU_M_MUX


	long count_block;
	long count_no_correct_block1;
	long count_no_correct_block2;
	long count_no_correct_result;
	long count_notRS1;
	long count_notRS2;
	long err_tmp;

	unsigned char tlf_number[6];
	unsigned char tlf_counter=0;
	unsigned char tlf_state=0;
	unsigned char presto = 0;
	unsigned char ring_counter = 0;
	unsigned long presto_time =0;
	unsigned long wait_time =0;
	unsigned long presto_ring =0;

	unsigned short addr1;
	unsigned char  *bt;
   /*
void ProtocolFromModACT155()
{
	while(embSerialACT155.UsedMod())
	{
   //			ResetWatchDog();
//			if(++ic>16) return;
			westByte = embSerialACT155.GetMod();
//printfpd("M:%02X",westByte);
			switch(westByte)
			{
			case 0x55: 
				time3BlankMod = time1; ready_mod=1; recieveWest=0; embMsgWest.Init(); break; 			
			case 0xAA: recieveWest = 1; ready_mod=1; time3BlankMod = time1; embMsgWest.Init();	break; 			
			case 0xA5: markerWest  = 1; ready_mod=1; time3BlankMod = time3Marker = time1; break; // �������� ����� ���!
			case 0x5A: mode5AWest=1; ready_mod=1; break;
			default:
				if(markerWest==1)	markerWest=2; 
				if(recieveWest==1)
				{
					if(mode5AWest) { embMsgWest.Add(Modify5A(westByte)); mode5AWest=0;	}
					else embMsgWest.Add(westByte);
				}
			}


			if(embMsgWest.IsEnd())
		//	if(embMsgWest.ChkCRC()) //101212
			{
				if((embMsgWest.AddrS()!=SelfID())&&(embMsgWest.AddrI()!=SelfID()))
				{
						// �������� �������� ������ ��������� �����
					embSerialACT155.AddTransit(0x55);	
					embSerialACT155.AddTransit(0xAA);
//printfpd("T:%d",embMsgWest.FullSize());	
// printfpd("T:%d",embMsgWest.body[10]);
 // embMsgWest.body[10]++; //to test

					
					for(i=0; i<embMsgWest.FullSize(); i++) 
					{

						switch(embMsgWest.body[i])
						{
						case 0x5A: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x00); break;
						case 0x55: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x01); break;
						case 0xA5: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x02); break;
						case 0xAA: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x03); break;
						default: embSerialACT155.AddTransit(embMsgWest.body[i]);
						}
					}
				}
					
				if(embMsgWest.AddrS()==SelfID())
				{
					embMsgWest.SetDir(1);
					rBuffEmbMsg.Add(embMsgWest);
		 //101212			embMsgWest.Init();
				}

				recieveWest = 0;

			   embMsgWest.Init();  //101210 - to do not send message
			}	//is end chk crc
	  //		else
	  //		{
	  //		   embMsgWest.Init(); //101212 chkcrc
	  //		   recieveWest = 0;
	  //		}

//		if(!recieveWest)
		{
			if(tBuffEmbMsgWest.Used())
			{
				EmbMsg embMsgA;
				embMsgA.Init();
				tBuffEmbMsgWest.Get(embMsgA);
				embSerialACT155.AddTransit(0x55);
				embSerialACT155.AddTransit(0xAA);
//printfpd("t:%d",embMsgWest.FullSize());
				for(i=0; i<embMsgA.FullSize(); i++) 
				{
					switch(embMsgA.body[i])
					{
					case 0x5A: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x00); break;
					case 0x55: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x01); break;
					case 0xA5: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x02); break;
					case 0xAA: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x03); break;
					default: embSerialACT155.AddTransit(embMsgA.body[i]);
					}
	 //				ResetWatchDog();
				}
				embSerialACT155.AddTransit(0x55);
			}
		}
	}
}

void ProtocolFromTransitACT155()
{
	while(embSerialACT155.UsedTransit())
	{
 //		ResetWatchDog();
//		if(++ic>16) return;
		eastByte = embSerialACT155.GetTransit();
//printfpd("T:%02X",eastByte);

		switch(eastByte)
		{
				case 0x55: 
					time3BlankTransit = time1; ready_transit=1; recieveEast=0; embMsgEast.Init(); 
					break; 			
				case 0xAA: countRecv++; recieveEast=1; ready_transit=1; time3BlankTransit = time1; embMsgEast.Init(); break; 			
				case 0xA5: 	markerEast =1; ready_transit=1; time3BlankTransit = time3Marker = time1;  break; // �������� ����� ���!
					// ���� � ������� ���� ����� �� ��������, �� �������� ���
				case 0x5A: mode5AEast=1; ready_transit=1; break;
				default:
					if(markerEast==1)	markerEast=2; 
					if(recieveEast==1)
					{
						if(mode5AEast) { embMsgEast.Add(Modify5A(eastByte)); mode5AEast=0;	}
						else embMsgEast.Add(eastByte);
					}
		}

		if(embMsgEast.IsEnd())
 //		if(embMsgEast.ChkCRC()) //101212
		{
			if((embMsgEast.AddrS()!=SelfID())&&(embMsgEast.AddrI()!=SelfID()))
			{
				embSerialACT155.AddMod(0x55);	
				embSerialACT155.AddMod(0xAA);	
				for(i=0; i<embMsgEast.FullSize(); i++) 
				{

					switch(embMsgEast.body[i])
					{
					case 0x5A: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x00); break;
					case 0x55: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x01); break;
					case 0xA5: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x02); break;
					case 0xAA: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x03); break;
					default: embSerialACT155.AddMod(embMsgEast.body[i]);
					}
				}
				countSend++;
			}
			
			if(embMsgEast.AddrS()==SelfID())
			{

				embMsgWest.SetDir(2);
				rBuffEmbMsg.Add(embMsgEast);
	   //10122			embMsgEast.Init();
			}
		   embMsgEast.Init();	//101210 to not resend this message
		   recieveEast=0;
		}
	//		else
   //			{
   //			   embMsgEast.Init(); //101212 chkcrc
   //			   recieveEast=0;
   //			}

//		if(!recieveEast)
		{
			if(tBuffEmbMsgEast.Used())
			{
				EmbMsg embMsgA;
				embMsgA.Init();
				tBuffEmbMsgEast.Get(embMsgA);
				
				embSerialACT155.AddMod(0x55);
				embSerialACT155.AddMod(0xAA);
				for(i=0; i<embMsgA.FullSize(); i++) 
				{
					switch(embMsgA.body[i])
					{
					case 0x5A: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x00); break;
					case 0x55: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x01); break;
					case 0xA5: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x02); break;
					case 0xAA: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x03); break;
					default: embSerialACT155.AddMod(embMsgA.body[i]);
					}
	  //				ResetWatchDog();
				}
				embSerialACT155.AddMod(0x55);
			}
		}
	}
}


void Check2InitTransitMod()
{

	if(!ready_transit) unEmb2NetStat.emb2NetStat.ready_transit=1;
	if(!ready_mod) unEmb2NetStat.emb2NetStat.ready_mod=1;
		// ���� ��������� ��������� ready_transit ��� ready_mod �� "0" � "1"
		// �� time3Marker = 0; ��� ����� 2355 ����� � �������� 64�*8/11=46545
	if(time1-time3BlankMod>500) 
	{
		recieveWest=0; 
		time3BlankMod = time1;
		embSerialACT155.AddTransit(0x55);
	}
	if(time1-time3BlankTransit>500)
	{
		recieveEast=0; 
		time3BlankTransit = time1;
		embSerialACT155.AddMod(0x55);
	}


	if((time1-time3highID)>10000) 
	{
		time3highID=time1;
	}		

		if(unEmb2NetStat.emb2NetStat.buffModPm<embSerialACT155.UsedMod()) unEmb2NetStat.emb2NetStat.buffModPm = embSerialACT155.UsedMod();
		if(unEmb2NetStat.emb2NetStat.buffTransPm<embSerialACT155.UsedTransit()) unEmb2NetStat.emb2NetStat.buffTransPm = embSerialACT155.UsedTransit();
		if(unEmb2NetStat.emb2NetStat.buffModPd<embSerialACT155.UsedSendMod()) unEmb2NetStat.emb2NetStat.buffModPd = embSerialACT155.UsedSendMod();
		if(unEmb2NetStat.emb2NetStat.buffTransPd<embSerialACT155.UsedSendTransit()) unEmb2NetStat.emb2NetStat.buffTransPd = embSerialACT155.UsedSendTransit();
		if(unEmb2NetStat.emb2NetStat.buff232Pm<embRS232.UsedReceive()) unEmb2NetStat.emb2NetStat.buff232Pm = embRS232.UsedReceive();
		if(unEmb2NetStat.emb2NetStat.buff232Pd<embRS232.UsedTrans()) unEmb2NetStat.emb2NetStat.buff232Pd = embRS232.UsedTrans();

//		if(!recieveEast)
		{
				if(!embSerialACT155.UsedSendMod()) 
				{	
					if(tBuffEmbMsgEast.Used())
					{
						EmbMsg embMsgA;
						embMsgA.Init();
						tBuffEmbMsgEast.Get(embMsgA);
					
						embSerialACT155.AddMod(0x55);
						embSerialACT155.AddMod(0xAA);
						for(i=0; i<embMsgA.FullSize(); i++) 
						{
							switch(embMsgA.body[i])
							{
							case 0x5A: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x00); break;
							case 0x55: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x01); break;
							case 0xA5: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x02); break;
							case 0xAA: embSerialACT155.AddMod(0x5A); embSerialACT155.AddMod(0x03); break;
							default: embSerialACT155.AddMod(embMsgA.body[i]);
							}
			   //				ResetWatchDog();
						}
						embSerialACT155.AddMod(0x55);
					}
				}
		}

//		if(!recieveWest)
		{
			if(!embSerialACT155.UsedSendTransit()) 
			{	
				if(tBuffEmbMsgWest.Used())
				{
					EmbMsg embMsgA;
					embMsgA.Init();
					tBuffEmbMsgWest.Get(embMsgA);
					embSerialACT155.AddTransit(0x55);
					embSerialACT155.AddTransit(0xAA);
					for(i=0; i<embMsgA.FullSize(); i++) 
					{
						switch(embMsgA.body[i])
						{
						case 0x5A: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x00); break;
						case 0x55: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x01); break;
						case 0xA5: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x02); break;
						case 0xAA: embSerialACT155.AddTransit(0x5A); embSerialACT155.AddTransit(0x03); break;
						default: embSerialACT155.AddTransit(embMsgA.body[i]);
						}
				 //		ResetWatchDog();
					}
					embSerialACT155.AddTransit(0x55);
				}
			}
		}

}
  */
/*
unsigned char	ab1[] =	{ 0x45,0x60,0xBF,0x25,0x52,0x2A,0x64,0x3F,0x89,0x00};   // IM-Filter part 1 
unsigned char	ab2[] =	{ 0x45,0x68,0x53,0x02,0x49,0x8A,0x07,0xF6,0x04,0x00};   // IM-Filter part 2 
unsigned char	ab3[] =	{ 0x45,0x18,0x08,0xB0,0xC5,0x42,0x3E,0xFB,0x72,0x07 };  // FRR-Filter    
unsigned char	ab4[] =	{ 0x45,0x28,0x43,0x8a,0xBc,0x27,0x88,0x00,0x00,0x00 }; // AR-Filter - ������ 20
unsigned char	ab5[] =	{ 0x45,0x48,0x96,0x38,0x29,0x96,0xC9,0x2B,0x8B,0x00 }; /// LPR-Filter       
unsigned char	ab6[] =	{0x45,0x20,0x08,0x90,0x3F,0xBC,0x75,0x28,0x72,0x07}; // FRX-Filter       
unsigned char	ab7[] =	{ 0x45,0x30,0xBE,0x04,0xB0,0x27,0x85,0x50,0xc0,0x1a}; // AX-Filter -������ 20
unsigned char	ab8[] =	{ 0x45,0x50,0x96,0x38,0x29,0xF5,0xFA,0x2B,0x8B,0x00}; // LPX-Filter       
unsigned char	ab9[] =	{ 0x45,0x00,0x30,0x9B,0x88,0x80,0x00,0xC8,0x32,0x80}; // TH-Filter part 1 
unsigned char	ab10[] =	{ 0x45,0x08,0x80,0x00,0x80,0x00,0x67,0x35,0x5A,0x01 }; // TH-Filter part 2 
unsigned char	ab11[] =	{ 0x45,0x10,0x22,0xAD,0xB2,0x2A,0x24,0xDC,0x88,0x00};  // TH-Filter part 3 
unsigned char	ab12[] =	{ 0x45,0x80,0xF9,0x29,0x9B,0x2A,0x1A,0x22,0xC1,0x32}; // DC-Parameter     
unsigned char	ab13[] =	{ 0x45,0x70,0x32,0x3B,0x1B,0xC0,0xC3,0xB2,0xAC,0x02}; // Ringing          
unsigned char	ab14[] =	{ 0x45,0x90,0x3E,0xE5,0x2E,0xBA,0x81,0x2A,0xBA,0x8A }; // LP-Filters       
unsigned char	ab15[] =	{ 0x45,0x88,0x7B,0x01,0x2C,0x7B,0xB3,0x47,0x7B,0x01}; // Hook Levels      
unsigned char	ab16[] =	{ 0x45,0x78,0x00,0xC0,0x6D,0x7A,0xB3,0x48,0x08,0x00}; // Ramp Generator   
unsigned char	ab17[] =	{ 0x45,0x58,0x4A,0x41,0x34,0xDB,0x0E,0xA2,0x2A,0x00}; // TTX 
unsigned char	ab18[] =	{0x45,0x38,0x33,0x49,0x22,0x65,0xBB,0x00,0x00,0x00}; // TG1              
unsigned char	ab19[] =	{0x45,0x40,0x33,0x49,0x22,0x65,0xBB,0x00,0x00,0x00}; // TG2              
unsigned char	ab20[] =	{ 0x45,0x98,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  // Reserved
unsigned char	ab21[] =	{ 0x45,0x30,0xBE,0x04,0xB0,0x27}; // AX-Filter -������ 29
unsigned char	ab22[] =	{ 0x46, 0x30, 0x07,0x10,0x79,0x11,0x02,0xFB,0x60,0x00,0x00,0x00 }; //DTMF POP
unsigned char	ab23[] =	{ 0x46,0x4A,0x00 };
unsigned char	ab24[] =	{0x44, 0x21, 0x00, 0x16, 0x06, 0x00, 0x00,  0x16, 0x06, 0x00 }; //pcmr,pcmx- line A
unsigned char	ab25[] =	{ 0x44, 0x1A, 0x00 }; // DSCR
unsigned char	ab26[] =	{ 0x44, 0x2B, 0x04 }; //TSTR3
unsigned char	ab27[] =	{ 0x44, 0x15, 0x01, 0x20, 0x07, 0x00, 0x03 };// bcr1-5
unsigned char	ab28[] =	{ 0x44,0x06,0x80 };  //XCR
unsigned char	ab29[] =	{ 0x44,0x1c,0x00 };  //LMCR1
unsigned char	ab30[] =	{0x4c, 0x21, 0x80, 0x96, 0x86, 0x80, 0x80,  0x96, 0x86, 0x80 }; //pcmr,pcmx- line B
// AKTIV
unsigned char	a22[] =	{ 0x02 };  // AKTIV mode -- ����������� ���������
unsigned char	a221[] =	{ 0x44,0x1c,0x22 };  // LMCR1
unsigned char	a222[] =	{ 0x44,0x1A,0x00 };  // dscr
//outportb(0x511, 0x04); // off hook
// PAUSE
unsigned char	a26[] =	{ 0x02 }; // RING pause MODE -- ��������� ���
unsigned char	a261[] =	{ 0x44,0x1c,0xAA };  // LMCR1
unsigned char	a262[] =	{ 0x44,0x1A,0x05 };  // dscr
//outportb(0x511, 0x04); // off hook
// PAUSE 2
unsigned char	a263[] =	{ 0x02 }; // RING pause MODE -- ��������� ���
unsigned char	a264[] =	{ 0x44,0x1c,0xAA };  // LMCR1
unsigned char	a265[] =	{ 0x44,0x1A,0x05 };  // dscr
//outportb(0x511, 0x00); // off hook
// RING
unsigned char	a272[] =	{ 0x05 }; // RING burst MODE -- ������ ������
unsigned char	a271[] =	{ 0x44,0x1c,0x22 };  // LMCR1
unsigned char	a27[] =	{ 0x44,0x1A,0x00 };  // dscr
//outportb(0x511, 0x00); // �n hook
// WAIT
unsigned char	a28[] =	{ 0x07 }; // power dnv mode -- �������� �������� ������
//outportb(0x511, 0x00); // on hook
unsigned char aaa[7];
unsigned char aa[] = { 0xC4,0x07,0xFF,0x00,0x00,0x00,0x00 }; 

void InitTLF()
{
	int i;

// ����� ������
	for(i=0; i<15; i++) outportb(0x511, 0x08); 
	outportb(0x511, 0x00);
	for(i=0; i<10000; i++);

	outportb(0x510, 0x02); for(i=0; i<sizeof(ab1); i++) outportb(0x50F, ab1[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab1); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab2); i++) outportb(0x50F, ab2[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab2); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab3); i++) outportb(0x50F, ab3[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab3); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab4); i++) outportb(0x50F, ab4[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab4); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab5); i++) outportb(0x50F, ab5[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab5); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab6); i++) outportb(0x50F, ab6[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab6); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab7); i++) outportb(0x50F, ab7[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab7); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab8); i++) outportb(0x50F, ab8[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab8); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab9); i++) outportb(0x50F, ab9[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab9); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab10); i++) outportb(0x50F, ab10[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab10); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab11); i++) outportb(0x50F, ab11[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab11); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab12); i++) outportb(0x50F, ab12[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab12); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab13); i++) outportb(0x50F, ab13[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab13); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab14); i++) outportb(0x50F, ab14[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab14); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab15); i++) outportb(0x50F, ab15[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab15); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab16); i++) outportb(0x50F, ab16[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab16); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab17); i++) outportb(0x50F, ab17[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab17); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab18); i++) outportb(0x50F, ab18[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab18); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab19); i++) outportb(0x50F, ab19[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab19); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab20); i++) outportb(0x50F, ab20[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab20); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab21); i++) outportb(0x50F, ab21[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab21); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab22); i++) outportb(0x50F, ab22[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab22); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab23); i++) outportb(0x50F, ab23[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab23); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab24); i++) outportb(0x50F, ab24[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab24); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab25); i++) outportb(0x50F, ab25[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab25); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab26); i++) outportb(0x50F, ab26[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab26); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab27); i++) outportb(0x50F, ab27[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab27); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab28); i++) outportb(0x50F, ab28[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab28); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab29); i++) outportb(0x50F, ab29[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab29); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab30); i++) outportb(0x50F, ab30[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(ab30); i++);
}

void Ring()
{
	int i;
	outportb(0x510, 0x02); for(i=0; i<sizeof(a272); i++) outportb(0x50F, a272[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a272); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a271); i++) outportb(0x50F, a271[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a271); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a27); i++) outportb(0x50F, a27[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a27); i++);
  outportb(0x511, 0x00); // �n hook
}
void Active()
{
	int i;
	outportb(0x510, 0x02); for(i=0; i<sizeof(a22); i++) outportb(0x50F, a22[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a22); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a221); i++) outportb(0x50F, a221[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a221); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a222); i++) outportb(0x50F, a222[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a222); i++);
	outportb(0x511, 0x04); // off hook
}
void Pause()
{
	int i;
	outportb(0x510, 0x02); for(i=0; i<sizeof(a26); i++) outportb(0x50F, a26[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a26); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a261); i++) outportb(0x50F, a261[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a261); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a262); i++) outportb(0x50F, a262[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a262); i++);
	outportb(0x511, 0x04); // off hook
}
void Pause2()
{
	int i;
	outportb(0x510, 0x02); for(i=0; i<sizeof(a263); i++) outportb(0x50F, a263[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a263); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a264); i++) outportb(0x50F, a264[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a264); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a265); i++) outportb(0x50F, a265[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a265); i++);
	outportb(0x511, 0x00); // off hook
}

void Wait()
{
	int i;
	outportb(0x510, 0x02); for(i=0; i<sizeof(a22); i++) outportb(0x50F, a22[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a22); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a221); i++) outportb(0x50F, a221[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a221); i++);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a222); i++) outportb(0x50F, a222[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a222); i++);
//	outportb(0x510, 0x02); for(i=0; i<sizeof(a28); i++) outportb(0x50F, a28[i]); outportb(0x510, 0x01); for(i=0; i<200*sizeof(a28); i++);
	outportb(0x511, 0x00); // on hook
}

void Read()
{
// ������  ��������/������ �� SPI
// outportb(0x510, 0x02); for(i=0; i<sizeof(ab1); i++) outportb(0x50F, ab1[i]); outportb(0x510, 0x01);
// while((inportb(0x510) & 0x01)!=0);
// ������ �������� ������  �� ������  0x50F ����������� ������� �� ���� ������� �  ����������
	int i;
	outportb(0x510, 0x02); for(i=0; i<sizeof(aa); i++) outportb(0x50F, aa[i]); outportb(0x510, 0x01); inportb(0x510); for(i=0; i<200*sizeof(aa); i++);
	for(i=0; i<7; i++) aaa[i] = inportb(0x50F);
	
}

 */

void SaveFile()
{
						//  <����� � ����-������/32><�������� �����/N�8>
						//	�������� �����.
//	��������: <����� � ������/32><��������/16><N ����� ���������/16><���� ���������/N�8><CRC/16>
//	�����: <����� � ������/32><��������/16><N ����� ���������/16><CRC ���������/16>						ul2uc.uc[0] = embMsg.Body(0);
	ul2uc.uc[0] = embMsgRequest->Body(0);
	ul2uc.uc[1] = embMsgRequest->Body(1);
	ul2uc.uc[2] = embMsgRequest->Body(2);
	ul2uc.uc[3] = embMsgRequest->Body(3);
  //	addrRAM = (unsigned char far *)ul2uc.ul;
//t	addrRAM = (unsigned char *)ul2uc.ul;
   	addrRAM = (unsigned char *)(NVRAM_BASE);

	ui2uc.uc[0] = embMsgRequest->Body(4);
	ui2uc.uc[1] = embMsgRequest->Body(5);
	ui2uc.uc[2] = 0;
	ui2uc.uc[3] = 0;

	shift = ui2uc.ui;
	ui2uc.uc[0] = embMsgRequest->Body(6);
	ui2uc.uc[1] = embMsgRequest->Body(7);
	ui2uc.uc[2] = 0;
	ui2uc.uc[3] = 0;

	len = ui2uc.ui;
	temp_crc=0;
	for(i=0; i<len; i++) temp_crc += embMsgRequest->Body(i+8);
	ui2uc.uc[0] = embMsgRequest->Body(len+8);
	ui2uc.uc[1] = embMsgRequest->Body(len+9);
	ui2uc.uc[2] = 0;
	ui2uc.uc[3] = 0;

	if(ui2uc.ui==temp_crc) for(i=0; i<len; i++) *(addrRAM+i+shift)= embMsgRequest->Body(i+8);
	/// ��������� ����� ///
	embMsgAns.SetType(0x05);
	embMsgAns.SetLength(10);
	embMsgAns.SetBody(0,embMsgRequest->Body(0));
	embMsgAns.SetBody(1,embMsgRequest->Body(1));
	embMsgAns.SetBody(2,embMsgRequest->Body(2));
	embMsgAns.SetBody(3,embMsgRequest->Body(3));
	embMsgAns.SetBody(4,embMsgRequest->Body(4));
	embMsgAns.SetBody(5,embMsgRequest->Body(5));
	embMsgAns.SetBody(6,embMsgRequest->Body(6));
	embMsgAns.SetBody(7,embMsgRequest->Body(7));
	ui2uc.ui=temp_crc;
	embMsgAns.SetBody(8,ui2uc.uc[0]);
	embMsgAns.SetBody(9,ui2uc.uc[1]);
}


#define PARAMETERS_DISPLACEMENT (0x1000)
#define PARAMETERS_DISPLACEMENT1 (0x1100)


extern "C" void SavePortsFromNVRAM()
{
	unsigned char  *bt;
 	bt = (unsigned char *)(NVRAM_BASE);

	outportb(0x501 ,*(bt + PARAMETERS_DISPLACEMENT + 0x1));
	outportb(0x502 ,*(bt + PARAMETERS_DISPLACEMENT + 0x2));
	outportb(0x503 ,*(bt + PARAMETERS_DISPLACEMENT + 0x3));

	outportb(0x512 ,*(bt + PARAMETERS_DISPLACEMENT + 0x12));
	outportb(0x513 ,*(bt + PARAMETERS_DISPLACEMENT + 0x13));
	outportb(0x514 ,*(bt + PARAMETERS_DISPLACEMENT + 0x14));
	outportb(0x515 ,*(bt + PARAMETERS_DISPLACEMENT + 0x15));

	outportb(0x520 ,*(bt + PARAMETERS_DISPLACEMENT + 0x20));
	outportb(0x521 ,*(bt + PARAMETERS_DISPLACEMENT + 0x21));
	outportb(0x522 ,*(bt + PARAMETERS_DISPLACEMENT + 0x22));
	outportb(0x523 ,*(bt + PARAMETERS_DISPLACEMENT + 0x23));
	outportb(0x524 ,*(bt + PARAMETERS_DISPLACEMENT + 0x24));
	outportb(0x525 ,*(bt + PARAMETERS_DISPLACEMENT + 0x25));

//#ifdef PROG_PU_M_MUX
	 outportb3(0x37 ,*(bt + PARAMETERS_DISPLACEMENT1 + 0x37));
	 for(long i = 0; i < 0x10; i++)
	 {
	  outportb3((0x90 + i) ,*(bt + PARAMETERS_DISPLACEMENT1 + 0x90 + i));
	 }
//#endif //PROG_PU_M_MUX

}

extern "C" void SaveParameterToNVRAM(unsigned long current_port, unsigned char parameter)
{
  unsigned char  *bt;
  bt = (unsigned char *)(NVRAM_BASE);
  if((current_port >= 0x501) && (current_port <= 0x525))
  {
 //  printEthLongHex(parameter);
	*(bt + PARAMETERS_DISPLACEMENT + (current_port - 0x500)) = parameter;
  }
//#ifdef PROG_PU_M_MUX
  if((current_port < 0x100))
  {
	*(bt + PARAMETERS_DISPLACEMENT1 + current_port) = parameter;
  }
//#endif //PROG_PU_M_MUX
}

unsigned char test_ustir;							  
unsigned char pd_pm; //pd -0; pm - 1

void WritePort()
{

#ifdef TEST_PUMVA
	printfpd("\n\n\n\r____________> %02X", embMsgRequest->Body(0));
	printfpd(" %02X", embMsgRequest->Body(1));
	printfpd(" %02X", embMsgRequest->Body(2));
	printfpd(" %02X", embMsgRequest->Body(3));
	printfpd(" %02X", embMsgRequest->Body(4));
	printfpd(" %02X", embMsgRequest->Body(5));
	printfpd(" %02X", embMsgRequest->Body(6));

#endif


	if((embMsgRequest->Body(1)&0xC0)==0x80)
	{
		embMsg485Request_1.Init();
		embMsg485Request_1.SetAddr(0);//0x01);
		embMsg485Request_1.SetLength(4);//4
		embMsg485Request_1.SetBody(0,0x07);
		embMsg485Request_1.SetBody(1,embMsgRequest->Body(0));
		embMsg485Request_1.SetBody(2,embMsgRequest->Body(1)&0x3F);
		embMsg485Request_1.SetBody(3,embMsgRequest->Body(4));
		embMsg485Request_1.CalcCRC();
   //		embMsg485Request_1.SetReadyToSend();
		tBuffEmbMsg485Request_1.Add(embMsg485Request_1);

	}
	else
	{
		if((embMsgRequest->Body(1)&0xC0)==0xC0)
		{
			embMsg485Request_2.Init();
			embMsg485Request_2.SetAddr(0);//0x02);
			embMsg485Request_2.SetLength(4);//4
			embMsg485Request_2.SetBody(0,0x07);
			embMsg485Request_2.SetBody(1,embMsgRequest->Body(0));
			embMsg485Request_2.SetBody(2,embMsgRequest->Body(1)&0x3F);
			embMsg485Request_2.SetBody(3,embMsgRequest->Body(4));
			embMsg485Request_2.CalcCRC();
   //			embMsg485Request_2.SetReadyToSend();
			tBuffEmbMsg485Request_2.Add(embMsg485Request_2);

		}
		else
		{
		   if((embMsgRequest->Body(0)+(embMsgRequest->Body(1)<<8)) == TEST_PORT)
		   {
   #ifdef TEST_PUMVA
	printfp("\n\r: test");
   #endif

			  test_ustir = embMsgRequest->Body(4) & MASK_BIT_0;	 //1 get on test ustir
			   if(test_ustir)
			   {
                unEmb2TypeVer.emb2TypeVer.signature_hardware[0] |=  MASK_BIT_2;
				}
				else
				{
				 unEmb2TypeVer.emb2TypeVer.signature_hardware[0] &=  ~((unsigned long)MASK_BIT_2);
				}
		   }
		   else if((embMsgRequest->Body(0)+(embMsgRequest->Body(1)<<8)) == ATT_PORT)
		   {
		    #ifdef TEST_PUMVA
	printfp("\n\r: att");
   #endif

			  SetAttData(embMsgRequest->Body(4));	 //1 get on test ustir
			  SetAtt((unsigned char)GetAttData());
			  SetNeedWriteDevId();
			  unEmb2TypeVer.emb2TypeVer.signature_hardware[1] =  GetAttData() & 0xf;
   #ifdef TEST_PUMVA
	printfpd("\n\r: %02X", unEmb2TypeVer.emb2TypeVer.signature_hardware[1]);
   #endif

		   }
		   else
		   {
			outportb(embMsgRequest->Body(0)+(embMsgRequest->Body(1)<<8), embMsgRequest->Body(4));
			SaveParameterToNVRAM(embMsgRequest->Body(0)+(embMsgRequest->Body(1)<<8) , embMsgRequest->Body(4));
			embMsgAns.SetType(0x0A);
			embMsgAns.SetBody(0,embMsgRequest->Body(0));
			embMsgAns.SetBody(1,embMsgRequest->Body(1));
			embMsgAns.SetBody(2,0);
			embMsgAns.SetBody(3,8);
			embMsgAns.SetBody(4,embMsgRequest->Body(4));
			embMsgAns.SetLength(5);
			}

		}
	}
}

void ReadPort()
{

  //	 printEthLongHex(embMsgRequest->Body(1));
 //	embMsgRequest->Body(0)
 //	if((embMsg.Body(1)&0xC0)==0x80)
	if((embMsgRequest->Body(1)&0xC0)==0x80)
	{

  //	printEthLongHex(0x80);

		embMsg485Request_1.Init();
		embMsg485Request_1.SetAddr(0);//0x01);
		embMsg485Request_1.SetLength(3); //3
		embMsg485Request_1.SetBody(0,0x08);
		embMsg485Request_1.SetBody(1,embMsgRequest->Body(0));
		embMsg485Request_1.SetBody(2,embMsgRequest->Body(1)&0x3F);
		embMsg485Request_1.CalcCRC();
	 //	embMsg485Request_1.SetReadyToSend();
		   tBuffEmbMsg485Request_1.Add(embMsg485Request_1);

	}
	else
	{
		if((embMsgRequest->Body(1)&0xC0)==0xC0)
		{
			embMsg485Request_2.Init();
			embMsg485Request_2.SetAddr(0);//0x02);
			embMsg485Request_2.SetLength(3);//3
			embMsg485Request_2.SetBody(0,0x08);
			embMsg485Request_2.SetBody(1,embMsgRequest->Body(0));
			embMsg485Request_2.SetBody(2,embMsgRequest->Body(1)&0x3F);
			embMsg485Request_2.CalcCRC();
	   //		embMsg485Request_2.SetReadyToSend();
			   tBuffEmbMsg485Request_2.Add(embMsg485Request_2);

		}
		else
		{
			inportb(embMsgRequest->Body(0)+(embMsgRequest->Body(1)<<8));
			embMsgAns.SetType(0x0B);
			embMsgAns.SetBody(0,embMsgRequest->Body(0));
			embMsgAns.SetBody(1,embMsgRequest->Body(1));
			embMsgAns.SetBody(2,0);
			embMsgAns.SetBody(3,8);
			embMsgAns.SetBody(4,inportb(embMsgRequest->Body(0)+(embMsgRequest->Body(1)<<8)));
			embMsgAns.SetLength(5);
		}
	}
}
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
////////////////////  M A I N  //////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

//void main()

int rrr=0;
unsigned countUD1=0;
unsigned countUD2=0;

unsigned long ErrResSNMP;
unsigned char start_count;
unsigned char NeedWriteID;

unsigned long ch1ok, ch2ok, ch1bad, ch2bad, ansnum;
unsigned char Packet[32];

extern "C" void SetTestConfig()
{

                  Setudevconfig(0,1);		//1 device
				  Setudevconfig(1,0);		//rezerv
				  Setudevconfig(2,2);		//addr = 1 101117	   type = 2

				  Setudevconfig(3,1);		//upc type = 2 101117	addr = 1


                  SetNeedWriteDevId();
 


}
#define PACKET_SIZE	(31) //0....31
extern "C" unsigned char CheckPacket(unsigned char * packet)
{
 unsigned char checksum;
 checksum = 0;
 for(long i = 0; i < (PACKET_SIZE); i++)	  //
 {
  checksum += packet[i];
 }
  checksum += 1;
  if(checksum == packet[PACKET_SIZE])
  {
  /*
  printfp("\n\r+++");
  printfpd("ch:%X",checksum);
  printfpd(" p:%X",packet[PACKET_SIZE]);
  */
  	 return 1;
  }
  else
  {
  /*
  printfp("\n\r________________________");
  printfpd("ch:%X",checksum);
  printfpd(" p:%X",packet[PACKET_SIZE]);
  */
  	return 0;
  }
}

//unsigned char test_ustir;

//EmbMsg485Buffer tBuffEmbMsg485Request_1;
//EmbMsg485Buffer tBuffEmbMsg485Request_2;

 unsigned char send_keeper1, send_keeper2;

unsigned long send_to_485_cnt;
unsigned long send_to_mod_cnt;
unsigned long rcv_from_485_cnt;
unsigned long rcv_from_mod_cnt;




 extern "C" void Init_PU_M()
{

 send_to_485_cnt = 0;
 send_to_mod_cnt = 0;
 rcv_from_485_cnt = 0;
 rcv_from_mod_cnt = 0;



  send_keeper1 = send_keeper2 = 1;


 unsigned char tmp;
 test_ustir = 0;

 ch1ok = 0l;
 ch2ok = 0l;
 ch1bad = 0l;
 ch2bad = 0l;
 ansnum = 0l;

  NeedWriteID = 0;
 for(long in = 0; in < DEVCONFIG_QUANTITY; in++)
  {
  devans[in] = 0;
  devstate[in] = 0;
   for(i = 0; i < DEV_INFO_SIZE; i++)
            {
             statedev[in].byte[i] = 0; 
            }
  }


//__________________________________________________101108
ans1=0; 
 ans2=0;
 embMsg485Request.Init();
// addr485=1;
 ss=0;
 for(i=0; i<32; i++)
	{
		unStateRRL.stateRRL.ppu1_bytes[i] = 0;
		unStateRRL.stateRRL.ppu2_bytes[i] = 0;
	}
 unStateRRL.stateRRL.ver = 0x01;
 send41 = 0l; send42 =0l; received1 =0l; received2 =0l; good1 =0l; good2 =0l; bad1 =0l; bad2 =0l;




//__________________________________________________101108



#ifdef RS485_MSG_BUFF
	   tBuffRS485.Init();
	   time_lastsend_rs485 = 0;
	   flag_wait_rs485 = 0;
#endif //RS485_MSG_BUFF


#ifdef USE_RS125
 parse_status = 0l;
 rs125_send_timer = 0l;
for(im = 0; im < PERIOD_OF_KEEP; im++)
{
 oct_res_sub[im] = 0;
 oct_tr_sub[im] = 0;
 oct_res_ser[im] = 0;
 oct_tr_ser[im] = 0;
 }

// cnt_oct_res_sub = 0;
// cnt_oct_tr_sub = 0;
// cnt_oct_res_ser = 0;
// cnt_oct_tr_ser = 0;
#endif //


ErrResSNMP = 0l;
start_count = 0;
//_______________________________________________
 mode5A232E = 0;
 mode5A485E = 0;
 mode5A485 = 0;
//________________________________________________
 flagRequest=0;
 serr=0xFF;
 crc_temp=0;
 i=0;
 time1old=0;
 time1old485 = 0;
 time2old=0;
 flagsend = 0; //101203
 request1=0;
 request2=0;
 time3Marker=0;
 time3BlankTransit=0;
 time3BlankMod=0;
 flag_start_power = 0;
 markerWest=0;
 markerEast=0;
 ready_transit=0;
 ready_mod=0;
 dir=0; // 0 - "Transit->Mod", 1 - "Mod->Transit"
 old_ready_transit=0;
 old_ready_mod=0; // 0 - "Transit->Mod", 1 - "Mod->Transit"
 delete_msgWest=0;
 delete_msgEast=0;
 recieveWest=0;
 recieveEast=0;
 countSend=0;
 countRecv=0;
 time3highID=0;
 mode5A=0;
 mode5AWest=0;
 mode5AUp1=0;
 mode5AUp2=0;
 mode5AEast=0; 
 cycle=0;
 i232=0;
 iTrans=0;
 iMod=0;
 ans1=0;
 ans2=0;
 addr485=0;
 cur_req_pointer = 0;
 cur_req_quantity = 0;
 

 tlf_counter=0;
 tlf_state=0;
 presto = 0;
 ring_counter = 0;
 presto_time =0;
 wait_time =0;
 presto_ring =0;


//________________________________________________

AsciiInit();
EmbInit();	 //embrs232 embrs485
//_________________________________________________
/* 130521
  
   ab1[0] =	0x45;ab1[1] =0x60;ab1[2] =0xBF;ab1[3] =0x25;ab1[4] =0x52;ab1[5] =0x2A;ab1[6] =0x64;ab1[7] =0x3F;ab1[8] =0x89;ab1[9] =0x00;   // IM-Filter part 1 
   ab2[0] = 0x45;ab2[1] =0x68;ab2[2] =0x53;ab2[3] =0x02;ab2[4] =0x49;ab2[5] =0x8A;ab2[6] =0x07;ab2[7] =0xF6;ab2[8] =0x04;ab2[9] =0x00;   // IM-Filter part 2 
   ab3[0] =	0x45;ab3[1] =0x18;ab3[2] =0x08;ab3[3] =0xB0;ab3[4] =0xC5;ab3[5] =0x42;ab3[6] =0x3E;ab3[7] =0xFB;ab3[8] =0x72;ab3[9] =0x07;  // FRR-Filter    
   ab4[0] =	0x45;ab4[1] =0x28;ab4[2] =0x43;ab4[3] =0x8a;ab4[4] =0xBc;ab4[5] =0x27;ab4[6] =0x88;ab4[7] =0x00;ab4[8] =0x00;ab4[9] =0x00; // AR-Filter - ������ 20
   ab5[0] = 0x45;ab5[1] =0x48;ab5[2] =0x96;ab5[3] =0x38;ab5[4] =0x29;ab5[5] =0x96;ab5[6] =0xC9;ab5[7] =0x2B;ab5[8] =0x8B;ab5[9] =0x00; /// LPR-Filter       
   ab6[0] =	0x45;ab6[1] =0x20;ab6[2] =0x08;ab6[3] =0x90;ab6[4] =0x3F;ab6[5] =0xBC;ab6[6] =0x75;ab6[7] =0x28;ab6[8] =0x72;ab6[9] =0x07; // FRX-Filter       
   ab7[0] =	0x45;ab7[1] =0x30;ab7[2] =0xBE;ab7[3] =0x04;ab7[4] =0xB0;ab7[5] =0x27;ab7[6] =0x85;ab7[7] =0x50;ab7[8] =0xc0;ab7[9] =0x1a; // AX-Filter -������ 20
   ab8[0] =	0x45;ab8[1] =0x50;ab8[2] =0x96;ab8[3] =0x38;ab8[4] =0x29;ab8[5] =0xF5;ab8[6] =0xFA;ab8[7] =0x2B;ab8[8] =0x8B;ab8[9] =0x00; // LPX-Filter       
   ab9[0] =	0x45;ab9[1] =0x00;ab9[2] =0x30;ab9[3] =0x9B;ab9[4] =0x88;ab9[5] =0x80;ab9[6] =0x00;ab9[7] =0xC8;ab9[8] =0x32;ab9[9] =0x80; // TH-Filter part 1 
   ab10[0] = 0x45;ab10[1] =0x08;ab10[2] =0x80;ab10[3] =0x00;ab10[4] =0x80;ab10[5] =0x00;ab10[6] =0x67;ab10[7] =0x35;ab10[8] =0x5A;ab10[9] =0x01; // TH-Filter part 2 
   ab11[0] = 0x45;ab11[1] =0x10;ab11[2] =0x22;ab11[3] =0xAD;ab11[4] =0xB2;ab11[5] =0x2A;ab11[6] =0x24;ab11[7] =0xDC;ab11[8] =0x88;ab11[9] =0x00;  // TH-Filter part 3 
   ab12[0] = 0x45;ab12[1] =0x80;ab12[2] =0xF9;ab12[3] =0x29;ab12[4] =0x9B;ab12[5] =0x2A;ab12[6] =0x1A;ab12[7] =0x22;ab12[8] =0xC1;ab12[9] =0x32; // DC-Parameter     
   ab13[0] = 0x45;ab13[1] =0x70;ab13[2] =0x32;ab13[3] =0x3B;ab13[4] =0x1B;ab13[5] =0xC0;ab13[6] =0xC3;ab13[7] =0xB2;ab13[8] =0xAC;ab13[9] =0x02; // Ringing          
   ab14[0] = 0x45;ab14[1] =0x90;ab14[2] =0x3E;ab14[3] =0xE5;ab14[4] =0x2E;ab14[5] =0xBA;ab14[6] =0x81;ab14[7] =0x2A;ab14[8] =0xBA;ab14[9] =0x8A ; // LP-Filters       
   ab15[0] = 0x45;ab15[1] =0x88;ab15[2] =0x7B;ab15[3] =0x01;ab15[4] =0x2C;ab15[5] =0x7B;ab15[6] =0xB3;ab15[7] =0x47;ab15[8] =0x7B;ab15[9] =0x01; // Hook Levels      
   ab16[0] = 0x45;ab16[1] =0x78;ab16[2] =0x00;ab16[3] =0xC0;ab16[4] =0x6D;ab16[5] =0x7A;ab16[6] =0xB3;ab16[7] =0x48;ab16[8] =0x08;ab16[9] =0x00; // Ramp Generator   
   ab17[0] = 0x45;ab17[1] =0x58;ab17[2] =0x4A;ab17[3] =0x41;ab17[4] =0x34;ab17[5] =0xDB;ab17[6] =0x0E;ab17[7] =0xA2;ab17[8] =0x2A;ab17[9] =0x00; // TTX 
   ab18[0] = 0x45;ab18[1] =0x38;ab18[2] =0x33;ab18[3] =0x49;ab18[4] =0x22;ab18[5] =0x65;ab18[6] =0xBB;ab18[7] =0x00;ab18[8] =0x00;ab18[9] =0x00; // TG1              
   ab19[0] = 0x45;ab19[1] =0x40;ab19[2] =0x33;ab19[3] =0x49;ab19[4] =0x22;ab19[5] =0x65;ab19[6] =0xBB;ab19[7] =0x00;ab19[8] =0x00;ab19[9] =0x00; // TG2              
   ab20[0] = 0x45;ab20[1] =0x98;ab20[2] =0x00;ab20[3] =0x00;ab20[4] =0x00;ab20[5] =0x00;ab20[6] =0x00;ab20[7] =0x00;ab20[8] =0x00;ab20[9] =0x00;  // Rese20[8] =0x00;ab20[9] =0x00;  // Rese30;ab21[2] =0xBE;ab21[3] =0x04;ab21[4] =0xB0;ab21[5] =0x27; // AX-Filter -������ 29
   ab22[0] = 0x46;ab22[1] =0x30;ab22[2] =0x07;ab22[3] =0x10;ab22[4] =0x79;ab22[5] =0x11;ab22[6] =0x02;ab22[7] =0xFB;ab22[8] =0x60;ab22[9] =0x00;ab22[10] =0x00;ab22[11] =0x00 ; //DTMF POP
   ab23[0] = 0x46;ab23[1] =0x4A;ab23[2] =0x00 ;
   ab24[0] = 0x44;ab24[1] =0x21;ab24[2] =0x00;ab24[3] = 0x16;ab24[4] = 0x06;ab24[5] = 0x00;ab24[6] = 0x00;ab24[7] =  0x16;ab24[8] = 0x06;ab24[9] = 0x00 ; //pcmr;ab24[0] =pcmx- line A
   ab25[0] = 0x44;ab25[1] =0x1A;ab25[2] =0x00 ; // DSCR
   ab26[0] = 0x44;ab26[1] =0x2B;ab26[2] =0x04 ; //TSTR3
   ab27[0] = 0x44;ab27[1] =0x15;ab27[2] =0x01;ab27[3] = 0x20;ab27[4] = 0x07;ab27[5] = 0x00;ab27[6] = 0x03;// bcr1-5
   ab28[0] = 0x44;ab28[1] =0x06;ab28[2] =0x80;  //XCR
   ab29[0] = 0x44;ab29[1] =0x1c;ab29[2] =0x00; //LMCR1
   ab30[0] = 0x4c;ab30[1] =0x21;ab30[2] =0x80;ab30[3] = 0x96;ab30[4] = 0x86;ab30[5] = 0x80;ab30[6] = 0x80;ab30[7] =  0x96;ab30[8] = 0x86;ab30[9] = 0x80; //pcmr;ab6[0] =pcmx- line B
// AKTIV	
   a22[0] =	 0x02;  // AKTIV mode -- ����������� ���������
   a221[0] = 0x44;a221[1] =0x1c;a221[2] =0x22; // LMCR1
   a222[0] = 0x44;a222[1] =0x1A;a222[2] =0x00; // dscr
//outportb(0x511;ab6[0] = 0x04);ab6[0] = // off hook
// PAUSE
   a26[0] =	0x02; // RING pause MODE -- ��������� ���
   a261[0] = 0x44;a261[1] =0x1c;a261[2] =0xAA; // LMCR1
   a262[0] = 0x44;a262[1] =0x1A;a262[2] =0x05; // dscr
//outportb(0x511;ab6[0] = 0x04);ab6[0] = // off hook
// PAUSE 2
   a263[0] = 0x02; // RING pause MODE -- ��������� ���
   a264[0] = 0x44;a264[1] =0x1c;a264[2] =0xAA; // LMCR1
   a265[0] = 0x44;a265[1] =0x1A;a265[2] =0x05; // dscr
//outportb(0x511;ab6[0] = 0x00);ab6[0] = // off hook
// RING
   a272[0] = 0x05; // RING burst MODE -- ������ ������
   a271[0] = 0x44;a271[1] =0x1c;a271[2] =0x22;  // LMCR1
   a27[0] =	 0x44;a27[1] =0x1A;a27[2] =0x00; // dscr
//outportb(0x511;ab6[0] = 0x00);ab6[0] = // �n hook
// WAIT
   a28[0] = 0x07; // power dnv mode -- �������� �������� ������
//outportb(0x511;ab6[0] = 0x00);ab6[0] = // on hook
   aa[0] =  0xC4;aa[1] =0x07;aa[2] =0xFF;aa[3] =0x00;aa[4] =0x00;aa[5] =0x00;aa[6] =0x00; 
//_____________________________________________

	  */


//__________________________________________________<< init _tlf

//void InitMain()
//{

	unEmb2NetStat.emb2NetStat.allPacketRecv=0;	// +
	unEmb2NetStat.emb2NetStat.genMarker=0;			// +
	unEmb2NetStat.emb2NetStat.highID=0;         // +
	unEmb2NetStat.emb2NetStat.requestMarker=0;  // +
	unEmb2NetStat.emb2NetStat.selfPacketRecv=0; // +
	unEmb2NetStat.emb2NetStat.selfPacketSend=0; // +

	unStateBMD155.stateBMD155.count_block=0;
	unStateBMD155.stateBMD155.count_no_correct_block1=0;
	unStateBMD155.stateBMD155.count_no_correct_block2=0;
	unStateBMD155.stateBMD155.count_no_correct_result=0;
	unStateBMD155.stateBMD155.count_notRS1=0;
	unStateBMD155.stateBMD155.count_notRS2=0;
	unStateBMD155.stateBMD155.demPI=0;
	unStateBMD155.stateBMD155.loopPI=0;
	unStateBMD155.stateBMD155.statePI=0;

	unEmb2TypeVer.emb2TypeVer.softVer    = SOFT_VER;  //add suppourt protocol	rs232 from ethernet protocol 888
//later	unEmb2TypeVer.emb2TypeVer.type       = 0x0902;
	unEmb2TypeVer.emb2TypeVer.ctrlNumber = SelfID();
	unEmb2TypeVer.emb2TypeVer.ctrlYear   = SelfYear();

#ifndef COUNT_BUFF_ERR
	unEmb2TypeVer.emb2TypeVer.ctrlVer1   = SelfVer1();
	unEmb2TypeVer.emb2TypeVer.ctrlVer2   = SelfVer2();
#else
	unEmb2TypeVer.emb2TypeVer.ctrlVer1   = 0;
	unEmb2TypeVer.emb2TypeVer.ctrlVer2   = 0;
#endif

	for(i=0; i<16; i++)
	{
		unEmb2TypeVer.emb2TypeVer.signature_software[i] = 0;
		unEmb2TypeVer.emb2TypeVer.signature_hardware[i] = 0;
	}

  /*
	unEmb2TypeVer.emb2TypeVer.signature_hardware[0] = inportb(0x501);
	unEmb2TypeVer.emb2TypeVer.signature_hardware[1] = inportb(0x502);
	unEmb2TypeVer.emb2TypeVer.signature_hardware[2] = inportb(0x514);
 */
		/* 130521
		SavePortsFromNVRAM();

//___________________________________________________________________________
		unEmb2TypeVer.emb2TypeVer.signature_hardware[0] = inportb(0x501);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[1] = inportb(0x502);
//		unEmb2TypeVer.emb2TypeVer.signature_hardware[2] = inportb(0x514);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[2] = inportb(0x503);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[3] = inportb(0x512);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[4] = inportb(0x513);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[5] = inportb(0x514);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[6] = inportb(0x515);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[7] = 0;//inportb(0x507); // reserv
		unEmb2TypeVer.emb2TypeVer.signature_hardware[8] = 0;//inportb(0x508); // reserv
		unEmb2TypeVer.emb2TypeVer.signature_hardware[9] = 0; // reserv
		unEmb2TypeVer.emb2TypeVer.signature_hardware[10] = inportb(0x520);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[11] = inportb(0x521);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[12] = inportb(0x522);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[13] = inportb(0x523);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[14] = inportb(0x524);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[15] = inportb(0x525);
		*/
//_____________________________________________________________________________

	tmp =  read_nvram_char(RESTARTS_NVRAM_ADDRESS);
	write_nvram_char(RESTARTS_NVRAM_ADDRESS, (tmp + 1));


 //	bt = (unsigned char far*)0x80000000;
	bt = (unsigned char *)(NVRAM_BASE);


	unEmb2TypeVer.emb2TypeVer.signature_software[0] = *bt;
	unEmb2TypeVer.emb2TypeVer.signature_software[1] = *(bt+1);
	unEmb2TypeVer.emb2TypeVer.signature_software[2] = *(bt+2);
	unEmb2TypeVer.emb2TypeVer.signature_software[3] = *(bt+3);
	unEmb2TypeVer.emb2TypeVer.signature_software[4] = *(bt+4);
	unEmb2TypeVer.emb2TypeVer.signature_software[5] = *(bt+5);
	unEmb2TypeVer.emb2TypeVer.signature_software[6] = *(bt+6);
	unEmb2TypeVer.emb2TypeVer.signature_software[7] = *(bt+7);
	unEmb2TypeVer.emb2TypeVer.signature_software[8] = *(bt+8);
	unEmb2TypeVer.emb2TypeVer.signature_software[9] = *(bt+9);
	unEmb2TypeVer.emb2TypeVer.signature_software[10] = *(bt+10);
	unEmb2TypeVer.emb2TypeVer.signature_software[11] = *(bt+11);
	unEmb2TypeVer.emb2TypeVer.signature_software[12] = *(bt+12);
	unEmb2TypeVer.emb2TypeVer.signature_software[13] = *(bt+13);
	unEmb2TypeVer.emb2TypeVer.signature_software[14] = *(bt+14);
	unEmb2TypeVer.emb2TypeVer.signature_software[15] = *(bt+15);
//}

//__________________________________________________





 //port!!!!!	outport(0xFFA4, 0x0077);
//	outportb(0x6FF,inportb(0x6FF)|0x10);
//port	unsigned countUD1=0;
//port	unsigned countUD2=0;

 countUD1=0;	//port
 countUD2=0;   //port

///////  ����� �������  ///////
///////////////////////////////

	tBuffEmbMsgWest.Init();
	tBuffEmbMsgEast.Init();
	rBuffEmbMsg.Init();
 //	embMsgTemp.Init();
	embSerialACT155.Init();	  //hier init irq

//--------------------------------------------------  >> add  init
 //not need init	EmbTimerCallback embTimerCallback0;

//ok 	EmbMsgBuffer rBuffEmbMsg;	
//ok	EmbMsgBuffer tBuffEmbMsgWest;
//ok	EmbMsgBuffer tBuffEmbMsgEast;
//ok    EmbSerialPU_M embSerialACT155;


	 embMsg.Init();
     embMsgWest.Init();
	 embMsgEast.Init();
	 embMsgAns.Init();
//	 EmbMsg embMsgTemp;
     embMsg485.Init();	 //added 090406
	 embMsg232.Init();	 //added 090406
//	 embMsg232E.Init();	 //added 090406
	 embMsg485E.Init();	  //added 090406


	embMsg485_1.Init();
    embMsg485_2.Init();
    embMsg485Request_1.Init();
	embMsg485Request_2.Init();

    tBuffEmbMsg485Request_1.Init();
	tBuffEmbMsg485Request_2.Init();


//ok in embinit	EmbRS232 embRS232;
//ok in embinit EmbRS485 embRS485;
	
  
 //-------------------------------------------------	<< add




  //	ResetWatchDog();
//	embIndicator.Init();
//	embSerialACT155.Init();
  

//090406 this maked in embinit	embRS232.Init(384);		// ������������� RS232 �� �������� 38400 ����/�

///////////////////////////////////////////////////////////////////////////////
	embTimer.Init(10); // *0,1 ms ���� ���������� ���������� �� �������
	embTimerCallback0.callback = &Callback0;
	embTimerCallback0.interval = 1; // ����� ������� 1 ��� �� N ������������ �������
	embTimerCallback0.count = 0;
	embTimer.SetCallBack0(&embTimerCallback0);
//////////////////////
//130521
	  /*130521
	InitTLF();
//	Ring();
	for(tlf_counter=0; tlf_counter<6; tlf_counter++) tlf_number[tlf_counter] = 0xFF;
	tlf_counter=0;

	   */
	for(i=0; i<16; i++)
	{
		send1[i]=0;
		send2[i]=0;
		unStateBMD155.stateBMD155.ppu1_bytes[i]=0;
		unStateBMD155.stateBMD155.ppu2_bytes[i]=0;
		unStateBMD155.stateBMD155.state=0;
	}
//// �������� ����������� ������ ////

 //130521	for(i=0; i<9; i++) powerInFar[i]=0;

   //port	int rrr=0;
	rrr=0; //port

///////  �������� ����� ������� 0x95 - 0x00  ///////
///////  "�����" 0x95 - 0x01
////////////////////////////////////////////////
   //	Enable(); // ��������� ��� ����������
	send1[0]=12;
	send2[0]=12;

   
	time3Marker = time3;

	unStateRRL.stateRRL.ver = 0x01;
	unStateRRL.stateRRL.state = 0x01;

//130523	Wait();
//	Ring();
//	Pause();
	presto_time = time1;


 //port 	InitMain();
// 526-527	������� ������ ����� �����������	16 ���
// 528-52A	������� ������, ������������ �� � 1 ������	24 ���
// 52B-52D	������� ������, ������������ �� � 2 ������	24 ���
// 52E-52F	������� ������ �� ������������ �� � 1 ������	16 ���
// 530-531	������� ������ �� ������������ �� � 2 ������	16 ���
// 532-533	������� ����� �������� �������	16 ���
	 /* 130521
	count_no_correct_result = (unsigned)inportb(0x526) + ((unsigned)inportb(0x527)<<8);	
	count_block = (unsigned)inportb(0x532) + ((unsigned)inportb(0x533)<<8);
	count_notRS1 = (unsigned)inportb(0x52E) + ((unsigned)inportb(0x52F)<<8);
	count_notRS2 = (unsigned)inportb(0x530) + ((unsigned)inportb(0x531)<<8); 
	count_no_correct_block1 = (unsigned)inportb(0x528) + ((unsigned)inportb(0x529)<<8) + ((unsigned)inportb(0x52A)<<16);
	count_no_correct_block2 = (unsigned)inportb(0x52B) + ((unsigned)inportb(0x52C)<<8) + ((unsigned)inportb(0x52D)<<16);
		  */
	unStatePUM.statePUM.ver = 0x01;
	unStatePUM.statePUM.reserv = 0x20;

// ���� 0�501 ��� ���		
//1	"0" - � MUX;  "1" - ��� MUX	������� ��������������
//2		
//3		
//4		
//5	"1" - 2�, "2" - 4�, "3" - 8�, "4" - 17�, "5" - 34�	�������� ������
//6		
//7		
//8	
//#ifdef PROG_PU_M_MUX
	 /*130521
	if(inportb(0x501)&0x01)
	{
		switch(inportb(0x501)&0xF0)
		{
			case 0x10: unEmb2Mux34.emb2Mux34.numE1 = 1; break;
			case 0x20: unEmb2Mux34.emb2Mux34.numE1 = 2; break;
			case 0x30: unEmb2Mux34.emb2Mux34.numE1 = 4; break;
			case 0x40: unEmb2Mux34.emb2Mux34.numE1 = 8; break;
			case 0x50: unEmb2Mux34.emb2Mux34.numE1 = 16; break;
			default: unEmb2Mux34.emb2Mux34.numE1 = 0;
		}
	}
	else 
	{
		unEmb2Mux34.emb2Mux34.numE1 = 0;
	}

	for(i=0; i<unEmb2Mux34.emb2Mux34.numE1; i++)
	{
		unEmb2Mux34.emb2Mux34.ctrl_e1[i] = 0;
		unEmb2Mux34.emb2Mux34.state_e1[i] = 0;
	}
	*/
//#endif //PROG_PU_M_MUX

  IOs_Init();// init pins 96 and 97

   if( IO_Pin71_Read() )	//
   {
   unEmb2TypeVer.emb2TypeVer.type       =  0x0903;

  	 unEmb2TypeVer.emb2TypeVer.signature_hardware[0] &= ~(MASK_BIT_1);
     }
   else	  //pm
   {
   unEmb2TypeVer.emb2TypeVer.type       =  0x0904;

   	 unEmb2TypeVer.emb2TypeVer.signature_hardware[0] |= MASK_BIT_1;
   }
 //  unEmb2TypeVer.emb2TypeVer.signature_hardware[1] =  GetAttData() & 0xf;
 SetPin100ToZero();		//work


} //add this

extern "C" void SetNeedWriteDevId(void)
{

  NeedWriteID = 1;
}


extern "C" void ClearNeedWriteDevId(void)
{

  NeedWriteID = 0;
}

extern "C" unsigned char GetNeedWriteDevId(void)
{
//static unsigned long DelayWriteTime;



  return NeedWriteID;
}



extern "C" void PU_M()
{
 static unsigned long timer_read;
  timer_read++;

  if(!(timer_read % 1000l))
  {

  // if( IO_Pin97_Read())	//work
	
   if(!pd_pm)
   {
 //  if( IO_Pin91_Read() && (!test_ustir) && (GetTestMode() != 0x22))	//work
   if( (!test_ustir) && (GetTestMode() != 0x22))	//work
   {
     //hier set pin 96	to work = zero
 //	 unEmb2TypeVer.emb2TypeVer.signature_hardware[0] &= ~(MASK_BIT_0);
	 SetPin100ToZero();
	  unEmb2TypeVer.emb2TypeVer.signature_hardware[0] &= ~(MASK_BIT_0);

   }
   else	  //
   {
	 //hier set pin 96	to test = one
//#ifndef DO_NOT_USE_GEN
	 SetPin100ToOne();
//#endif
 //	 unEmb2TypeVer.emb2TypeVer.signature_hardware[0] |= MASK_BIT_0;
  unEmb2TypeVer.emb2TypeVer.signature_hardware[0] |= MASK_BIT_0;

   }
/*
 if( IO_Pin71_Read())	//work
   {
     //hier set pin 96	to work = zero
	 unEmb2TypeVer.emb2TypeVer.signature_hardware[0] &= ~(MASK_BIT_0);
	}
   else	  //test
   {
	 //hier set pin 96	to test = one
   	 unEmb2TypeVer.emb2TypeVer.signature_hardware[0] |= MASK_BIT_0;
   }

*/
   } //pd_pm for pd only
	 





  }
	   /*
	uemb4pumfabinfo.emb4pumfabinfo.errUp1 	 = inportb(0x36);	 //celling in up
	uemb4pumfabinfo.emb4pumfabinfo.errUp2 	 = inportb(0x37);
	uemb4pumfabinfo.emb4pumfabinfo.errDown1 = inportb(0x34);	 //celling in down
	uemb4pumfabinfo.emb4pumfabinfo.errDown2 = inportb(0x35);

	   */



	long err_tmp_now = 0l;
	static long err_tmp_prev1 = 0l;
	static long err_tmp_prev3 = 0l;
    static long err_tmp_prev4 = 0l;



   if(GetNeedWriteDevId())
		   {
	   //	   printf("\n\r Write!!"); //t
			 WriteDevId();
			 ClearNeedWriteDevId();
		   }
  /* 130521
#ifdef USE_RS125

if ((time1 - rs125_send_timer) > RS125_SEND_TIMEOUT)
{
  rs125_send_timer =  time1;
 SendRequestStcs(ZERO_OFFSET, REP_MAX_LEN);

}

if (rs125_send_timer > time1)
{
  rs125_send_timer =  time1;
}



#endif // USE_RS125

	  */
//#ifdef PROG_PU_M_MUX
		 /* 130521
		for(i=0; i<unEmb2Mux34.emb2Mux34.numE1; i++)
		{
			unEmb2Mux34.emb2Mux34.ctrl_e1[i]  = inportb3(0x090+i);
			unEmb2Mux34.emb2Mux34.state_e1[i] = inportb3(0x080+i);
		}
		*/
//#endif //PROG_PU_M_MUX

////
/*
		unEmb2TypeVer.emb2TypeVer.signature_hardware[0] = inportb(0x501);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[1] = inportb(0x502);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[2] = inportb(0x514);

  //		bt = (unsigned char far*)0x80000000;
		 bt = (unsigned char *)(NVRAM_BASE);



		unEmb2TypeVer.emb2TypeVer.signature_software[0] = *bt; // cfg PUM
		unEmb2TypeVer.emb2TypeVer.signature_software[1] = *(bt+1); // tlf - �����
		unEmb2TypeVer.emb2TypeVer.signature_software[2] = *(bt+2);
		unEmb2TypeVer.emb2TypeVer.signature_software[3] = *(bt+3);
		unEmb2TypeVer.emb2TypeVer.signature_software[4] = *(bt+4);
		unEmb2TypeVer.emb2TypeVer.signature_software[5] = *(bt+5);
		unEmb2TypeVer.emb2TypeVer.signature_software[6] = *(bt+6);
		unEmb2TypeVer.emb2TypeVer.signature_software[7] = *(bt+7);
		unEmb2TypeVer.emb2TypeVer.signature_software[8] = *(bt+8);
		unEmb2TypeVer.emb2TypeVer.signature_software[9] = *(bt+9);
		unEmb2TypeVer.emb2TypeVer.signature_software[10] = *(bt+10);
		unEmb2TypeVer.emb2TypeVer.signature_software[11] = *(bt+11);
		unEmb2TypeVer.emb2TypeVer.signature_software[12] = *(bt+12);
		unEmb2TypeVer.emb2TypeVer.signature_software[13] = *(bt+13);
		unEmb2TypeVer.emb2TypeVer.signature_software[14] = *(bt+14);
		unEmb2TypeVer.emb2TypeVer.signature_software[15] = *(bt+15);
  */

//_________________________________________________________________________
//___________________________________________________________________________
	/* 130521
		unEmb2TypeVer.emb2TypeVer.signature_hardware[0] = inportb(0x501);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[1] = inportb(0x502);
//		unEmb2TypeVer.emb2TypeVer.signature_hardware[2] = inportb(0x514);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[2] = inportb(0x503);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[3] = inportb(0x512);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[4] = inportb(0x513);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[5] = inportb(0x514);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[6] = inportb(0x515);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[7] = 0;//inportb(0x507); // reserv
		unEmb2TypeVer.emb2TypeVer.signature_hardware[8] = 0;//inportb(0x508); // reserv
		unEmb2TypeVer.emb2TypeVer.signature_hardware[9] = 0; // reserv
		unEmb2TypeVer.emb2TypeVer.signature_hardware[10] = inportb(0x520);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[11] = inportb(0x521);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[12] = inportb(0x522);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[13] = inportb(0x523);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[14] = inportb(0x524);
		unEmb2TypeVer.emb2TypeVer.signature_hardware[15] = inportb(0x525);
		 */
		 //_____________________________________________________________________________


 //	bt = (unsigned char far*)0x80000000;
	bt = (unsigned char *)(NVRAM_BASE);


	unEmb2TypeVer.emb2TypeVer.signature_software[0] = *bt;
	unEmb2TypeVer.emb2TypeVer.signature_software[1] = *(bt+1);
	unEmb2TypeVer.emb2TypeVer.signature_software[2] = *(bt+2);
	unEmb2TypeVer.emb2TypeVer.signature_software[3] = *(bt+3);
	unEmb2TypeVer.emb2TypeVer.signature_software[4] = *(bt+4);
	unEmb2TypeVer.emb2TypeVer.signature_software[5] = *(bt+5);
	unEmb2TypeVer.emb2TypeVer.signature_software[6] = *(bt+6);
	unEmb2TypeVer.emb2TypeVer.signature_software[7] = *(bt+7);
	unEmb2TypeVer.emb2TypeVer.signature_software[8] = *(bt+8);
	unEmb2TypeVer.emb2TypeVer.signature_software[9] = *(bt+9);
	unEmb2TypeVer.emb2TypeVer.signature_software[10] = *(bt+10);
	unEmb2TypeVer.emb2TypeVer.signature_software[11] = *(bt+11);
	unEmb2TypeVer.emb2TypeVer.signature_software[12] = *(bt+12);
	unEmb2TypeVer.emb2TypeVer.signature_software[13] = *(bt+13);
	unEmb2TypeVer.emb2TypeVer.signature_software[14] = *(bt+14);
	unEmb2TypeVer.emb2TypeVer.signature_software[15] = *(bt+15);
//}

//__________________________________________________




//_________________________________________________________________________


////
// 526-527	������� ������ ����� �����������	16 ���
// 528-52A	������� ������, ������������ �� � 1 ������	24 ���
// 52B-52D	������� ������, ������������ �� � 2 ������	24 ���
// 52E-52F	������� ������ �� ������������ �� � 1 ������	16 ���
// 530-531	������� ������ �� ������������ �� � 2 ������	16 ���
// 532-533	������� ����� �������� �������	16 ���
 /*
	err_tmp = (unsigned)inportb(0x526) + ((unsigned)inportb(0x527)<<8);
	if(err_tmp>=count_no_correct_result) unStateBMD155.stateBMD155.count_no_correct_result = err_tmp - count_no_correct_result;
	else unStateBMD155.stateBMD155.count_no_correct_result = err_tmp - count_no_correct_result + 0x10000;
	count_no_correct_result = err_tmp;
	unStatePUM.statePUM.ulErrOut = err_tmp;
//	if(err_tmp>=count_no_correct_result) count_no_correct_result = err_tmp - count_no_correct_result;
//	else count_no_correct_result = count_no_correct_result - err_tmp;

	err_tmp = (unsigned)inportb(0x532) + ((unsigned)inportb(0x533)<<8);
	if(err_tmp>=count_block) unStateBMD155.stateBMD155.count_block = err_tmp - count_block;
	else unStateBMD155.stateBMD155.count_block = err_tmp - count_block + 0x10000;
	count_block = err_tmp;
	unStatePUM.statePUM.ulBlock = err_tmp;
//	if(err_tmp>=count_block) count_block = err_tmp - count_block;
//	else count_block = count_block - err_tmp;

	err_tmp = (unsigned)inportb(0x52E) + ((unsigned)inportb(0x52F)<<8);
	if(err_tmp>=count_notRS1)	unStateBMD155.stateBMD155.count_notRS1 = err_tmp - count_notRS1;
	else unStateBMD155.stateBMD155.count_notRS1 = err_tmp - count_notRS1 + 0x10000;
	count_notRS1 = err_tmp;
	unStatePUM.statePUM.ulErrAfterRS1 = err_tmp;
//	if(err_tmp>=count_notRS1)  count_notRS1= err_tmp - count_notRS1;
//	else count_notRS1 = count_notRS1 - err_tmp;

	err_tmp = (unsigned)inportb(0x530) + ((unsigned)inportb(0x531)<<8); 
	if(err_tmp>=count_notRS2) unStateBMD155.stateBMD155.count_notRS2 = err_tmp - count_notRS2;//count_notRS2;
	else unStateBMD155.stateBMD155.count_notRS2 = err_tmp - count_notRS2 + 0x10000;
	count_notRS2 = err_tmp;
	unStatePUM.statePUM.ulErrAfterRS2 = err_tmp;
//	if(err_tmp>=count_notRS2) count_notRS2 = err_tmp - count_notRS2;
//	else count_notRS2 = count_notRS2 - err_tmp;

	err_tmp = (unsigned)inportb(0x528) + ((unsigned)inportb(0x529)<<8) + ((unsigned long)inportb(0x52A)<<16);
	if(err_tmp>=count_no_correct_block1) unStateBMD155.stateBMD155.count_no_correct_block1 = err_tmp - count_no_correct_block1;
	else unStateBMD155.stateBMD155.count_no_correct_block1 = err_tmp - count_no_correct_block1 + 0x1000000;
	count_no_correct_block1 = err_tmp;
	unStatePUM.statePUM.ulErrBeforeRS1 = err_tmp;

//	if(err_tmp>=count_no_correct_block1) count_no_correct_block1 = err_tmp - count_no_correct_block1;
//	else count_no_correct_block1 = count_no_correct_block1 - err_tmp;

	err_tmp = (unsigned)inportb(0x52B) + ((unsigned)inportb(0x52C)<<8) + ((unsigned long)inportb(0x52D)<<16);
	if(err_tmp>=count_no_correct_block2) unStateBMD155.stateBMD155.count_no_correct_block2 = err_tmp - count_no_correct_block2;
	else unStateBMD155.stateBMD155.count_no_correct_block2 = err_tmp - count_no_correct_block2 + 0x1000000;
	count_no_correct_block2 = err_tmp; 
	unStatePUM.statePUM.ulErrBeforeRS2 = err_tmp;
//	if(err_tmp>=count_no_correct_block2) count_no_correct_block2 = err_tmp - count_no_correct_block2;
//	else count_no_correct_block2 = count_no_correct_block2 - err_tmp;
*/

//________________________________________________________________________________>> from bmd155
 /* 130521
   err_tmp = (unsigned short)inportb(0x526) + ((unsigned short)inportb(0x527)<<8);
   err_tmp_now =   err_tmp -  err_tmp_prev1;
   err_tmp_prev1 = err_tmp;
   if(err_tmp >= count_no_correct_result) 
	unStateBMD155.stateBMD155.count_no_correct_result = err_tmp - count_no_correct_result;
	else
	unStateBMD155.stateBMD155.count_no_correct_result = (err_tmp  + 0x10000 ) - count_no_correct_result ;
 
	count_no_correct_result = err_tmp;
	unStatePUM.statePUM.ulErrOut = err_tmp;

 	if(!start_count)
 	{start_count = 1;}
 	else
 	{
	ErrResSNMP += unStateBMD155.stateBMD155.count_no_correct_result;
 	}

	err_tmp = (unsigned short)inportb(0x532) + ((unsigned short)inportb(0x533)<<8);
   	if(err_tmp>=count_block)
   	 unStateBMD155.stateBMD155.count_block = err_tmp - count_block;
	else 
	unStateBMD155.stateBMD155.count_block = (err_tmp + 0x10000 ) - count_block ;
	count_block = err_tmp;
	unStatePUM.statePUM.ulBlock = err_tmp;

	err_tmp = (unsigned short)inportb(0x52E) + ((unsigned short)inportb(0x52F)<<8);
	err_tmp_now =   err_tmp -  err_tmp_prev3;
    err_tmp_prev3 = err_tmp;
 	if(err_tmp >= count_notRS1)
 	unStateBMD155.stateBMD155.count_notRS1 = err_tmp - count_notRS1;
	else
	unStateBMD155.stateBMD155.count_notRS1 = (err_tmp + 0x10000) - count_notRS1 ;
	count_notRS1 = err_tmp;
	unStatePUM.statePUM.ulErrAfterRS1 = err_tmp;

	err_tmp = (unsigned short)inportb(0x530) + ((unsigned short)inportb(0x531)<<8); 
	err_tmp_now =   err_tmp -  err_tmp_prev4;
    err_tmp_prev4 = err_tmp;
 	if	(err_tmp>=count_notRS2)
 	 unStateBMD155.stateBMD155.count_notRS2 = err_tmp - count_notRS2;//count_notRS2;
	else 
 	unStateBMD155.stateBMD155.count_notRS2 = (err_tmp + 0x10000) - count_notRS2 ;

	count_notRS2 = err_tmp;
	unStatePUM.statePUM.ulErrAfterRS2 = err_tmp;

	err_tmp = (unsigned short)inportb(0x528) + ((unsigned short)inportb(0x529)<<8) + ((unsigned long)inportb(0x52A)<<16);

	if(err_tmp>=count_no_correct_block1)
	unStateBMD155.stateBMD155.count_no_correct_block1 = err_tmp - count_no_correct_block1;
	else 

	unStateBMD155.stateBMD155.count_no_correct_block1 = (err_tmp + 0x1000000) - count_no_correct_block1 ;
	count_no_correct_block1 = err_tmp;
	unStatePUM.statePUM.ulErrBeforeRS1 = err_tmp;

	err_tmp = (unsigned short)inportb(0x52B) + ((unsigned short)inportb(0x52C)<<8) + ((unsigned long)inportb(0x52D)<<16);

	if(err_tmp	>= count_no_correct_block2)
	 unStateBMD155.stateBMD155.count_no_correct_block2 = err_tmp - count_no_correct_block2;
	else
	unStateBMD155.stateBMD155.count_no_correct_block2 = (err_tmp + 0x1000000) - count_no_correct_block2 ;
 	count_no_correct_block2 = err_tmp; 
	unStatePUM.statePUM.ulErrBeforeRS2 = err_tmp;
   */
//________________________________________________________________________________,, from bmd 155
/* 130521
//#ifdef PROG_PU_M_MUX

	unEmb2Mux34.emb2Mux34.e3 = inportb(0x522);
	unEmb2Mux34.emb2Mux34.err_e3 = (unsigned)inportb(0x526) + ((unsigned)inportb(0x527)<<8);
	unEmb2Mux34.emb2Mux34.reserv[0] = inportb(0x524);
	unEmb2Mux34.emb2Mux34.reserv[1] = inportb3(0x037);
	unEmb2Mux34.emb2Mux34.softVer = 1;
	unEmb2Mux34.emb2Mux34.type = 1;

//#endif //PROG_PU_M_MUX


	unStatePUM.statePUM.state[0] = inportb(0x520);
	unStatePUM.statePUM.state[1] = inportb(0x521);
	unStatePUM.statePUM.state[2] = inportb(0x522);
	unStatePUM.statePUM.state[3] = inportb(0x523); /// ������
	unStatePUM.statePUM.state[4] = inportb(0x524);
	unStatePUM.statePUM.state[5] = inportb(0x525);
	unStatePUM.statePUM.state[6] = inportb(0x536);
	unStatePUM.statePUM.state[7] = inportb(0x537);
	unStatePUM.statePUM.state[8] = inportb(0x538);
	unStatePUM.statePUM.state[9] = inportb(0x539);
//#ifdef PROG_PU_M_MUX
	unStatePUM.statePUM.state[10] = inportb3(0x036); // �����
	unStatePUM.statePUM.state[11] = inportb3(0x037); // ����� �1 ��� ��������� ���
	unStatePUM.statePUM.state[12] = inportb3(0x028); // ������� ��� ��. ����
	unStatePUM.statePUM.state[13] = inportb3(0x029); // ������� ��� ��. ����
	unStatePUM.statePUM.state[14] = inportb3(0x02A); // ������� ��� ��. ����

*/
//#else
   /*
	unStatePUM.statePUM.state[10] = 0; // �����
	unStatePUM.statePUM.state[11] = 0; // ����� �1 ��� ��������� ���
	unStatePUM.statePUM.state[12] = 0; // ������� ��� ��. ����
	unStatePUM.statePUM.state[13] = 0; // ������� ��� ��. ����
	unStatePUM.statePUM.state[14] = 0; // ������� ��� ��. ����
	*/
//#endif



	unStatePUM.statePUM.state[15] = 0;

/*130521
		if(time1 - wait_time >= 40) 
		{
			wait_time = time1;
			Read();
		if(aaa[3]&0x40) 
		{
			if(tlf_state) 
			{
				Active();
				tlf_counter = 0; presto=0; presto_ring = 0; presto_time = 0;
			}
			tlf_state = 0;
		}
		else 
		{
			if(!tlf_state)
			{
				Wait();
				tlf_state=1;
			}
			if((aaa[3]&0x80)&&(aaa[5]&0x80))
			{
//	unsigned char tlf_number[4];
//	unsigned char tlf_counter=0;
//					Ring();
				switch(aaa[5]&0xFC)
				{
					case 196: tlf_counter++; tlf_number[2]=tlf_number[1]; tlf_number[1]=tlf_number[0]; tlf_number[0] = 1; break;
					case 200: tlf_counter++; tlf_number[2]=tlf_number[1]; tlf_number[1]=tlf_number[0]; tlf_number[0] = 2; break;
					case 204: tlf_counter++; tlf_number[2]=tlf_number[1]; tlf_number[1]=tlf_number[0]; tlf_number[0] = 3; break;
					case 208: tlf_counter++; tlf_number[2]=tlf_number[1]; tlf_number[1]=tlf_number[0]; tlf_number[0] = 4; break;
					case 212: tlf_counter++; tlf_number[2]=tlf_number[1]; tlf_number[1]=tlf_number[0]; tlf_number[0] = 5; break;
					case 216: tlf_counter++; tlf_number[2]=tlf_number[1]; tlf_number[1]=tlf_number[0]; tlf_number[0] = 6; break;
					case 220: tlf_counter++; tlf_number[2]=tlf_number[1]; tlf_number[1]=tlf_number[0]; tlf_number[0] = 7; break;
					case 224: tlf_counter++; tlf_number[2]=tlf_number[1]; tlf_number[1]=tlf_number[0]; tlf_number[0] = 8; break;
					case 228: tlf_counter++; tlf_number[2]=tlf_number[1]; tlf_number[1]=tlf_number[0]; tlf_number[0] = 9; break;
					case 232: tlf_counter++; tlf_number[2]=tlf_number[1]; tlf_number[1]=tlf_number[0]; tlf_number[0] = 0; break;
					case 236: tlf_counter = 0; presto=0; presto_ring = 0; presto_time = 0; break;
					default: tlf_counter = 0; presto=0; presto_ring = 0; presto_time = 0; break;
				}

			unStateBMD155.stateBMD155.loopPI = tlf_number[0];
			unStateBMD155.stateBMD155.demPI = (unsigned)tlf_number[1]*10+(unsigned)tlf_number[0];
			unStateBMD155.stateBMD155.statePI = tlf_number[1];

			unsigned char * nbase = (unsigned char *)(NVRAM_BASE);


				if(tlf_counter>=2) 
				{
//		if(((unsigned)tlf_number[1]*10+(unsigned)tlf_number[0]) == unEmb2TypeVer.emb2TypeVer.signature_software[1]) // = self_tlf_number
			if(((unsigned)tlf_number[1]*10+(unsigned)tlf_number[0]) == (*(nbase + 1))) // = self_tlf_number
					{
						presto = 1;
						presto_time = 0;
						presto_ring = 0;
						ring_counter = 0;
					}
					else
					{
						if(((unsigned)tlf_number[1]*10+(unsigned)tlf_number[0]) == 99) 
						{
							presto = 2;
							presto_time = 0;
							presto_ring = 0;
							ring_counter = 0;
						}
					}
					for(tlf_counter=0; tlf_counter<6; tlf_counter++) tlf_number[tlf_counter] = 0xFF;
					tlf_counter=0;
				}
			}

			if(presto)
			{
				if((!presto_ring)&&(time1-presto_time>2000))
				{
					presto_ring = 1;
					presto_time = time1;
					ring_counter++;
					if(ring_counter>7) 
					{
						presto=0;
						presto_ring = 0;
						presto_time = 0;
						Wait();
					}
				}
				else
				{
					if(time1-presto_time<1400) 
					{
						Ring();
					}
					else 
					{
						presto_ring = 0;
						if(presto==1) Pause();
						else Pause2();
					}
				}
			}
		}

		}
		rrr++;	
		*/	
	 //	ResetWatchDog();

	//	unsigned eee;
////////////////////////////////////////////////
   /*

		while(embSerialACT155.UsedUD2())
		{
			byte = embSerialACT155.GetUD2();
	  //		printf(".%c",byte);

			switch(byte)
			{
				case 0xAA: embMsg485_2.Init(); stemp++; break; // �����
				case 0x5A: mode5AUp2=1; break;
				default:
					if(mode5AUp2) 
					{
						embMsg485_2.Add(Modify5A(byte));
						mode5AUp2=0;
					}
					else embMsg485_2.Add(byte);
			}
			if(embMsg485_2.IsEnd())
			{		
				countUD2=0;
//______________________________________________
		   //______________________________________________



				for(i=0; i<32; i++)
				{
					unStateRRL.stateRRL.ppu2_bytes[i] = embMsg485_2.Body(i);
				}
				for(i=0; i<16; i++)
				{
					unStateBMD155.stateBMD155.ppu2_bytes[i] = embMsg485_2.Body(i);
				}
				embMsg485_2.Init(); 
			}
		}
	 //	if(time1-time2old>10) // 10

//101203   		if(time1-time2old > 30) //port
	  //	if(time1-time2old > 100) //port
	     		if((time1-time1old > SEND_PERIOD) && flagsend) //port 101203	 hier use time1old
		{
  //101203			time2old = time1;
#ifdef COUNT_BUFF_ERR
	 if(inportb(0xA) & 0x1)
	 {
		unEmb2TypeVer.emb2TypeVer.ctrlVer1++;
	 }
 if(inportb(0xA) & 0x2)
	 {
		unEmb2TypeVer.emb2TypeVer.ctrlVer2++;
	 }

#endif

			time1old = time1;  //101203	 hier use only time1old
//#ifndef PU_M_TEST //on test have onlu channel2
			flagsend = 0;
//#endif
			countUD2++;
		 //	if(embMsg485Request_2.IsReadyToSend())
		   //	{
			   if(tBuffEmbMsg485Request_2.Used() && send_keeper2)
			{
		//	printfp("\n\r________t1");
				EmbMsg485 embMsg485Request_2;
				embMsg485Request_2.Init();
				tBuffEmbMsg485Request_2.Get(embMsg485Request_2);

			send_keeper2 = 0;

				embSerialACT155.AddUD2(0xFF);
				embSerialACT155.AddUD2(0xAA);
//printfpd("=:%d", embMsg485Request_2.Length());

				for(i=0; i<embMsg485Request_2.Length()+5; i++) 
				{
					switch(embMsg485Request_2.body[i])
					{
					case 0x5A: embSerialACT155.AddUD2(0x5A); embSerialACT155.AddUD2(0x00); break;
					case 0x55: embSerialACT155.AddUD2(0x5A); embSerialACT155.AddUD2(0x01); break;
					case 0xA5: embSerialACT155.AddUD2(0x5A); embSerialACT155.AddUD2(0x02); break;
					case 0xAA: embSerialACT155.AddUD2(0x5A); embSerialACT155.AddUD2(0x03); break;
					default: embSerialACT155.AddUD2(embMsg485Request_2.body[i]);
					}
				}
				embMsg485Request_2.Init();
			}
			else
			{
			send_keeper2 = 1;

				embMsg485Request_2.Init();
				embMsg485Request_2.SetAddr(0);// ��� 1 //addr485);
				embMsg485Request_2.SetLength(1);
				embMsg485Request_2.SetBody(0,0x00);
				embMsg485Request_2.CalcCRC();

				embSerialACT155.AddUD2(0xFF);
				embSerialACT155.AddUD2(0xAA);
//printfpd("=:%d", embMsg485Request_2.Length());

				for(i=0; i<embMsg485Request_2.Length()+3; i++) 
				{
					switch(embMsg485Request_2.body[i])
					{
					case 0x5A: embSerialACT155.AddUD2(0x5A); embSerialACT155.AddUD2(0x00); break;
					case 0x55: embSerialACT155.AddUD2(0x5A); embSerialACT155.AddUD2(0x01); break;
					case 0xA5: embSerialACT155.AddUD2(0x5A); embSerialACT155.AddUD2(0x02); break;
					case 0xAA: embSerialACT155.AddUD2(0x5A); embSerialACT155.AddUD2(0x03); break;
					default: embSerialACT155.AddUD2(embMsg485Request_2.body[i]);
					}
				}
				embMsg485Request_2.Init();
			}
		}

		if(countUD2>4) 
		{
			for(i=0; i<16; i++)
			{
				unStateBMD155.stateBMD155.ppu2_bytes[i] = 0;
			}
			for(i=0; i<32; i++)
			{
				unStateRRL.stateRRL.ppu2_bytes[i] = 0;
			}
			unStateRRL.stateRRL.state = 0x00;
		}

*/
//////////////////////////////////////////////////
//		old_ready_transit=ready_transit;
//		old_ready_mod=ready_mod;
//////////////////////////////////////////////////
 
//#ifdef FULL_TEST_TRANZIT
//if(GetTestMode() != 2)
//{
//#endif
 /* 130521
		Check2InitTransitMod();		
		ProtocolFromModACT155();
		ProtocolFromTransitACT155();

 */

//#ifdef FULL_TEST_TRANZIT
//}
//else
//{
 //t  test_PU37();
//} 
//#endif
//////////////////////////////////////////////////
		i232=0;

//t #include checkremotemod.inc
// #include answermod.inc
//t #include answerpum.inc
 
//101115 #include pu_m_v_rem.c	 //01108
#include checkremotermba.c
//#include answerpumvi.c
#include answerrmba.c
//#include answerpum.inc

	}
//}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : emb_use_irq0(void)
* Returned Value   : none
* Comments         :
*    This routine is used to use irq0
*END*----------------------------------------------------------------------*/
extern "C" void emb_use_irq0()
{
#ifdef IncEmbSerialMD34AVT
//#ifdef PROG_BUKC
//my_int_enable_irq0();
//#endif //PROG_BUKC
  embSerialACT155.IsrXX();
  IntFlag |= INT0_FLAG;
#endif // IncEmbSerialMD34AVT

#ifdef IncEmbSerialACT155
 //	  Stephany19++; 
     embSerialACT155.IsrXX();
 IntFlag |= INT0_FLAG;
#endif // IncEmbSerialACT155

// if(InterruptWatchDog < (unsigned long)INTERRUPT_WAIT)
// {
//   InterruptWatchDog++;
   my_int_enable_irq0();
// }

}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : time_notify_core(void)
* Returned Value   : none
* Comments         :
*    This routine is used to port embisr to be called from timer isr
*END*----------------------------------------------------------------------*/
 
extern "C" void time_notify_core(void)	// called frequency = 1 ms
 {
// hier need call EmbTimer::IsrXX for any exemplar, declared as type EmbTimer
    embTimer.IsrXX();
	TimerCounter ++;

//_________________________________________
//    TimerISR();
//_________________________________________


 } 
	
//_____________________________________________________________________________
#define a14 ab22  
#define a15 ab23
#define a16 ab24  
#define a17 ab25
#define a18 ab26  
#define a19 ab27

#define a20 ab29  
#define a21 ab28
#define a23 ab30
#define ac   aa

void t2ms(unsigned long d)
{
 delay_mcs(d * 2000l);
}



/*
void StartTestTlf()
{
// unsigned char j, aa_loc, aa1, aa2, aa3, code;
 unsigned int i;//,z,  merc, zerc,up0erc,up1erc, w;
 

  //	embRS232.Init(384);		// ������������� RS232 �� �������� 38400 ����/�
///////////////////////////////////////////////////////////////////////////////
 //	Enable(); // ��������� ��� ����������
// ����� ������
for(i=0; i<15; i++) outportb(0x511, 0x08);
outportb(0x511, 0x00);
t2ms(1);

//ScreenSetBuffer();
//ScreenAddString("test TLF----e");
//ScreenIntSent();
 //printf("\n\r test TLF----e\n\r");

//while(1)
//{
//outportb(0x510, 0x02); for(i=0; i<sizeof(an); i++) outportb(0x50F, an[i]); outportb(0x510, 0x01); while((inportb(0x510) & 0x01)!=0);
//outport(wdtcon,0x5555);
//outport(wdtcon,0xaaaa);
//}

   // INIT ������
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab1); i++) outportb(0x50F, ab1[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
t2ms(1);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab2); i++) outportb(0x50F, ab2[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
t2ms(1);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab3); i++) outportb(0x50F, ab3[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
t2ms(1);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab4); i++) outportb(0x50F, ab4[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
t2ms(1);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab5); i++) outportb(0x50F, ab5[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
t2ms(1);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab6); i++) outportb(0x50F, ab6[i]); outportb(0x510, 0x01); //for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
t2ms(1);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab7); i++) outportb(0x50F, ab7[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
t2ms(1);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab8); i++) outportb(0x50F, ab8[i]); outportb(0x510, 0x01); //for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
t2ms(1);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab9); i++) outportb(0x50F, ab9[i]); outportb(0x510, 0x01); //for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab10); i++) outportb(0x50F, ab10[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab11); i++) outportb(0x50F, ab11[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab12); i++) outportb(0x50F, ab12[i]); outportb(0x510, 0x01); //for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab13); i++) outportb(0x50F, ab13[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab14); i++) outportb(0x50F, ab14[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab15); i++) outportb(0x50F, ab15[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab16); i++) outportb(0x50F, ab16[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab17); i++) outportb(0x50F, ab17[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab18); i++) outportb(0x50F, ab18[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab19); i++) outportb(0x50F, ab19[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(ab20); i++) outportb(0x50F, ab20[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);

outportb(0x510, 0x02); for(i=0; i<sizeof(ab21); i++) outportb(0x50F, ab21[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);


	outportb(0x510, 0x02); for(i=0; i<sizeof(a14); i++) outportb(0x50F, a14[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a15); i++) outportb(0x50F, a15[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a16); i++) outportb(0x50F, a16[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a17); i++) outportb(0x50F, a17[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a18); i++) outportb(0x50F, a18[i]); outportb(0x510, 0x01); //for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a19); i++) outportb(0x50F, a19[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a20); i++) outportb(0x50F, a20[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
	outportb(0x510, 0x02); for(i=0; i<sizeof(a21); i++) outportb(0x50F, a21[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);

outportb(0x510, 0x02); for(i=0; i<sizeof(a22); i++) outportb(0x50F, a22[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);
outportb(0x510, 0x02); for(i=0; i<sizeof(a23); i++) outportb(0x50F, a23[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);


outportb(0x511, 0x04); // 0);


outportb(0x511, 0x04); // r(i=0; i<sizeof(a26); i++) outportb(0x50F, a26[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
while((inportb(0x510) & 0x01)!=0);




//outport(wdtcon,0x5555);
//outport(wdtcon,0xaaaa);

	

//t2ms(1000);
//outport(wdtcon,0x5555);
//outport(wdtcon,0xaaaa);




}
*/
//while(1)
  /*
void TestTlf()
	{

  unsigned char  aa_loc, aa1, aa2, aa3, code;
  unsigned int i;

t2ms(2);

// ����� �������  ����� ������

//outport(wdtcon,0x5555);
//outport(wdtcon,0xaaaa);
         
	
outportb(0x510, 0x02); for(i=0; i<sizeof(ac); i++) outportb(0x50F, ac[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
 
 while((inportb(0x510) & 0x01)!=0);

aa_loc = inportb(0x50f);
aa_loc=inportb(0x50f);
aa_loc=inportb(0x50f);
aa1=inportb(0x50f);
aa2=inportb(0x50f);
aa3=inportb(0x50f);
aa_loc =inportb(0x50f);

//if ((aa3 & 0x80)!=0)
//if ((aa1 & 0x40)!=0)
 //{ 
if ((aa1&0x80)&&(aa3&0x80))
//if(1)
{
switch ( (aa3 & 0xfc)>>2 )
{
	case  (48+1) :  code='1'; break;
	case  (48+2) :  code='2'; break;
	case  (48+3) :  code='3'; break;
	case  (48+4) :  code='4'; break;
	case  (48+5) :  code='5'; break;
	case  (48+6) :  code='6'; break;
	case  (48+7) :  code='7'; break;
	case  (48+8) :  code='8'; break;
	case  (48+9) :  code='9'; break;
	case  (48+10) :  code='0'; break;
	case  (48+11) :  code='*'; break;
	case  (48+12) :  code='#'; break;
	case  (48+13) :  code='A'; break;
	case  (48+14) :  code='B'; break;
	case  (48+15) :  code='C'; break;
	default:  	code='?';
}

//ScreenAddByte( aa1); // intreg1
//ScreenAddByte( aa2); // intreg2
//ScreenAddByte( aa3); // intreg3
//ScreenAddByte( aa); // intreg4
//ScreenAddByte( aa); // intreg4
//ScreenAddChar('=');// CR
//ScreenAddChar(code);// CR
//ScreenAddChar(13);// CR
//ScreenIntSent();

#ifndef USART0_TRY_PDC_1T
printf("\r %d %d %d %d %d = %c \r\n", aa1, aa2, aa3, aa_loc, aa_loc, code);
#else
printfp("\r");
printfpd("%d",aa1);
printfpd("%d",aa2);
printfpd("%d",aa3);
printfpd("%d",aa_loc);
printfp(" = ");
printfpd("%c",code);
printfp("\r\n");
OperateBuffers_usart0t();

#endif

}
//tt2ms(100);
t2ms(10);

// }

	//}

	//ScreenAddString(" exit to monitor");
	//ScreenIntSent();
//  asm { db 0fah, 0eah ,00h, 0ah, 00h, 27h ;}  // -- exit to monitor

}
   */
extern "C" void test_PU37_start()
{
 unsigned char  n, i;

 //	embRS232.Init(384);		// ������������� RS232 �� �������� 38400 ����/�
///////////////////////////////////////////////////////////////////////////////
//	Enable(); // ��������� ��� ����������

	// BUS TEST 
	 
	outportb(0x500, i);
	if (i != ( inportb(0x500)) ) 
			{
   //		   		ScreenAddString("BUS test  err");
#ifndef USART0_TRY_PDC_1T
			  printf("\n\rBUS test  err");
#else
		     printfp("\n\rBUS test  err");
#endif


		  //	ScreenIntSent();
	}
	 
	   
//ScreenSetBuffer();
//ScreenAddString("test PU37   4 DDC ������� timer mode----");
//ScreenIntSent();
//t printf("\rtest PU37   4 DDC channels timer mode----\r");

   // INIT DDC  -- �������

for (i=0; i<20; i++)
//for (i=0; i<200; i++)
	{
   n=inportb(0x507);
   n=inportb(0x50B);
   n=inportb(0x50d);
   n=inportb(0x509);
  }

   outport(0x506,0x55); // ��������� ���������� �� �����
// outport(0x506,0xff);
}
//outport(wdtcon,0x5555);
//outport(wdtcon,0xaaaa);

//while(1)


 unsigned char  rm, rmo, rtz,rtzo, tm, ttz, tup0, tup1;     
  unsigned int   merc, zerc,up0erc,up1erc;
  unsigned char rup0, rup0o,  rup1, rup1o;
  unsigned long rmc, tmc, rtzc,  ttzc, tup0c, rup0c, tup1c, rup1c;


void test_PU37_interrupt_ovner()
{

 //unsigned int tmp =  (unsigned int)INT0_FLAG;
   //t      while (IntFlag & tmp)
   //     if(IntFlag & tmp)
   //	 if(1)
	 //	{
	   //	  IntFlag &=  ~tmp;
		//n=inportb(0x505); // ����� ������ ����������


   //		if
       char cnt = 16;
	 //	while (((inportb(0x505) &  0x10) != 0) && cnt)  // RX up0
		while (((inportb(0x505) &  0x10) != 0) && cnt)  // RX up0
				{
				 	rup0=inportb(0x50b);
					rup0c++;
					if (rup0o!=rup0)
							{			
									if (up0erc <0xfffe) up0erc++;
							}
					rup0++;
					rup0o=rup0;
					cnt--;
				}

	 //	if 
	   cnt = 16;
		while(((inportb(0x505) &  0x40) != 0) && cnt) // RX up1
				{
				 	rup1=inportb(0x50d);
					rup1c++;
					if (rup1o!=rup1)
							{			
									if (up1erc <0xfffe) up1erc++;
							}
					rup1++;
					rup1o=rup1;
					cnt--;
				}

	//	if
  //	bstate =  inportb(0x505);

		cnt = 16; //t16;
		while (((inportb(0x505) &  0x01) != 0) && cnt)  // RX MODEM
				{
				 	rm=inportb(0x507);
					rmc++;
		  	 //  printf("MOD : rmo: %d  rm: %d  \n\r", rmo, rm);

					if (rmo!=rm)
							{		
							 //		tchar =   inportb(0x508);
							   //		tchar =   inportb(0x508);	
									if (merc <0xfffe) merc++;
							  //	    printf("MOD : rmo: %d  rm: %d  tchar: 0x%02x \n\r", rmo, rm, tchar);
							  //	    printf("MOD : rmo: %X  rm: %X   \n\r", rmo, rm);
									//508
									
							}
					rm++;
					rmo=rm;
					cnt--;
				}

	  //	if 
	    cnt = 16; //t16;
		while(((inportb(0x505) &  0x04) != 0) && cnt)  // RX TRANZIT
				{
				 rtz=inportb(0x509);
					rtzc++;
					if (rtzo!=rtz)
							{
									if (zerc <0xfffe) 	zerc++;
								  //	 printf("TRNZ : rtzo: %d  rtz: %d  tchar: 0x%02x \n\r", rmo, rm, tchar);
							  //		 printf("TRNZ : rtzo: %d  rtz: %d   \n\r", rtzo, rtz);

							}
				rtz++;
				rtzo=rtz;
				cnt--;
				}

	    my_int_enable_irq0();

}

void test_PU37()
{
	 /*
 static unsigned char  rm, rmo, rtz,rtzo, tm, ttz, tup0, tup1,   i;     
 static unsigned int   merc, zerc,up0erc,up1erc;
 static unsigned char rup0, rup0o,  rup1, rup1o;
 static unsigned long rmc, tmc, rtzc,  ttzc, tup0c, rup0c, tup1c, rup1c;

	*/
  static unsigned char    i;

 static int PeriodCounter = 0l;
// unsigned char tchar;
// unsigned char bstate;
// unsigned long cnt;
// for (i=0; i<20; i++)
//	{
//   n=inportb(0x507);
//   n=inportb(0x50B);
//   n=inportb(0x50d);
//   n=inportb(0x509);
//  }


 //  outport(0x506,0x55); //t ��������� ���������� �� �����


//t2ms(3);
//t delay_mcs(1l); //work 
//  delay_mcs(50l); 
//for (bt=0; bt<0x02ff; bt++) {} // ��������
   		i++;
// DDC  rx- tx test----------------------------------------------------
// timer mode TX---------------------------------------
 PeriodCounter++;
// if(PeriodCounter > 100000l)
//ok if(PeriodCounter > 10000l)
 //ok  if(PeriodCounter > 1000l)
//ok  if(PeriodCounter > 10l)
//t if(PeriodCounter >5l)
//#ifndef FULL_TEST_TRANZIT
 if(PeriodCounter > TEST_PERIOD)

//if(PeriodCounter > 10000l) //t
//#else
//if(1)
//#endif// FULL_TEST_TRANZIT
  {
 PeriodCounter = 0l;
	 // TX UP0
//for (i=0; i<10; i++)
	 //	{

//modem transmit 508 : bit5
//transit transmit50a : bit5
//up0 : transmit50c : bit5
//up1 : transmit 50e
 

	 // 	bstate =  inportb(0x50c);

		//  printf("bstate up0:  %d  \n\r", bstate);


			   // while((inportb(0x505) & 0x20) == 0) {}
				  //	  if(inportb(0x505) & 0x20)
				 //	    if(inportb(0x50c) & 0x20)

		   //			  {
	//	   #ifndef FULL_TEST_TRANZIT
			 /*
  	 if(embSerialACT155.UsedSendUD1() < 5) 
			     {

				embSerialACT155.AddUD1(tup0++);
			    embSerialACT155.AddUD1(tup0++);
			    embSerialACT155.AddUD1(tup0++);
				embSerialACT155.AddUD1(tup0++);
				embSerialACT155.AddUD1(tup0++);


			   //		   outportb(0x50B, tup0++);
						 		 tup0c += 5;   
	 //		#endif								   
								 } 
			   */
#ifdef PROG_BMD155PS				
		   if(embSerialACT155.UsedSendPower() < 5) 
			     {

				embSerialACT155.AddPower(tup0++);
			    embSerialACT155.AddPower(tup0++);
			    embSerialACT155.AddPower(tup0++);
				embSerialACT155.AddPower(tup0++);
				embSerialACT155.AddPower(tup0++);


			   //		   outportb(0x50B, tup0++);
						 		 tup0c += 5;   
	 //		#endif								   
								 } 
#endif // PROG_BMD155PS

				 





	  //	}

// TIMER MODE
	 // TX UP1
//for (i=0; i<2; i++)
//{
			  //	 while((inportb(0x505) & 0x80) == 0) {}
//bstate =  inportb(0x50e);

   //		  printf("bstate up1 :  %d  \n\r", bstate);

	//					if (inportb(0x50e) & 0x20)
   //						{
 //  #ifndef FULL_TEST_TRANZIT
 /*
  		if(embSerialACT155.UsedSendUD2() < 5)
			     {
			   //ok		   embSerialACT155.UsedUD1();
			   	  		 embSerialACT155.AddUD2(tup1++);
						  embSerialACT155.AddUD2(tup1++);
						   embSerialACT155.AddUD2(tup1++);
						    embSerialACT155.AddUD2(tup1++);
							 embSerialACT155.AddUD2(tup1++);

   					 //t	 outportb(0x50D, tup1++);
   				   		 tup1c+=5;
//#endif
   					  	 }
						 */
//}
	 // TX MODEM
//for (i=0; i<8; i++)
//{
 				   //		 while((inportb(0x505) & 0x02) == 0) {}
  // bstate =  inportb(0x508);
	   //		 printf("bstate md :  %d  \n\r", bstate);

				//		 if	 (inportb(0x508) & 0x20)
					//	 {

//#ifdef FULL_TEST_TRANZIT
		   if(embSerialACT155.UsedSendMod() < 5)
		  // 	if(!embSerialACT155.UsedSendMod()) 
				  {
		  		   embSerialACT155.AddMod(tm++);
				      embSerialACT155.AddMod(tm++);
					     embSerialACT155.AddMod(tm++);
						    embSerialACT155.AddMod(tm++);
							   embSerialACT155.AddMod(tm++);

		  		   tmc += 5;
		  		  }
//#else

			//t	  outportb(0x507, tm++);
			   //	  tmc++;
//#endif

					  //	 }
//}
	  // TX TRANZIT
//for (i=0; i<8; i++)
//{
  				   //		while((inportb(0x505) & 0x08) == 0) {}
   // bstate =  inportb(0x50a);
		   //		 printf("bstate trz :  %d  \n\r", bstate);

			//			if (inportb(0x50a) & 0x20)
					//	{
//#ifdef FULL_TEST_TRANZIT
			  //	  while
		  	  if(embSerialACT155.UsedSendTransit() < 5)
		   //	  if(!embSerialACT155.UsedSendTransit()) 
			     {
			   	   embSerialACT155.AddTransit(ttz++);
	   		 //  	   ttzc++;
				     embSerialACT155.AddTransit(ttz++);
	   		//   	   ttzc++;
  					embSerialACT155.AddTransit(ttz++);
	   		//   	   ttzc++;
  					embSerialACT155.AddTransit(ttz++);
	   		 //  	   ttzc++;
  					embSerialACT155.AddTransit(ttz++);
	   		 //  	   ttzc++;
			  ttzc += 5;
  
			    }
  			//	if(embSerialACT155.UsedSendTransit() < 2)
		   //	  if(!embSerialACT155.UsedSendTransit()) 
			//     {
			//   	   embSerialACT155.AddTransit(ttz++);
	   		//   	   ttzc++;
			//    }
			//	  if(embSerialACT155.UsedSendTransit() < 1)
		   //	  if(!embSerialACT155.UsedSendTransit()) 
			//     {
			//   	   embSerialACT155.AddTransit(ttz++);
	   		//   	   ttzc++;
			//    }
			  



//#else

					  //	 outportb(0x509,  ttz++); 
				  //		ttzc++;
//#endif
				   //		}
//}

} //PeriodCounter
//--------------------------------------------------------------

//	if (0x80 & inportb(0xff2e)) // ��� ��������� ���������� INT3

   //	while (0x20 & inportb(0xff2e)) // ��� ��������� ���������� INT1
 /*
   unsigned int tmp =  (unsigned int)INT0_FLAG;
   //t      while (IntFlag & tmp)
        if(IntFlag & tmp)
   //	 if(1)
		{
		  IntFlag &=  ~tmp;
		//n=inportb(0x505); // ����� ������ ����������


   //		if
        cnt = 16;
		while (((inportb(0x505) &  0x10) != 0) && cnt)  // RX up0
				{
				 	rup0=inportb(0x50b);
					rup0c++;
					if (rup0o!=rup0)
							{			
									if (up0erc <0xfffe) up0erc++;
							}
					rup0++;
					rup0o=rup0;
					cnt--;
				}

	 //	if 
	   cnt = 16;
		while(((inportb(0x505) &  0x40) != 0) && cnt) // RX up1
				{
				 	rup1=inportb(0x50d);
					rup1c++;
					if (rup1o!=rup1)
							{			
									if (up1erc <0xfffe) up1erc++;
							}
					rup1++;
					rup1o=rup1;
					cnt--;
				}

	//	if
  //	bstate =  inportb(0x505);

		cnt = 16;
		while (((inportb(0x505) &  0x01) != 0) && cnt)  // RX MODEM
				{
				 	rm=inportb(0x507);
					rmc++;
		  	 //  printf("MOD : rmo: %d  rm: %d  \n\r", rmo, rm);

					if (rmo!=rm)
							{		
									tchar =   inportb(0x508);
									tchar =   inportb(0x508);	
									if (merc <0xfffe) merc++;
								    printf("MOD : rmo: %d  rm: %d  tchar: 0x%02x \n\r", rmo, rm, tchar);
									//508
									
							}
					rm++;
					rmo=rm;
					cnt--;
				}

	  //	if 
	    cnt = 16;
		while(((inportb(0x505) &  0x04) != 0) && cnt)  // RX TRANZIT
				{
				 rtz=inportb(0x509);
					rtzc++;
					if (rtzo!=rtz)
							{
									if (zerc <0xfffe) 	zerc++;
							}
				rtz++;
				rtzo=rtz;
				cnt--;
				}
		

	//	} 

*/

//___________________________________________________________________________
 
	if( embSerialACT155.m_RBuffMod.Used()) 
	{
	rm=embSerialACT155.m_RBuffMod.Get();
					rmc++;
		  	 //  printf("MOD : rmo: %d  rm: %d  \n\r", rmo, rm);

					if (rmo!=rm)
							{		
							 //		tchar =   inportb(0x508);
							   //		tchar =   inportb(0x508);	
									if (merc <0xfffe) merc++;
								 //   printf("MOD : rmo: %d  rm: %d  tchar: 0x%02x \n\r", rmo, rm, tchar);
									//508
									
							}
					rm++;
					rmo=rm;

}

  
  //	if(irq.bit.IRQ_RX_trans)// m_RBuffTransit.Add(inportb(0x509)); 
   if( embSerialACT155.m_RBuffTransit.Used()) 
 {	
  rtz=embSerialACT155.m_RBuffTransit.Get();
					rtzc++;
					if (rtzo!=rtz)
							{
									if (zerc <0xfffe) 	zerc++;
							}
				rtz++;
				rtzo=rtz;
}


   //	if(irq.bit.IRQ_RX_UD1)// m_RBuffUD1.Add(inportb(0x50B)); 
#ifdef PROG_BMD155PS   
	if( embSerialACT155.m_RBuffPower.Used())
	{
				 	rup0=embSerialACT155.m_RBuffPower.Get();
					rup0c++;
					if (rup0o!=rup0)
							{			
									if (up0erc <0xfffe) up0erc++;
							}
					rup0++;
					rup0o=rup0;
				  //	cnt--;
				}
#endif //  PROG_BMD155PS
			   

   //	if(irq.bit.IRQ_RX_UD2)//	 m_RBuffUD2.Add(inportb(0x50D)); 	   //090413
   /*
	if( embSerialACT155.m_RBuffUD2.Used())
	{
				 rup1=embSerialACT155.m_RBuffUD2.Get();
				   rup1c++;
					if (rup1o!=rup1)
							{
									if (up1erc <0xfffe) 	up1erc++;
							}
				rup1++;
				rup1o=rup1;
		 //	cnt--;
	}

	 */

			   
//___________________________________________________________________________





#ifdef PROG_BMD155PS	  
	if (tup0c > 20000)
		{

	 //		ScreenAddString("Send UP0 --");
	//		ScreenAddInt(tup0c);
	 //		ScreenAddString(" RX--");
	//		ScreenAddInt(rup0c);
	//		ScreenAddString(" ERR--");
   //			ScreenAddInt(up0erc);
   //			ScreenIntSent();
 //  printf("\n\rSend UP0 -- %d  RX-- %d  ERR-- %d\n\r", tup0c, rup0c, up0erc);
#ifndef USART0_TRY_PDC_1T
   printf("\n\rSend Power -- %d  RX-- %d  ERR-- %d\n\r", tup0c, rup0c, up0erc);
#else
  printfp("\n\rSend Power --"); 
  printfpd("%d",tup0c);
  printfp(" RX--"); 
  printfpd("%d",rup0c);
  printfp(" ERR--"); 
  printfpd("%d",up0erc);
  OperateBuffers_usart0t();

#endif
			tup0c=0;rup0c=0; up0erc=0;
			}
#endif //PROG_BMD155PS
			
/*
	if (tup1c>20000)
		{

	  //		ScreenAddString("Send UP1 --");
	  //		ScreenAddInt(tup1c);
	  //		ScreenAddString(" RX--");
	  //		ScreenAddInt(rup1c);
	  //		ScreenAddString(" ERR--");
	  //		ScreenAddInt(up1erc);
	  //		ScreenIntSent();
  	  printf("Send UP1 -- %d  RX-- %d  ERR-- %d\n\r", tup1c, rup1c, up1erc);

			tup1c=0;rup1c=0; up1erc=0;

			}
*/

	if (ttzc>20000)
		{

	   //		ScreenAddString("Send TrZ --");
	   //		ScreenAddInt(ttzc);
	   //		ScreenAddString(" RX--");
	   //		ScreenAddInt(rtzc);
	   //		ScreenAddString(" ERR--");				  
	   //		ScreenAddInt(zerc);
	   //		ScreenIntSent();
   	//   printf("Send TrZ -- %d  RX-- %d  ERR-- %d\n\r", ttzc, rtzc, zerc);

#ifndef USART0_TRY_PDC_1T
    printf("Send TrZ -- %d  RX-- %d  ERR-- %d\n\r", ttzc, rtzc, zerc);
#else
  printfp("\n\rSend TrZ --"); 
  printfpd("%d",ttzc);
  printfp(" RX--"); 
  printfpd("%d",rtzc);
  printfp(" ERR--"); 
  printfpd("%d",zerc);
OperateBuffers_usart0t();

#endif

	 //  printf("count = %d \n\r",count1);

			ttzc=0;rtzc=0; zerc=0;
			}
	
	if (tmc>20000)
		{

		 //	ScreenAddString("Send MOD --");
		 //	ScreenAddInt(tmc);
		 //	ScreenAddString(" RX--");
		 //	ScreenAddInt(rmc);
		 //	ScreenAddString(" ERR--");
		 //	ScreenAddInt(merc);
		 //	ScreenIntSent();
   //	   printf("Send MOD -- %d  RX-- %d  ERR-- %d\n\r", tmc, rmc, merc);

#ifndef USART0_TRY_PDC_1T
     printf("Send MOD -- %d  RX-- %d  ERR-- %d\n\r", tmc, rmc, merc);
#else
  printfp("\n\rSend MOD --"); 
  printfpd("%d",tmc);
  printfp(" RX--"); 
  printfpd("%d",rmc);
  printfp(" ERR--"); 
  printfpd("%d",merc);
OperateBuffers_usart0t();
#endif


			tmc=0;rmc=0; merc=0;
		}
	

//outport(wdtcon,0x5555);
//outport(wdtcon,0xaaaa);
 //     wd_reset();	

	//  my_int_enable_irq0();
   //	  }
 //	  else
 //	  {
 //	  printf("\n wait interrupt...\n\r");
 //	  }
//}

	//ScreenAddString(" exit to monitor");
	//ScreenIntSent();
//  asm { db 0fah, 0eah ,00h, 0ah, 00h, 27h ;}  // -- exit to monitor
}




//#ifdef PROG_BMD155
extern  "C" unsigned long TypeVer(void)
{
static unsigned long ret;
ret =  (unsigned long)unEmb2TypeVer.emb2TypeVer.type;
ret <<=16;
ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.softVer;
//ret = 0x12345678;
return ret;
}

extern  "C" unsigned long CtrlNumberS(void)
{
static unsigned long ret;
ret =  (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlYear;
ret <<=16;
ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlNumber;
//ret = 0x12345678;
return ret;
}

extern  "C" unsigned long CtrlVerS(void)
{
static unsigned long ret;
ret =  (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlVer1;
ret <<=16;
ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlVer2;
//ret = 0x12345678;
return ret;
}

extern  "C" unsigned long BlockS(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulBlock;
//ret <<=16;
//ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlVer2;
//ret = 0x12345678;
return ret;
}

extern  "C" unsigned long ErrOutS(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulErrOut;
//ret <<=16;
//ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlVer2;
//ret = 0x12345678;
return ret;
}

extern  "C" unsigned long ErrAfterRS1S(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulErrAfterRS1;
//ret <<=16;
//ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlVer2;
//ret = 0x12345678;
return ret;
}

extern  "C" unsigned long ErrAfterRS2S(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulErrAfterRS2;
//ret <<=16;
//ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlVer2;
//ret = 0x12345678;
return ret;
}

extern  "C" unsigned long ErrBeforeRS1S(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulErrBeforeRS1;
//ret <<=16;
//ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlVer2;
//ret = 0x12345678;
return ret;
}

extern  "C" unsigned long ErrBeforeRS2S(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulErrBeforeRS2;
//ret <<=16;
//ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlVer2;
//ret = 0x12345678;
return ret;
}

extern  "C" unsigned long StateModemS(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.state[4];
ret <<= 24;
ret =  unStatePUM.statePUM.state[2];
ret <<= 8;

//ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlVer2;
//ret = 129; //t
return ret;
}
/*
extern  "C" unsigned long LoopS(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.state[5];
return ret;
}
*/
//extern unsigned long Stephany19;
/*
extern  "C" void SetLoopS(unsigned long val)
{
 unStatePUM.statePUM.state[5] = (unsigned char)val;
  Stephany19 = val;
}
 */
/*
extern  "C" unsigned long TlfNumberS(void)
{
static unsigned long ret;
ret =  unEmb2TypeVer.emb2TypeVer.signature_software[1];
return ret;
}
*/
//extern  "C" void SetTlfNumberS(unsigned long *val)
/*
extern  "C" void SetTlfNumberS(signed long val)
{
 unEmb2TypeVer.emb2TypeVer.signature_software[1] = (unsigned char)val;
 unsigned char* bt = (unsigned char *)(NVRAM_BASE);
 *(bt+1) = (unsigned char)val;
  Stephany19 = val;
}
*/
//extern  "C" unsigned long SetLoopO(uchar_ptr data_ptr, uint_32 * data_len)
 /*
extern  "C" void SetLoopO(unsigned char* data_ptr, unsigned long* data_len)
{
  if(!(* data_len))
  {
	 * data_ptr =  unStatePUM.statePUM.state[5];
  }
  else
  {
	  unStatePUM.statePUM.state[5] =  * data_ptr;
  }

}
 */
extern  "C" void SetTlfNumberO(unsigned char* data_ptr, unsigned long* data_len)
{
  unsigned char* bt = (unsigned char *)(NVRAM_BASE);
  unEmb2TypeVer.emb2TypeVer.signature_software[1] = (unsigned char)*data_ptr;
  *(bt+1) =   (unsigned char)*data_ptr;
  //Stephany19 = (unsigned char)*data_ptr;
}


//extern  "C" unsigned char * GetTlfNumberO(unsigned char* data_ptr, unsigned long* data_len)

extern  "C" void SetBERO(unsigned char* data_ptr, unsigned long* data_len)
{
}


//extern  "C" unsigned char * GetTlfNumberO(unsigned char* data_ptr, unsigned long* data_len)
extern  "C" unsigned char * GetTlfNumberO(unsigned long* data_len)
{
 unsigned char* bt = (unsigned char *)(NVRAM_BASE);
 *data_len = 1;
 return (bt+1);
}





extern  "C" void SetLoopO(unsigned char* data_ptr, unsigned long* data_len)
{
  unStatePUM.statePUM.state[5] = (unsigned char)*data_ptr;
 // Stephany19 = (unsigned char)*data_ptr;
}


//extern  "C" unsigned char * GetTlfNumberO(unsigned char* data_ptr, unsigned long* data_len)
extern  "C" unsigned char * GetLoopO(unsigned long* data_len)
{
  *data_len = 1;
  return &unStatePUM.statePUM.state[5];
}

extern  "C" unsigned long BitErrOut(void)
{
	return ErrResSNMP;
}
extern  "C" unsigned long bReset(void)
{
	return 0x55;
}


extern "C" void SetBLoopNear(unsigned long varval)
{
   	if(varval) {outportb(0x525, unStatePUM.statePUM.state[5] | 0x4);}
	else {outportb(0x525, unStatePUM.statePUM.state[5] & 0xfb);}
}

extern "C" void SetBLoopFar(unsigned long varval)
{
	if(varval) {outportb(0x525, unStatePUM.statePUM.state[5] | 0x8);}
	else {outportb(0x525, unStatePUM.statePUM.state[5] & 0xf7);}
}

extern "C" void SetBAlarmLaser(unsigned long varval)
{
   if(varval) {outportb(0x525, unStatePUM.statePUM.state[4] | 0x8);}
	else {outportb(0x525, unStatePUM.statePUM.state[4] & 0xf7);}

}







extern  "C" unsigned long bSignal1(void)
{
	 //  522 : 1  1/0  unlock /lock
	 if(unStatePUM.statePUM.state[2] & 2) return 0l;
	 else return 1l;
}
extern  "C" unsigned long bSignal2(void)
{
  if(unStatePUM.statePUM.state[2] & 0x8) return 0l;
	 else return 1l;

}
extern  "C" unsigned long bOpticModule(void)
{
   if(unStatePUM.statePUM.state[4] & 0x4) return 0l;
	 else return 1l;

}
extern  "C" unsigned long bFrame(void)
{
   if(unStatePUM.statePUM.state[4] & 0x1) return 0l;
	 else return 1l;
}
extern  "C" unsigned long InputSignal(void)
{
	if(unStatePUM.statePUM.state[4] & 0x1) return 0l;
	 else return 1l;

}
extern  "C" unsigned long bLoopNear(void)
{
	if(unStatePUM.statePUM.state[5] & 0x4) return 1l;
	 else return 0l;

}
extern  "C" unsigned long bLoopFar(void)
{
	if(unStatePUM.statePUM.state[5] & 0x8) return 1l;
	 else return 0l;
}
extern  "C" unsigned long bAlarmLaser(void)
{
 //	if(unStatePUM.statePUM.state[4] & 0x8) return 0l;
 //	 else return 1l;
  	if(unStatePUM.statePUM.state[4] & 0x8) return 1l;
 	 else return 0l;


}





// unsigned char *TLFNumberData;
/*
extern "C" unsigned char *TLFNumberData2(void)
{
 static unsigned char Buffer[] = "Test"; 
 return	Buffer;
}
*/


/*
extern "C" void embMsgWestE_Init(void)
{
 embMsgWestE.Init();
}


extern "C" void embMsgWestE_Add(char * pc)
{
 embMsgWestE.Add((unsigned char)* pc);
  
}
*/

//extern "C" void printEmb(void)
//{
// for(i=0; i< 10; i++) 
//		   	 {
		//   	 	printEthLongHex(embMsgWestE.body[i]);
 //		   	 }
//}

//___________________________________________________________________________________
/* 130523
char TestRing()
{
unsigned char  aa_loc, aa1, aa2, aa3;//, code;
unsigned int i;
  	t2ms(2);
  	outportb(0x510, 0x02); for(i=0; i<sizeof(ac); i++) outportb(0x50F, ac[i]); outportb(0x510, 0x01);// for(i=0; i<100; i++);
  	while((inportb(0x510) & 0x01)!=0);
	aa_loc = inportb(0x50f);
	aa_loc=inportb(0x50f);
	aa_loc=inportb(0x50f);
	aa1=inportb(0x50f);
	aa2=inportb(0x50f);
	aa3=inportb(0x50f);
	aa_loc =inportb(0x50f);
#ifndef USART0_TRY_PDC_1T
	printf("\r aa1=0x%X aa2=0x%X aa3=0x%X aa_loc=0x%X \r\n", aa1, aa2, aa3, aa_loc);
#else
	printfp("\r aa1=0x");
	printfpd("%X ", aa1);
    printfp(" aa2=0x");
	printfpd("%X", aa2);
    printfp(" aa3=0x");
	printfpd("%X", aa3);
    printfp(" aa_loc=0x");
	printfpd("%X", aa_loc);
	OperateBuffers_usart0t();
#endif


  	if (aa1 & 0x48)
	{
	return 1;
	}
	t2ms(10);
	return 0;
}

void StartRing()
{
 Ring();
}
*/
//__________________________________________________________________________________


//#ifdef PROG_PU_M_MUX_TEST
  /*
extern "C" void CompareRegs(void)
{
unsigned char nvram, xil;
unsigned char  *bt;
 	bt = (unsigned char *)(NVRAM_BASE);
   	 for(long i = 0; i < 0x10; i++)
	 {
	  xil = inportb3(0x90 + i); 
	  nvram = *(bt + PARAMETERS_DISPLACEMENT1 + 0x90 + i);
	  	if(xil != nvram)
	  	{
		 printf("\n\r i = 0x%02X xil = 0x%02X nvram = 0x%02X \n\r", i , xil , nvram);
	  	}
		else
		{
		 printf("\r i = 0x%02X xil = 0x%02X nvram = 0x%02X", i , xil , nvram);
		}
	 }
}
   */
//#endif //PROG_PU_M_MUX_TEST

#ifdef COUNT_BUFF_ERR

extern "C" unsigned long GetCounter1()
{ 
 return unEmb2TypeVer.emb2TypeVer.ctrlVer1;
}

extern "C" unsigned long GetCounter2()
{ 
 return unEmb2TypeVer.emb2TypeVer.ctrlVer2;
}

 
#endif


